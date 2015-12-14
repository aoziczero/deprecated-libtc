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
#define tc_log_write_forward( ltype , tag , msg )\
	if ( _level & ltype ) {\
		tc::log::record record(ltype,tag);\
		va_list args;\
		va_start(args,msg);\
		int len=tc_vsnprintf(record.message,4096,msg,args);\
		va_end(args);\
		if ( len <= 0 ) \
			return ;\
		return write( record );\
	}\

#endif

tc::log::logger::logger(void)
	: _level( tc::log::all )
{
}

tc::log::logger::~logger(void){
}

void tc::log::logger::trace( const tag& tag, const char * msg, ...){
	tc_log_write_forward( log::trace , tag , msg );	
}

void tc::log::logger::debug( const tag& tag , const char* msg, ...){
	tc_log_write_forward( log::debug , tag , msg );
}

void tc::log::logger::info( const tag& tag , const char* msg, ...){
	tc_log_write_forward( log::info , tag , msg );
}

void tc::log::logger::warn( const tag& tag , const char* msg, ...){
	tc_log_write_forward( log::warn , tag , msg );
}

void tc::log::logger::error( const tag& tag , const char* msg, ...){
	tc_log_write_forward( log::error, tag , msg );
}

void tc::log::logger::fatal( const tag& tag , const char* msg, ...){
	tc_log_write_forward( log::fatal, tag , msg );
}

void tc::log::logger::write( const tc::log::record& record ){
    tc::threading::spinlock::guard guard(_lock);
    auto it = _sinks.begin();
    while ( it != _sinks.end() ) {
        tc::buffer::byte_buffer<> buf(4096);
		auto ps = it->second;
		if ( ps && !ps->writers.empty() ){
			if ( ps->encoder->encode( record , buf )) {
				for ( auto w : ps->writers ) {
					w->write( record ,  buf );
				}
			}
		}
        ++it;
    }
}

void tc::log::logger::add_encoder( const std::shared_ptr<tc::log::encoder>& e ){
    tc::threading::spinlock::guard guard(_lock);
	_sinks[ e->name() ] = std::shared_ptr<sink>(new sink(e));
}

void tc::log::logger::add_writer(const std::string& encoder_name
		, const std::shared_ptr<tc::log::writer>& w ){
	auto it = _sinks.find(encoder_name);
	if ( it != _sinks.end() ) {
		it->second->writers.push_back(w);
	}
}

void tc::log::logger::enable(tc::log::type lt)
{
	_level |= lt;
}
void tc::log::logger::disable(tc::log::type lt)
{
	_level &= ~lt;
}

s32&  tc::log::logger::levels(void) {
	return _level;
}

tc::log::logger::sink::sink( const std::shared_ptr<tc::log::encoder> e)
	: encoder(e)
{
}
