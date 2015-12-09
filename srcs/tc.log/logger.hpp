#ifndef __tc_log_logger_h__
#define __tc_log_logger_h__

#include <tc.log/file_function_line.hpp>

namespace tc {
namespace log {

class logger {
public:
	logger(void);
	~logger(void);

	std::string trace( const file_function_line& ffl , const char* tag, const char* msg, ...);
	std::string trace( const char* tag, const char* msg, ...);
private:

};

}
}

#endif
