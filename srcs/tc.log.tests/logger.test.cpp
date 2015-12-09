#include "stdafx.h"

#include "tc.log/logger.hpp"
#include <thread>

TEST(logger, trace) {
	tc::log::logger logger;
	std::string msg = logger.trace(TC_FFL, "Tag" , "Msg %d", 1);
	gout << msg << gendl;
}
