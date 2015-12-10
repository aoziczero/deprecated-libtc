#ifndef __tc_log_writer_h__
#define __tc_log_writer_h__

#include <tc.log/record.hpp>
#include <tc.common/byte_buffer.hpp>

namespace tc {
namespace log {

class writer {
public:
	writer( void );
	virtual ~writer( void );
	virtual const char* name( void ) = 0;
	virtual void write( const record& r ,  const tc::buffer::byte_buffer<>& data ) = 0;
};

}}

#endif
