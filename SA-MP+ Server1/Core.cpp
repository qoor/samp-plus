#include "Core.h"
#include "Entity.h"

Core* core;

Core::Core()
{
	settings = new Settings("server.cfg");
	network = new Network(getListeningAddress(), getListeningPort() + 1, getMaxPlayers());
	entity = new Entity();
}

std::string Core::getListeningAddress()
{
	if (settings->isValidParam("bind"))
		return settings->getParamValue("bind");

	return "";
}

unsigned short Core::getListeningPort()
{
	return (std::stoi(settings->getParamValue("port")));
}

unsigned short Core::getMaxPlayers()
{
	return (std::stoi(settings->getParamValue("maxplayers")));
}

void Core::update()
{
	network->update();
}
