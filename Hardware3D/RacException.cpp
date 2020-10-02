#include "RacException.h"
#include <sstream>

RacException::RacException(int line, const char* file) noexcept
	:
	line(line),
	file(file)
{}

const char* RacException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* RacException::GetType() const noexcept
{
	return "Rac Exception";
}

int RacException::GetLine() const noexcept
{
	return line;
}

const std::string& RacException::GetFile() const noexcept
{
	return file;
}

std::string RacException::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << file << std::endl
		<< "[Line] " << line;
	return oss.str();
}
