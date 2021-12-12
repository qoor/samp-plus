#include "StdInc.h"

#define RECONNECT_TIME 6000
#define CONNECTION_ATTEMPT_COUNT 10U
#define TIMEOUT_TIME 10000U

#include <SA-MP+/RPC.h>
#include <SA-MP+/PacketType.h>

Network::Network(std::string address, std::string port) : raknetPeer(NULL), raknetSocketDescriptor(NULL), raknetSystemAddress(NULL), initialized(false), connected(false), serverHasPlugin(false), reconnectTime(0)
{
	size_t addressSize = address.size();

	if (addressSize > 0)
	{
		serverAddress = new char[addressSize + 1];
		strcpy_s(serverAddress, addressSize + 1, address.c_str());
		serverPort = std::stoi(port) + 1;

		Debug::write("주소: %s\t포트: %d", serverAddress, serverPort);
	}

	raknetPeer = RakNet::RakPeerInterface::GetInstance();
	raknetSocketDescriptor = new RakNet::SocketDescriptor();

	Debug::write("네트워크 접속 준비..");

	if (raknetPeer->Startup(1, raknetSocketDescriptor, 1) == RakNet::StartupResult::RAKNET_STARTED)
	{
		Debug::write("네트워크 접속 준비 됨.");

		initialized = true;
	}
	else
		Debug::write("네트워크 접속 준비 실패.");
}

Network::~Network()
{
	if (raknetPeer == NULL)
		return;

	disconnect();
	
	//RakNet::RakPeerInterface::DestroyInstance(raknetPeer);
}

void Network::tryConnect()
{
	if (!isInitialized())
		return;

	disconnect();

	Debug::write("서버에 SA-MP+ 접속 시도..");

	raknetSystemAddress = new RakNet::SystemAddress(serverAddress, serverPort);

	core->getNetwork()->raknetPeer->Connect(serverAddress, serverPort, SAMP_PLUS_PASSWORD, std::strlen(SAMP_PLUS_PASSWORD), 0, 0, CONNECTION_ATTEMPT_COUNT, 500U, TIMEOUT_TIME);
}

void Network::disconnect()
{
	if (raknetSystemAddress != NULL)
	{
		raknetPeer->CloseConnection(*raknetSystemAddress, true);

		delete raknetSystemAddress;
	}

	connected = false;
}

void Network::update()
{
	if (!isInitialized())
		return;

	if (reconnectTime > 0)
	{
		if (GetTickCount32() - reconnectTime >= RECONNECT_TIME)
		{
			reconnectTime = 0;

			tryConnect();

			return;
		}
	}

	RakNet::Packet* packet;

	for (packet = raknetPeer->Receive(); packet != NULL; raknetPeer->DeallocatePacket(packet), packet = raknetPeer->Receive())
	{
		if (packet->length <= 0)
			continue;

		RakNet::BitStream bitStream(&packet->data[1], packet->length - 1, false);
		Debug::write("받은 패킷: %i, 로컬: %i, 바이트 크기: %i byte(s)", packet->data[0], packet->wasGeneratedLocally, bitStream.GetNumberOfBytesUsed());

		switch (packet->data[0])
		{
		case ePacketType::PACKET_PLAYER_REQUEST_VERSION:
			clientGame->sendJoinData();
			break;

		case ePacketType::PACKET_PLAYER_REGISTERED:
			connected = true;
			serverHasPlugin = true;

			break;

		case ePacketType::PACKET_RPC:
			unsigned short rpcid;

			if (bitStream.Read<unsigned short>(rpcid))
			{
				RPC::update(rpcid, bitStream);

				Debug::write("rpcid: %d 호출 됨.", rpcid);
			}

			break;

		case ePacketType::PACKET_PLAYER_PROPER_DISCONNECT:
			disconnect();
			reconnectTime = GetTickCount32();

			break;

		case ePacketType::PACKET_CONNECTION_REJECTED:
		case ePacketType::PACKET_PLAYER_PROPER_KICK:
			disconnect();

			break;

		case ID_CONNECTION_LOST:
			connected = false;

			if (isServerHasPlugin())
				tryConnect();

			break;
		}
	}
}

uint32_t Network::sendPacket(ePacketType packetType, RakNet::BitStream* sourceBitStream, PacketPriority priority, PacketReliability reliability, char orderingChannel, bool broadCast)
{
	RakNet::BitStream bitStream;

	bitStream.Write(static_cast<unsigned char>(packetType));

	if (sourceBitStream)
		bitStream.Write(reinterpret_cast<char*>(sourceBitStream->GetData()), sourceBitStream->GetNumberOfBytesUsed());

	return raknetPeer->Send(&bitStream, priority, reliability, orderingChannel, *raknetSystemAddress, broadCast);
}
