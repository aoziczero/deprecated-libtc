#include "stdafx.h"
#include <tc.common/datetime.hpp>

void print_timestamp( const tc::timestamp& ts ) {
	tc::datetime dt(ts);
	gprintf("%04d%02d%02d %02d:%02d:%02d %03d %s\n"
			, dt.value().year , dt.value().month  , dt.value().day 
			, dt.value().hour , dt.value().minute , dt.value().second 
			, dt.value().millisecond , dt.value().wday_string()
			);
}

TEST( time , print ) {
	print_timestamp( tc::timestamp(0));
	// utc
	print_timestamp( tc::timestamp::now()); 
	// gmt + 9
	print_timestamp( tc::timestamp::now() + tc::timespan::hours(9)); 
}

