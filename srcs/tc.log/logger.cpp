#include "stdafx.h"
#include "logger.hpp"
#include <stdarg.h>

tc::log::logger::logger(void)
{
}

tc::log::logger::~logger(void)
{
}

std::string tc::log::logger::trace(const char * filename, const char * functionname
	, const int line, const char * tag, const char * msg, ...)
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
	rm += filename;
	rm += functionname;
	rm += tag;
	rm += m;
	return rm;
}
