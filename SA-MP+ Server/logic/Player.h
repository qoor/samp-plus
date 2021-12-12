#pragma once

class Player : public Ped
{
private:
	unsigned short pluginVersion;
	std::string pluginVersionString;
	bool joined;

	RakNet::SystemAddress playerSocket;
	std::string ipString;

	unsigned char blurLevel;

	class PlayerManager* playerManager;

public:
	Player(PlayerManager* playerManager, unsigned int playerid, const RakNet::SystemAddress& socket);
	~Player();

	void doPulse();

	void unlink();

	bool isJoined() { return joined; }
	void setJoined() { joined = true; }

	RakNet::SystemAddress& getSocket() { return playerSocket; }
	const char* getSourceIP();
	unsigned short getSourcePort() { return playerSocket.GetPort(); }

	uint send(const Packet& packet);

	unsigned char getBlurLevel() { return blurLevel; }
	void setBlurLevel(unsigned char blurLevel) { this->blurLevel = blurLevel; }
};
