#ifndef __tc_log_registry_h__
#define __tc_log_registry_h__

#include <tc.common/spinlock.hpp>

namespace tc { namespace log {
class encoder;
class writer;

/*!
 * \todo 1. define config file format\n
 * 2. implement load function
 */
class registry {
public:
	tc::log::encoder* singleton_encoder( const std::string& name );
	tc::log::writer* singleton_writer( const std::string& name );

	void register_encoder( const std::string& name , tc::log::encoder* e );
	void register_writer( const std::string& name , tc::log::writer* e );

	/*!
	 * init singleton encoders / writers
	 */
	bool load( const std::string& file );
public:
	static registry& instance( void );
private:
	registry( void );
	~registry( void );
private:
	tc::threading::spinlock _lock;
	std::map< std::string , tc::log::encoder* > _encoders;
	std::map< std::string , tc::log::writer* > _writers;

};

}}

#endif
