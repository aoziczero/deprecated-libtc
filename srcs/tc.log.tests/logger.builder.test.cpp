#include "stdafx.h"
#include "tc.log/logger.hpp"
#include "tc.log/simple_encoder.hpp"
#include "tc.log/registry.hpp"
#include "tc.log/factory.hpp"
#include "tc.log/context.hpp"
#include "tc.log/xml_context.hpp"
#include <thread>


TEST(logger, builder) {
	tc::log::context::instance(new tc::log::xml_context(""));

	tc::log::logger& logger = tc::log::context::instance().logger("");


	logger.trace( log_tag("Tag") , "Msg %d", 42 );
	logger.debug( log_tag("Tag") , "Msg %d", 42 );
	logger.info( log_tag("Tag") , "Msg %d", 42 ); 
	logger.warn( log_tag("Tag") , "Msg %d", 42 ); 
	logger.error( log_tag("Tag") , "Msg %d", 42 );
	logger.fatal( log_tag("Tag") , "Msg %d", 42 );
}



