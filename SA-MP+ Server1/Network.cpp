#include "Network.h"
#include "Callback.h"

#include <SA-MP+/Debug.h>
#include <RakNet/MessageIdentifiers.h>
#include <RakNet/BitStream.h>

Network::Network(std::string address, unsigned short port, unsigned short maxConnections) : initialized(false)
{
	if (address.size() > 0)
		initialize(address.c_str(), port, maxConnections);
	else
		initialize(NULL, port, maxConnections);
}

void Network::initialize(const char* address, unsigned short port, unsigned short maxConnections)
{
	raknetPeer = RakNet::RakPeerInterface::GetInstance();
	raknetSocketDescriptor = new RakNet::SocketDescriptor(port, address);

	if (raknetPeer->Startup(maxConnections, raknetSocketDescriptor, 1) != RakNet::StartupResult::RAKNET_STARTED)
	{
		Debug::write("SA-MP+ 플러그인을 초기화 할 수 없습니다.");
		exit(EXIT_FAILURE);
	}

	raknetPeer->SetIncomingPassword(SAMP_PLUS_PASSWORD, strlen(SAMP_PLUS_PASSWORD));
	raknetPeer->SetMaximumIncomingConnections(maxConnections + 1);

	Debug::write("SA-MP+ 서버 생성 됨. 주소: %s 포트: %d 최대 접속 인원: %d", address, port, maxConnections);

	initialized = true;
}

bool Network::destroyUnhandledConnection(RakNet::SystemAddress& address)
{
	const char* addressString = address.ToString(false);

	if (addressString == NULL || strlen(addressString) == 0)
		return false;

	for (std::list<ClientSocketInfo*>::iterator it = unhandledConnections.begin(); it != unhandledConnections.end(); ++it)
	{
		if (strcmp(addressString, (*it)->getAddress().ToString(false)) == 0)
		{
			delete (*it);

			unhandledConnections.erase(it);

			return true;
		}
	}

	return false;
}

Player* Network::handleConnection(unsigned int playerid)
{
	Player* player = getPlayerFromPlayerId(playerid);

	if (player != NULL)
		return player;

	char ip[16];

	GetPlayerIp(playerid, ip, sizeof(ip));

	if (strlen(ip) == 0)
		return NULL;

	for (std::list<ClientSocketInfo*>::iterator it = unhandledConnections.begin(); it != unhandledConnections.end(); ++it)
	{
		if (strcmp(ip, (*it)->getAddress().ToString(false)) == 0)
		{
			player = new Player(*it);

			unhandledConnections.erase(it);
			players.insert(std::map<unsigned int, Player*>::value_type(playerid, player));

			player->getSocket()->setState(ClientSocketInfo::eClientConnectionState::CONNECTED);

			return player;
		}
	}

	return NULL;
}

bool Network::destroyPlayerConnection(unsigned int playerid, bool kick)
{
	Player* player = getPlayerFromPlayerId(playerid);

	if (player == NULL)
		return false;

	if (kick)
		sendPacketEasy(PacketType::ePacketType::PACKET_PLAYER_PROPER_KICK, player->getSocket()->getAddress());
	else
		sendPacketEasy(PacketType::ePacketType::PACKET_PLAYER_PROPER_DISCONNECT, player->getSocket()->getAddress());

	closeConnectionEasy(player->getSocket()->getAddress());

	delete player;

	return players.erase(playerid);
}

void Network::update()
{
	if (!isInitialized())
		return;

	RakNet::Packet* packet;
	int playerid;

	for (packet = raknetPeer->Receive(); packet != NULL; raknetPeer->DeallocatePacket(packet), packet = raknetPeer->Receive())
	{
		if (packet->length <= 0)
			continue;

		RakNet::BitStream bitStream(&packet->data[1], packet->length - 1, false);
		Debug::write("받은 패킷 : %i, 로컬 : %i, 바이트 크기 : %i byte(s)", packet->data[0], packet->wasGeneratedLocally, bitStream.GetNumberOfBytesUsed());

		playerid = -1;

		if (packet->data[0] == ID_NEW_INCOMING_CONNECTION)
			sendPacketEasy(PacketType::ePacketType::PACKET_PLAYER_REQUEST_VERSION, packet->systemAddress);
		else if (packet->data[0] == PacketType::ePacketType::PACKET_PLAYER_JOIN_DATA)
		{
			for (std::list<ClientSocketInfo*>::iterator it = unhandledConnections.begin(); it != unhandledConnections.end(); ++it)
			{
				if (std::time(NULL) - (*it)->getCreationTime() >= MAX_CONNECTION_TIME)
				{
					delete *it;
					unhandledConnections.erase(it);
				}
			}

			int clientIntVersion;
			RakNet::RakString clientStringVersion;

			if (bitStream.Read(clientIntVersion) && bitStream.Read(clientStringVersion))
			{
				if (Callback::execute("OnPlayerSAMPPlusConnect", "is", packet->systemAddress.GetPort(), packet->systemAddress.ToString(false)))
				{
					ClientSocketInfo* playerSocketInfo = new ClientSocketInfo(packet->systemAddress, packet->guid, clientIntVersion, clientStringVersion);

					unhandledConnections.push_back(playerSocketInfo);

					Debug::write("새로운 접속 %s:%i 허용 됨.", packet->systemAddress.ToString(false), packet->systemAddress.GetPort());
				}
				else
				{
					sendPacketEasy(PacketType::ePacketType::PACKET_CONNECTION_REJECTED, packet->systemAddress);
					closeConnectionEasy(packet->systemAddress);

					Debug::write("새로운 접속 %s:%i 거부 됨.", packet->systemAddress.ToString(false), packet->systemAddress.GetPort());
				}
			}
		}
		else
		{
			playerid = getPlayerIdFromSystemAddress(packet->systemAddress);

			switch (packet->data[0])
			{
			case ID_DISCONNECTION_NOTIFICATION:
				if (playerid != -1)
					destroyPlayerConnection(playerid);
				else
					destroyUnhandledConnection(packet->systemAddress);

				Debug::write("주소 %s 의 접속이 종료 됨.", packet->systemAddress.ToString(false));

				break;

			case ID_CONNECTION_LOST:
				if (playerid != -1)
					destroyPlayerConnection(playerid);
				else
					destroyUnhandledConnection(packet->systemAddress);

				Debug::write("주소 %s 와의 연결이 끊어짐.", packet->systemAddress.ToString(false));

				break;

			default:
				Debug::write("알 수 없는 패킷이 들어옴. (유형: %u, 로컬: %u)", packet->data[0], packet->wasGeneratedLocally);

				break;
			}
		}
	}
}

