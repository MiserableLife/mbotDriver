#include "logger.h"

Logger::Logger(std::string path)	: out(path)
{
}
Logger::~Logger()
{
	out.close();
}
template<typename T>
Logger& 
Logger::operator<<(const T& t)
{
	out<<t<<std::endl;
	return *this;
}


