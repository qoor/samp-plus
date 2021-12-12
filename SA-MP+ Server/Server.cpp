#include "StdInc.h"

#include "SharedUtil.hpp"

Network* g_pNetwork;

Server::Server()
{
	settings = new Settings("server.cfg");
	settings->getParamValue("bind");
	network = new Network(getListeningAddress(), getListeningPort() + 1, getMaxPlayers());
	g_pNetwork = network;
	game = new Game();
	game->start();
}

Server::~Server()
{
	delete game;
}

std::string Server::getListeningAddress()
{
	if (settings->isValidParam("bind"))
		return settings->getParamValue("bind");

	return "";
}

unsigned short Server::getListeningPort()
{
	return std::stoi(settings->getParamValue("port"));
}

unsigned short Server::getMaxPlayers()
{
	return std::stoi(settings->getParamValue("maxplayers"));
}

void Server::doPulse()
{
	network->doPulse();
	game->doPulse();
}