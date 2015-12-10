#include "stdafx.h"
#include "tc.log/logger.hpp"
#include "tc.log/simple_encoder.hpp"
#include <thread>

class gtest_console_writer : public tc::log::writer {
public:
	gtest_console_writer( void ) {}
	virtual ~gtest_console_writer( void ) {}
	virtual const char* name(void){
		return "gtest_console_writer";
	}
	virtual void write( const tc::log::record& r 
			, const tc::buffer::byte_buffer<>& out ) 
	{
		testing::internal::ColoredPrintf(
			testing::internal::COLOR_GREEN, "[   USER   ] "); 
		testing::internal::GTestColor color = testing::internal::COLOR_YELLOW;
		if ( r.type == tc::log::debug){
			color = testing::internal::COLOR_RED;
		}
		if ( r.type == tc::log::error ){
			color = testing::internal::COLOR_GREEN;
		}
		testing::internal::ColoredPrintf( color , reinterpret_cast<char*>(out.rd_ptr()) );

	}
};

TEST(logger, trace) {
	tc::log::logger logger;
	tc::log::simple_encoder si;
	gtest_console_writer wr;
	logger.add_encoder(&si);
	logger.add_writer( si.name() , &wr );
	logger.disable(tc::log::debug);
	logger.disable(tc::log::trace);
	logger.trace( log_tag("Tag") , "Msg %d", 42 );
	logger.debug( log_tag("Tag") , "Msg %d", 42 );
	logger.info( log_tag("Tag") , "Msg %d", 42 ); 
	logger.warn( log_tag("Tag") , "Msg %d", 42 ); 
	logger.error( log_tag("Tag") , "Msg %d", 42 );
	logger.fatal( log_tag("Tag") , "Msg %d", 42 );
}
