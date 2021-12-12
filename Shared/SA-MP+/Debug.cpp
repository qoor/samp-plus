#include "StdInc.h"
#include "Debug.h"

#include <ctime>
#include <cstdarg>

std::ofstream Debug::file;

void Debug::initialize(std::string path)
{
	if (file.is_open() || path.length() == 0)
		return;

	file.open(path, std::ios::app);
}

void Debug::write(const char* format, ...)
{
	if (!file.is_open())
		return;

	time_t time = std::time(0);
	tm* localTime = std::localtime(&time);
	char timeBuffer[24];
	char buffer[2048];
	va_list args;
	std::string bufferString;

	sprintf_s(timeBuffer, sizeof(timeBuffer), "[%04d/%02d/%02d %02d:%02d:%02d] ",
		localTime->tm_year + 1900, localTime->tm_mon + 1, localTime->tm_mday,
		localTime->tm_hour + 1, localTime->tm_min + 1, localTime->tm_sec + 1);

	bufferString.append(timeBuffer);

	va_start(args, format);
	vsnprintf_s(buffer, sizeof(buffer), format, args);
	va_end(args);

	bufferString.append(buffer);
	bufferString.append("\n");

	file.write(bufferString.c_str(), bufferString.size());
	file.flush();
}

void Debug::finalize()
{
	if (!file.is_open())
		return;

	file.close();
}
