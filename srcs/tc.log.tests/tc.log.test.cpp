// tc.log.test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <tc.log/tc.log.hpp>
#include <tc.log/factory.hpp>
#include <tc.log/registry.hpp>

#if defined( TC_WIN32 )
#pragma comment( lib ,"gtest")
#pragma comment( lib ,"tc.common.lib")
#pragma comment( lib ,"tc.log.lib")
#endif

#include <tc.common/timespan.hpp>

int main( int argc , char* argv[] )
{
	testing::InitGoogleTest(&argc, argv);
	tc::timespan::localtime_offset(tc::timespan::hours(9));

	tc::log::init();

	const std::string gtest_writer = "gtest_console_writer";

	tc::log::factory::instance().
		register_writer(gtest_writer, tc::log::factory::creater_no_param<gtest_console_writer>());

	tc::log::registry::instance().writer(
		gtest_writer
		, tc::log::factory::instance().create_writer(gtest_writer, ""));


	return RUN_ALL_TESTS();
}

