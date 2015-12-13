#ifndef __tc_log_xml_context_h__
#define __tc_log_xml_context_h__

#include <tc.log/context.hpp>

namespace tc {
namespace log {

class logger;
class xml_context : public context{
public:
	xml_context( const std::string& xml );
	virtual ~xml_context( void );
	virtual log::logger& logger(const std::string& name);
	log::logger* load_logger_from_config(const std::string& name);
public:
	std::vector< log::logger* > _loggers;
	std::map< std::string, context::logger_config* > _configs;
};

}}

#endif
