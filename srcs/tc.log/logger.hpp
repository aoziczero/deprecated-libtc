#ifndef __tc_log_logger_h__
#define __tc_log_logger_h__

#ifndef TC_FFL
#define TC_FFL __FILE__,__FUNCTION__,__LINE__
#endif

namespace tc {
namespace log {

class logger {
public:
	logger(void);
	~logger(void);

	std::string trace( const char* filename , const char* functionname , const int line
		, const char* tag, const char* msg, ...);
private:

};

}
}

#endif