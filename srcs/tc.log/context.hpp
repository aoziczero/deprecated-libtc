#ifndef __tc_log_context_h__
#define __tc_log_context_h__

#include <tc.log/record.hpp>

namespace tc {
namespace log {

class logger;
class context{
public:
	context( void );
	virtual ~context( void );
	virtual log::logger& logger(const std::string& name) = 0;

	static context& instance(void);
	static void instance(context* ctx);

	struct config {
		std::string id;
		std::string param;
		std::string source;
		config(void);
		config(const config& rhs);
		config& operator=(const config& rhs);
	};

	struct sink_config {
		config encoder;
		std::vector< config > writers;
	};

	struct logger_config {
		int levels;
		std::vector< sink_config* > sinks;
	};
};

}}

#endif
