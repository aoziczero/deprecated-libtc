#include "stdafx.h"
#include "simple_block.hpp"

namespace tc { namespace buffer {

simple_block::simple_block( void )
	: _base(nullptr) , _size(0){
}

simple_block::simple_block( const tc::size_t sz )
	: _base(nullptr) , _size(0){
	reserve( sz );
}

simple_block::simple_block( const simple_block& rhs )
	: _base(nullptr) , _size(0){
	reserve( rhs.size() );
	memcpy( base() , rhs.base() , size());
}

simple_block::simple_block( simple_block&& rhs )
	: _base(rhs._base) , _size(rhs._size){
	rhs._base = nullptr;
	rhs._size = 0;
}

simple_block& simple_block::operator=( const simple_block& rhs ){
	if ( _base == rhs.base() )
		return *this;
	cleanup();
	reserve( rhs.size());
	memcpy( base() , rhs.base() , size());
	return *this;
}

simple_block& simple_block::operator=( simple_block&& rhs ){
	if ( _base == rhs.base() )
		return *this;
	swap( rhs );
	rhs.cleanup();
	return *this;
}


simple_block::~simple_block( void ) {
	cleanup();
}

u8* simple_block::base( void ) const {
	return _base;
}

tc::size_t simple_block::size( void ) const {
	return _size;
}

void simple_block::reserve( const tc::size_t sz ) {
	if ( sz > _size ) {
		_base = static_cast< u8*>(std::realloc( _base , sz ));
		_size = sz;
	}
}

void simple_block::cleanup( void ){
	if ( _base )
		std::free( _base );
	_base = nullptr;
	_size = 0;
}

void simple_block::swap( simple_block& rhs ) {
	std::swap( _base , rhs._base );
	std::swap( _size , rhs._size );
}

}}
