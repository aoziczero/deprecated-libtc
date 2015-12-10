#ifndef __tc_log_encoder_h__
#define __tc_log_encoder_h__

#include <tc.log/record.hpp>
#include <tc.common/byte_buffer.hpp>

namespace tc {
namespace log {

class encoder {
public:
	encoder( void );
	virtual ~encoder( void );
	virtual const char* name( void ) = 0;
	virtual bool encode( const record& r 
			, tc::buffer::byte_buffer<>& out ) = 0;
};

}}

#endif
