#pragma once

class Server
{
private:
	Settings* settings;
	Network* network;
	Game* game;

public:
	Server();
	~Server();

	std::string getListeningAddress();
	unsigned short getListeningPort();
	unsigned short getMaxPlayers();

	void doPulse();
};
