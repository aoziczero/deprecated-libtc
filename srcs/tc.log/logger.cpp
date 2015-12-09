#include "stdafx.h"
#include "logger.hpp"
#include <stdarg.h>
#include "record.hpp"
#include <tc.common/datetime.hpp>

#ifndef tc_vsnprintf
#if defined( TC_WIN32 )
#define tc_vsnprintf( b , bl , msg , arg ) _vsnprintf_s( b , bl , msg , arg )
#else
#define tc_vsnprintf( b , bl , msg , arg ) vsnprintf( b , bl , msg , arg )
#endif
#endif

#ifndef tc_log_write_forward
#define tc_log_write_forward( t )\
	va_list args; \
	va_start(args, msg); \
	char buffer[4096]; \
	int message_len = tc_vsnprintf(buffer,4096, msg, args);\
	va_end(args);\
	if ( message_len < 0 ) \
		return "";\
	message_len += 1;\
	return write( log::trace , tag , buffer , message_len );\

#endif

tc::log::logger::logger(void)
{
}

tc::log::logger::~logger(void)
{
}

std::string tc::log::logger::trace( const tag& tag, const char * msg, ...)
{
	tc_log_write_forward( log::trace );	
}
std::string tc::log::logger::debug( const tag& t , const char* msg, ...);
std::string tc::log::logger::info( const tag& t , const char* msg, ...);
std::string tc::log::logger::warn( const tag& t , const char* msg, ...);
std::string tc::log::logger::error( const tag& t , const char* msg, ...);
std::string tc::log::logger::fatal( const tag& t , const char* msg, ...);


std::string tc::log::logger::write( tc::log::type t 
		, const tag& tag 
		, const char* msg 
		, int msg_len )
{
	log::record* record = record::alloc( log::trace
			, tag.name
			, tag.file 
			, tag.function 
			, tag.line 
			, msg 
			, msg_len );
	char m[4096];
	tc::datetime dt(record->ts + tc::timespan::hours(9));
	snprintf( m , 4096 , "[%04d-%02d-%02d %02d:%02d:%02d][%s][%s][%s][%s:%s:%d]"
			, dt.value().year , dt.value().month  , dt.value().day 
			, dt.value().hour , dt.value().minute , dt.value().second 
			, record->type_acronym()
			, record->tag , record->message , record->file , record->function , record->line );
	record::free(record);
	return std::string(m);
}
