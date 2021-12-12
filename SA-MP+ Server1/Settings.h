#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <map>

class Settings
{
private:
	std::map<std::string, std::string> paramsMap;

public:
	Settings(const std::string path);
	inline std::string& getParamValue(const std::string key) { return (paramsMap.find(key)->second); }
	inline bool isValidParam(const std::string key) { return (paramsMap.find(key) != paramsMap.end()); }
};
