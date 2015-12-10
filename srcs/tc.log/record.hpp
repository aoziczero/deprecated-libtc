#ifndef __tc_log_record_h__
#define __tc_log_record_h__

#include <tc.common/bit.hpp>
#include <tc.common/timestamp.hpp>
#include <tc.common/threading.hpp>
#include <tc.log/tag.hpp>

namespace tc { namespace log {

enum type {
	trace = tc::tmp::bit(0) ,
	debug = tc::tmp::bit(1) , 
	info  = tc::tmp::bit(2) , 
	warn  = tc::tmp::bit(3) , 
	error = tc::tmp::bit(4) , 
	fatal = tc::tmp::bit(5) , 
	all = trace|debug|info|warn|error|fatal ,
	off = 0,
};

struct record{
	log::type type;
	tc::timestamp ts;		
	tc::threading::thread_id tid;
	const tc::log::tag& tag;
	char message[4096];

	record( tc::log::type type ,  const tc::log::tag& tag );
	~record( void );

	const char* type_acronym( void ) const ;
};

}}

#endif
