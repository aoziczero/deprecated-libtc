#include "stdafx.h"
#include "simple_encoder.hpp"
#include "tc.common/datetime.hpp"
#include "factory.hpp"

namespace tc {
namespace log {

simple_encoder::simple_encoder( void ) {

}

simple_encoder::~simple_encoder( void ) {

}

const char* simple_encoder::name( void ) {
	return simple_encoder::class_name();
}

bool simple_encoder::encode( const record& record
			, tc::buffer::byte_buffer<>& out )
{
	out.clear();
	out.reserve( strlen(record.tag.name) 
			+ strlen(record.tag.file) 
			+ strlen(record.tag.function) 
			+ strlen(record.message)+ 1024);
	tc::datetime dt(record.ts + tc::timespan::localtime_offset());
	int len = snprintf( reinterpret_cast<char*>(out.wr_ptr()) , out.space()
			, "[%04d-%02d-%02d %02d:%02d:%02d][%s][%s][%s][%s:%s:%d]\r\n"
			, dt.value().year , dt.value().month  , dt.value().day 
			, dt.value().hour , dt.value().minute , dt.value().second 
			, record.type_acronym()
			, record.tag.name , record.message , record.tag.file , record.tag.function , record.tag.line );
	out.wr_ptr(len+1);
	return true;
}

const char* simple_encoder::class_name( void ) {
	return "simple_encoder";
}

}}