Player* Network::getPlayerFromPlayerId(unsigned int playerid)
{
	std::map<unsigned int, Player*>::iterator it = players.find(playerid);

	if (it != players.end())
		return it->second;

	return NULL;
}

int Network::getPlayerIdFromSystemAddress(RakNet::SystemAddress& address)
{
	const char* addressString = address.ToString(false);

	if (addressString == NULL || strlen(addressString) == 0)
		return -1;

	for (std::map<unsigned int, Player*>::iterator it = players.begin(); it != players.end(); ++it)
	{
		if (strcmp(address.ToString(false), it->second->getSocket()->getAddress().ToString(false)) == 0)
			return (*it).first;
	}

	return -1;
}

uint32_t Network::sendPacketEasy(PacketType::ePacketType packetType, const RakNet::SystemAddress destAddress, RakNet::BitStream* sourceBitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool broadCast)
{
	RakNet::BitStream bitStream;

	bitStream.Write(static_cast<unsigned char>(packetType));

	if (sourceBitStream)
		bitStream.Write(reinterpret_cast<char*>(sourceBitStream->GetData()), sourceBitStream->GetNumberOfBytesUsed());

	return raknetPeer->Send(&bitStream, priority, reliability, orderingChannel, destAddress, broadCast);
}

uint32_t Network::sendPlayerPacketEasy(PacketType::ePacketType packetType, unsigned int playerid, RakNet::BitStream* sourceBitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool broadCast)
{
	Player* player = getPlayerFromPlayerId(playerid);

	if (player == NULL || player->getSocket()->getState() != ClientSocketInfo::eClientConnectionState::CONNECTED)
		return 0;

	return sendPacketEasy(packetType, player->getSocket()->getAddress(), sourceBitStream, priority, reliability, orderingChannel, broadCast);
}

uint32_t Network::sendRPC(unsigned short rpcid, const RakNet::SystemAddress destAddress, RakNet::BitStream* sourceBitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool broadCast)
{
	RakNet::BitStream bitStream;

	bitStream.Write(rpcid);

	if (sourceBitStream != NULL)
		bitStream.Write(reinterpret_cast<char*>(sourceBitStream->GetData()), sourceBitStream->GetNumberOfBytesUsed());

	return sendPacketEasy(PacketType::ePacketType::PACKET_RPC, destAddress, &bitStream, priority, reliability, orderingChannel, broadCast);
}

uint32_t Network::sendPlayerRPC(unsigned short rpcid, unsigned int playerid, RakNet::BitStream* sourceBitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool broadCast)
{
	Player* player = getPlayerFromPlayerId(playerid);

	if (player == NULL || player->getSocket()->getState() != ClientSocketInfo::eClientConnectionState::CONNECTED)
		return 0;

	return sendRPC(rpcid, player->getSocket()->getAddress(), sourceBitStream, priority, reliability, orderingChannel, broadCast);
}

void Network::Network::sendBroadcastRPC(unsigned short rpcid, RakNet::BitStream* sourceBitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool broadCast)
{
	Player* player = NULL;

	for (std::map<unsigned int, Player*>::iterator it = players.begin(); it != players.end(); ++it)
	{
		player = it->second;

		if (player == NULL || player->getSocket()->getState() != ClientSocketInfo::eClientConnectionState::CONNECTED)
			continue;

		sendRPC(rpcid, player->getSocket()->getAddress(), sourceBitStream, priority, reliability, orderingChannel, broadCast);
	}
}

void Network::closeConnectionEasy(const RakNet::SystemAddress& destAddress)
{
	return raknetPeer->CloseConnection(destAddress, false);
}
