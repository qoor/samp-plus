#include "StdInc.h"

#include "Settings.h"

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>

Settings::Settings()
{
	startCommandLineParsing(GetCommandLineA());
	getPluginSettings("SA-MP_Plus_Setting.ini");
}

bool Settings::startCommandLineParsing(LPSTR commands)
{
	if (std::strlen(commands) == 0)
		return false;

	std::string commandsString(commands), subString;
	size_t pos;

	while ((pos = commandsString.find(" -")) != std::string::npos)
	{
		subString = commandsString.substr(0, pos);
		insertParamData(subString);
		commandsString.erase(0, pos + 2);
	}

	subString = commandsString.substr(0, pos);
	insertParamData(subString);
	
	return true;
}

void Settings::insertParamData(std::string& subString)
{
	size_t pos;
	
	if ((pos = subString.find(' ')) != std::string::npos)
		paramsMap.insert(std::map<std::string, std::string>::value_type(subString.substr(0, pos), subString.substr(pos + 1)));
	else
		paramsMap.insert(std::map<std::string, std::string>::value_type(subString.substr(0, pos), " "));
}

std::string Settings::getParamData(std::string key)
{
	std::map<std::string, std::string>::iterator it = paramsMap.find(key);
	std::string value;

	if (it != paramsMap.end())
		value = it->second;

	return value;
}

bool Settings::getPluginSettings(std::string path)
{
	if (path.size() == 0)
		return false;

	std::ifstream fileStream;
	std::string line, key, value;
	unsigned char delimiter = '=';
	int delimiterPos = std::string::npos;

	this->path = path;

	fileStream.open(path, std::ios::in);

	if (!fileStream.is_open() && !savePluginSettings(false))
		return false;

	while (std::getline(fileStream, line))
	{
		delimiterPos = line.find('=');

		if (delimiterPos == std::string::npos)
			continue;

		key = line.substr(0, delimiterPos);

		if (key.size() == 0)
			continue;

		value = line.substr(delimiterPos + 1, line.size());

		if (value.size() == 0)
			continue;

		Debug::write("key: %s, value: %s", key.c_str(), value.c_str());

		pluginSettingsMap.insert(std::map<std::string, std::string>::value_type(key, value));
	}

	fileStream.close();

	return true;
}

bool Settings::savePluginSettings(bool haveFile)
{
	if (path.size() == 0)
		return false;

	std::ofstream fileStream(path, std::ios::ate);

	if (!fileStream.is_open())
		return false;

	if (!haveFile)
	{
		fileStream << "GrassAndPlants" << '=' << true << std::endl;
		fileStream << "MotionBlur" << '=' << false << std::endl;
		fileStream << "CarNames" << '=' << true << std::endl;
		fileStream << "HudMatchAspectRatio" << '=' << false << std::endl;
		fileStream << "FrameLimit" << '=' << 60 << std::endl;
		fileStream << "HighDetailVehicles" << '=' << false << std::endl;
		//fileStream << "HighDetailPeds" << '=' << false << std::endl;
		fileStream << "FieldOfView" << '=' << 70 << std::endl;
		fileStream << "TyreSmoke" << '=' << true << std::endl;
	}
	else
	{
		for (std::map<std::string, std::string>::iterator it = pluginSettingsMap.begin(); it != pluginSettingsMap.end(); ++it)
			fileStream << it->first << '=' << it->second << std::endl;
	}

	fileStream.flush();
	fileStream.close();

	return true;
}

std::string Settings::getSettingDataCore(std::string key)
{
	if (key.size() > 0)
	{
		std::map<std::string, std::string>::iterator it = pluginSettingsMap.find(key);

		if (it != pluginSettingsMap.end())
			return it->second;
	}

	return std::string("");
}
