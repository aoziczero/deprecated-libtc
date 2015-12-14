#ifndef __tc_log_registry_h__
#define __tc_log_registry_h__

#include <tc.common/spinlock.hpp>

#include <memory>

namespace tc { namespace log {
class encoder;
class writer;
class logger;
/*!
 * \todo 1. define config file format\n
 * 2. implement load function
 */
class registry {
public:
	std::shared_ptr<tc::log::encoder>  encoder(const std::string& id);
	void encoder(const std::string& id , const std::shared_ptr<tc::log::encoder>& e );

	std::shared_ptr<tc::log::writer>  writer(const std::string& id);
	void writer(const std::string& id , const std::shared_ptr<tc::log::writer>& e );

	std::shared_ptr<tc::log::logger> logger(const std::string& id);
	void logger(const std::string& id , const std::shared_ptr<tc::log::logger>& logger);
public:
	static registry& instance( void );
private:
	registry( void );
	~registry( void );
private:
	tc::threading::spinlock _lock;
	std::map< std::string, std::shared_ptr<tc::log::encoder> > _encoders;
	std::map< std::string, std::shared_ptr<tc::log::writer> > _writers;
	std::map< std::string, std::shared_ptr<tc::log::logger> > _loggers;
};

}}

#endif
