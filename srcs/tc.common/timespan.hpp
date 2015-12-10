#ifndef __tc_time_timespan_h__
#define __tc_time_timespan_h__

#include <tc.common/tc.hpp>

namespace tc {

class timestamp;
/*!
*	\class timespan
*	\author	tk
*/
class timespan {
public:
	timespan( void );
	explicit timespan( const s64 delta );
	timespan( const timespan& rhs );
	timespan& operator=( const timespan& rhs );
	
	~timespan( void );

public:
	bool operator==( const timespan& rhs ) const;
	bool operator!=( const timespan& rhs ) const;
	bool operator> ( const timespan& rhs ) const;
	bool operator>=( const timespan& rhs ) const;
	bool operator< ( const timespan& rhs ) const;
	bool operator<=( const timespan& rhs ) const;
public:
	timespan operator+( const timespan& rhs ) const;
	timespan operator-( const timespan& rhs ) const;
	timespan operator*( const int times) const;
	timespan operator/( const int times) const;

	timespan& operator+=( const timespan& rhs ) ;
	timespan& operator-=( const timespan& rhs ) ;
	timespan& operator*=( const int times) ;
	timespan& operator/=( const int times) ;
	
	s64 operator/( const timespan& rhs ) const;
	timespan operator-( void ) const;
	timestamp operator+( const timestamp& rhs ) const;
public:
	s64 total_days( void ) const;
	s64 total_hours( void ) const;
	s64 total_minutes( void ) const;
	s64 total_seconds( void ) const;
	s64 total_milliseconds( void ) const;
	s64 total_microseconds( void ) const;
public:
	static timespan days( s64 c );
	static timespan hours( s64 c );
	static timespan minutes( s64 c );
	static timespan seconds( s64 c );
	static timespan milliseconds( s64 c );
	static timespan microseconds( s64 c );

	static timespan localtime_offset(void);
	static void localtime_offset(const timespan& ts);
private:
	s64 _delta;
};

}

#endif
