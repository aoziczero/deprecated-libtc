#include "stdafx.h"
#include "datetime.hpp"

namespace tc {
namespace {

static const int MONTH_TABLE [2][12] = {
	{ 31 , 28 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31 } ,
	{ 31 , 29 , 31 , 30 , 31 , 30 , 31 , 31 , 30 , 31 , 30 , 31 } ,
};

bool is_leap_year( const int year ) {
	if ( (year % 4) == 0 ){
		if ( (year % 100) == 0 ) {
			if( (year % 400 ) == 0 ) {
				return true;
			}
			return false;
		}
		return true;
	}
	return false;
}

int day_counts( const int year ) {
	return is_leap_year( year ) ? 366 : 365;
}

int day_counts( int sty , int endy ) {
	int cnt = 0;
	while ( sty <= endy ) {
		cnt += day_counts(sty);
		++sty;
	}
	return cnt;
}

void convert( const s64 t , datetime::data& dt ) {
	s64 tick = t;
	dt.millisecond = static_cast<s8 >( ( tick / 1000 ) % 1000 );
	// to seconds	
	tick /= ( 1000000 ) ;

	static const int mod_second = 60;
	static const int mod_minute = 60 * 60;
	static const int mod_hour = 60 * 60 * 24;
	static const int div_minute = 60;
	static const int div_hour = 60 * 60;

	dt.second = tick % mod_second;
	dt.minute = static_cast< s8 >((tick % mod_minute) / div_minute );
	dt.hour   = static_cast< s8 >((tick % mod_hour) / div_hour );

	static const int div_days = 60 * 60 * 24;

	int day_count = static_cast<int>(tick / div_days);

	dt.wday = static_cast< datetime::day_of_week>( ( day_count + 4 ) % 7);
	dt.year = 1970;

	while ( true ) {
		int dc = day_counts( dt.year );
		if ( day_count < dc ) 
			break;
		++dt.year;
		day_count -= dc;
	}
	int mi = is_leap_year( dt.year ) ? 1 : 0;
	dt.month = 0;
	while ( true ) {
		if ( day_count < MONTH_TABLE[mi][dt.month] ) {
			break;
		}
		day_count -= MONTH_TABLE[mi][dt.month] ;
		dt.month += 1;
	}
	dt.month += 1;
	dt.day = day_count + 1;
}

}

datetime::datetime( void )
{
	convert( tc::timestamp::now().tick() , _data );
}

datetime::datetime( const tc::timestamp& ts )
{
	convert( ts.tick() , _data );
}

datetime& datetime::operator=( const tc::timestamp& ts ){
	convert( ts.tick() , _data );
	return *this;
}

const char* datetime::data::wday_string(void) const {
	static const char* wdays[] =
	{
		"sunday" , "monday" , "tuesday" , "wednesday" , "tuesday" , "friday" , "saturday" 
	};
	return wdays[wday];
}

}
