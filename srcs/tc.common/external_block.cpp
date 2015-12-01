#include "stdafx.h"
#include "external_block.hpp"

namespace tc { namespace buffer {

external_block::external_block(u8* b, tc::size_t sz)
	: _base(b) , _size(sz){
}


external_block::external_block( external_block&& rhs )
	: _base(rhs._base) , _size(rhs._size){
	rhs._base = nullptr;
	rhs._size = 0;
}


external_block& external_block::operator=( external_block&& rhs ){
	_base = rhs._base;
	_size = rhs._size;
	rhs.cleanup();
	return *this;
}

external_block::~external_block( void ) {
	cleanup();
}

u8* external_block::base( void ) const {
	return _base;
}

tc::size_t external_block::size( void ) const {
	return _size;
}

void external_block::reserve(const tc::size_t)
{
}

void external_block::cleanup( void ){
	_base = nullptr;
	_size = 0;
}

void external_block::swap( external_block& rhs ) {
	std::swap( _base , rhs._base );
	std::swap( _size , rhs._size );
}

}}
