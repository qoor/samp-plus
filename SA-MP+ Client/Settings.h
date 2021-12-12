#pragma once

#include <map>

class Settings
{
private:
	std::map<std::string, std::string> paramsMap;
	std::map<std::string, std::string> pluginSettingsMap;

	std::string path;

public:
	Settings();
	bool startCommandLineParsing(LPSTR commands);
	void insertParamData(std::string& subString);
	inline bool isValidParamData(std::string key) { return (paramsMap.find(key) != paramsMap.end()); }
	std::string getParamData(std::string key);

	bool getPluginSettings(std::string path);
	bool savePluginSettings(bool haveFile = true);
	bool isValidSettingData(std::string key) { return (pluginSettingsMap.find(key) != pluginSettingsMap.end()); }
	std::string getSettingDataCore(std::string key);
	void getSettingData(std::string key, std::string& dest) { dest = getSettingDataCore(key); }
	void getSettingData(std::string key, int& dest) { dest = std::stoi(getSettingDataCore(key)); }
	void getSettingData(std::string key, uint& dest) { dest = std::stoul(getSettingDataCore(key)); }
	void getSettingData(std::string key, bool& dest)
	{ 
		if (getSettingDataCore(key).compare("1"))
			dest = true;

		dest = false;
	}
	void getSettingData(std::string key, float& dest) { dest = std::stof(getSettingDataCore(key)); }
	void getSettingData(std::string key, double& dest) { dest = std::stod(getSettingDataCore(key)); }
};
