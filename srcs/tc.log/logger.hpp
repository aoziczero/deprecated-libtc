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

	void add_encoder( tc::log::encoder* e );
	void add_writer( const char* encoder_name , tc::log::writer* w );
private:
	tc::threading::spinlock _lock;		
	struct sink {
		tc::log::encoder* encoder;
		std::vector< tc::log::writer* > writers;
		sink( tc::log::encoder* e );
	};
	std::map< std::string , sink* > _sinks;
};

}
}

#endif
