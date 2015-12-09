#ifndef __tc_log_logger_h__
#define __tc_log_logger_h__

#include <tc.log/tag.hpp>
#include <tc.log/record.hpp>

namespace tc {
namespace log {

class logger {
public:
	logger(void);
	~logger(void);

	std::string trace( const tag& t , const char* msg, ...);
	std::string debug( const tag& t , const char* msg, ...);
	std::string info( const tag& t , const char* msg, ...);
	std::string warn( const tag& t , const char* msg, ...);
	std::string error( const tag& t , const char* msg, ...);
	std::string fatal( const tag& t , const char* msg, ...);
	std::string write( tc::log::type t , const tag& tag , const char* msg , int msg_len );
private:

};

}
}

#endif
