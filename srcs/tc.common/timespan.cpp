#include "stdafx.h"
#include "timespan.hpp"
#include "timestamp.hpp"

namespace tc{
namespace impl{
	static timespan localtime_offset;
}

timespan::timespan( void )
	: _delta(0)
{
}

timespan::timespan( const s64 delta )
	: _delta(delta )
{
}

timespan::timespan( const timespan& rhs )
	: _delta( rhs._delta )
{
}

timespan& timespan::operator=( const timespan& rhs ){
	_delta = rhs._delta;
	return *this;
}

timespan::~timespan( void ){
}

bool timespan::operator==( const timespan& rhs ) const {
	return _delta == rhs._delta;
}
bool timespan::operator!=( const timespan& rhs ) const{
	return _delta != rhs._delta;
}
bool timespan::operator> ( const timespan& rhs ) const{
	return _delta > rhs._delta;
}
bool timespan::operator>=( const timespan& rhs ) const{
	return _delta >= rhs._delta;
}
bool timespan::operator< ( const timespan& rhs ) const{
	return _delta < rhs._delta;
}
bool timespan::operator<=( const timespan& rhs ) const{
	return _delta <= rhs._delta;
}


timespan timespan::operator+( const timespan& rhs ) const {
	return timespan( _delta + rhs._delta );
}
timespan timespan::operator-( const timespan& rhs ) const{
	return timespan( _delta - rhs._delta );
}
timespan timespan::operator*( const int times) const{
	return timespan( _delta * times );
}
timespan timespan::operator/( const int times) const{
	return timespan( _delta / times  );
}

timespan& timespan::operator+=( const timespan& rhs )  {
	_delta += rhs._delta;
	return *this;
}
timespan& timespan::operator-=( const timespan& rhs ) {
	_delta -= rhs._delta;
	return *this;
}
timespan& timespan::operator*=( const int times) {
	_delta *= times;
	return *this;
}
timespan& timespan::operator/=( const int times) {
	_delta /= times;
	return *this;
}
	
s64 timespan::operator/( const timespan& rhs ) const {
	if( rhs._delta == 0 )
		return 0;
	return _delta / rhs._delta;
}
timespan timespan::operator-( void ) const {
	return timespan(-_delta);
}

timestamp timespan::operator+( const timestamp& rhs ) const {
	return rhs + *this;
}

s64 timespan::total_days( void ) const {
	return _delta / (static_cast<s64>(24) * 60 * 60 * 1000 * 1000);
}
s64 timespan::total_hours( void ) const {
	return _delta / (static_cast<s64>(60) * 60 * 1000 * 1000);
}
s64 timespan::total_minutes( void ) const{
	return _delta / (60 * 1000 * 1000);
}
s64 timespan::total_seconds( void ) const{
	return _delta / (1000 * 1000);
}
s64 timespan::total_milliseconds( void ) const{
	return _delta / 1000;
}
s64 timespan::total_microseconds( void ) const{
	return _delta;
}

timespan timespan::days( s64 c ) {
	return timespan( c * 24 * 60 * 60 * 1000 * 1000 );
}

timespan timespan::hours( s64 c ) {
	return timespan( c * 60 * 60 * 1000 * 1000 );
}

timespan timespan::minutes( s64 c ) {
	return timespan( c * 60 * 1000 * 1000 );
}

timespan timespan::seconds( s64 c ) {
	return timespan( c * 1000 * 1000 );
}

timespan timespan::milliseconds( s64 c ) {
	return timespan( c * 1000 );
}

timespan timespan::microseconds( s64 c ) {
	return timespan( c );
}

timespan timespan::localtime_offset(void)
{
	return impl::localtime_offset;
}

void tc::timespan::localtime_offset(const timespan & ts)
{
	impl::localtime_offset = ts;
}

}
