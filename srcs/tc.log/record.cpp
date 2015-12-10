#include "stdafx.h"
#include "record.hpp"

namespace tc { namespace log {

const char* record::type_acronym( void ) const {
	switch( type ) {
	case log::trace: return "T";
	case log::debug: return "D";
	case log::info: return "I";
	case log::warn: return "W";
	case log::error: return "E";
	case log::fatal: return "F";
	case log::all: return "A";
	default:
		return "!";
	}
	return "?";
}

record::record( tc::log::type type ,  const tc::log::tag& tag )
	: type(type)
	, tag(tag)
	, ts(tc::timestamp::now())  
	, tid(tc::threading::current_thread_id())
{
}

record::~record( void ) {
}

}}
