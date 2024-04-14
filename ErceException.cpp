#include "ErceException.h"
#include <sstream>
ErceException::ErceException(int line, const char* file) noexcept
	:
	line (line),
	file (file)
{

}

const char* ErceException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* ErceException::GetType() const noexcept
{
	return "Erce Exception";
}

int ErceException::GetLine() const noexcept
{
	return line;
}

const std::string& ErceException::GetFile() const noexcept
{
	return file;
}

std::string ErceException::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << file << std::endl
		<< "[Line] " << line;
	return oss.str();
}
