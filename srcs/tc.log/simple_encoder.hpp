#ifndef __tc_log_simple_encoder_h__
#define __tc_log_simple_encoder_h__

#include <tc.log/encoder.hpp>

namespace tc {
namespace log {

class simple_encoder : public tc::log::encoder {
public:
	simple_encoder( void );
	virtual ~simple_encoder( void );
	virtual const char* name( void );
	virtual bool encode( const record& r 
			, tc::buffer::byte_buffer<>& out );
};

}}


#endif
