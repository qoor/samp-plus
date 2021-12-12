#pragma once

#include <iostream>
#include <fstream>

class Debug
{
private:
	static std::ofstream file;

	Debug() {}
	~Debug() {}

public:
	static void initialize(std::string path);
	static void write(const char* format, ...);
	static void finalize();
};
