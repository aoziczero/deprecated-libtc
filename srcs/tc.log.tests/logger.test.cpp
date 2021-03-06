#include "stdafx.h"
#include "tc.log/logger.hpp"
#include "tc.log/simple_encoder.hpp"
#include "tc.log/registry.hpp"
#include "tc.log/factory.hpp"
#include <thread>


TEST(logger, trace) {
	tc::log::logger logger;

	std::string encoder = tc::log::simple_encoder::class_name();
	std::string writer = "gtest_console_writer";

	logger.add_encoder(tc::log::registry::instance().encoder(encoder));
	logger.add_writer(encoder,
				tc::log::registry::instance().writer(writer));
	
	logger.disable(tc::log::debug);
	logger.disable(tc::log::trace);
	logger.trace( log_tag("Tag") , "Msg %d", 42 );
	logger.debug( log_tag("Tag") , "Msg %d", 42 );
	logger.info( log_tag("Tag") , "Msg %d", 42 ); 
	logger.warn( log_tag("Tag") , "Msg %d", 42 ); 
	logger.error( log_tag("Tag") , "Msg %d", 42 );
	logger.fatal( log_tag("Tag") , "Msg %d", 42 );
}



