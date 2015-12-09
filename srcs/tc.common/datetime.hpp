#ifndef __tc_datetime_h__
#define __tc_datetime_h__

#include <tc.common/timestamp.hpp>

namespace tc {

class datetime{
public:
	datetime( void );
	datetime( const tc::timestamp& ts );

	datetime& operator=( const tc::timestamp& ts );
public:
	enum day_of_week{
		sun = 0 , mon , tues , wednes , turhs , fri , satur
	};
	struct data {
		s16 year;
		s8  month;
		s8  day;
		s8  hour;
		s8  minute;
		s8  second;
		s8  millisecond; 
		day_of_week wday;

		const char* wday_string(void) const;
	};

	const data& value(void){
		return _data;
	}
private:
	data _data;
};

}

#endif
