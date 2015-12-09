#include "stdafx.h"
#include "logger.hpp"
#include <stdarg.h>

tc::log::logger::logger(void)
{
}

tc::log::logger::~logger(void)
{
}

std::string tc::log::logger::trace( const char * tag, const char * msg, ...)
{
	va_list args;
	va_start(args, msg);
	char m[2048];
#if defined( TC_WIN32 )
	_vsnprintf_s(m, 2048, msg, args);
#else
	vsnprintf(m, 2048, msg, args);
#endif
	va_end(args);
	std::string rm;
	rm += tag;
	rm += " ";
	rm += m;
	rm += " ";
	return rm;
}
std::string tc::log::logger::trace( const file_function_line& ffl
		, const char * tag, const char * msg, ...)
{
	va_list args;
	va_start(args, msg);
	char m[2048];
#if defined( TC_WIN32 )
	_vsnprintf_s(m, 2048, msg, args);
#else
	vsnprintf(m, 2048, msg, args);
#endif
	va_end(args);
	std::string rm;
	rm += ffl.file;
	rm += " ";
	rm += ffl.function;
	rm += " ";
	rm += tag;
	rm += " ";
	rm += std::to_string(ffl.line);	
	rm += " ";
	rm += m;
	rm += " ";
	return rm;
}
