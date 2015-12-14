#ifndef __tc_log_logger_h__
#define __tc_log_logger_h__

#include <tc.log/record.hpp>
#include <tc.log/encoder.hpp>
#include <tc.log/writer.hpp>
#include <tc.common/spinlock.hpp>

#include <vector>
#include <map>

namespace tc {
namespace log {

class logger {
public:
	logger(void);
	~logger(void);

	void trace( const tag& t , const char* msg, ...);
	void debug( const tag& t , const char* msg, ...);
	void info( const tag& t , const char* msg, ...);
	void warn( const tag& t , const char* msg, ...);
	void error( const tag& t , const char* msg, ...);
	void fatal( const tag& t , const char* msg, ...);
	void write( const tc::log::record& record );

	void add_encoder( const std::shared_ptr<tc::log::encoder>& e );
	void add_writer( const std::string& encoder_name 
			, const std::shared_ptr<tc::log::writer>& w );

	void enable(tc::log::type lt);
	void disable(tc::log::type lt);
	s32& levels(void);
private:
	tc::threading::spinlock _lock;		
	struct sink {
		std::shared_ptr<tc::log::encoder> encoder;
		std::vector< std::shared_ptr<tc::log::writer> > writers;
		sink( const std::shared_ptr<tc::log::encoder> e);
	};
	s32 _level;
	std::map< std::string , std::shared_ptr<sink> > _sinks;
	std::string _name;
};

}
}

#endif
