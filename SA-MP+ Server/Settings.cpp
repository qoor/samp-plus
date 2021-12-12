#include "StdInc.h"

Settings::Settings(const std::string path)
{
	std::ifstream file(path);
	std::string lineString;

	while (std::getline(file, lineString))
	{
		std::string key, value;
		std::string::size_type delimiter(lineString.find_first_of(' '));

		if (delimiter != std::string::npos)
		{
			key = lineString.substr(0, delimiter);
			value = lineString.substr(delimiter + 1);
		}
		else
		{
			key = lineString;
			value = "";
		}

		paramsMap.insert(std::map<std::string, std::string>::value_type(key, value));
	}
}
