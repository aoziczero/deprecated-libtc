#include "stdafx.h"
#include "rc_block.hpp"
#include <atomic>

namespace tc { namespace buffer {

rc_block::rc_block( void )
	: _base(nullptr) , _size(0){
}

rc_block::rc_block( const tc::size_t sz )
	: _base(nullptr) , _size(0){
	reserve( sz );
	add_ref();
}

rc_block::rc_block( const rc_block& rhs )
	: _base(rhs._base) , _size(rhs._size){
	add_ref();
}

rc_block::rc_block( rc_block&& rhs )
	: _base(rhs._base) , _size(rhs._size){
	rhs._base = nullptr;
	rhs._size = 0;
}

rc_block& rc_block::operator=( const rc_block& rhs ){
	rc_block temp( rhs );
	swap(temp);
	return *this;
}

rc_block& rc_block::operator=( rc_block&& rhs ){
	rc_block temp( std::move(rhs));
	swap(temp);
	return *this;
}

rc_block::~rc_block( void ) {
	cleanup();
}

u8* rc_block::base( void ) const {
	return _base;
}

tc::size_t rc_block::size( void ) const {
	return _size;
}

void rc_block::reserve( const tc::size_t sz ) {
	if ( sz > _size ) {
		std::atomic<tc::size_t>* rc = 
			reinterpret_cast< std::atomic<tc::size_t>* >(
					std::malloc( sizeof( std::atomic<tc::size_t> ) + sz ));
		rc->store(1);
		u8* new_base = reinterpret_cast< u8* > ( rc + 1 );

		if ( _base ) {
			memcpy( new_base , _base , _size );
		} 
		release();
		_base = new_base;
		_size = sz;
	}
}

void rc_block::cleanup( void ){
	if ( _base )
		release();
}

void rc_block::swap( rc_block& rhs ) {
	std::swap( _base , rhs._base );
	std::swap( _size , rhs._size );
}

void rc_block::add_ref( void ) {
	if ( _base == nullptr )
		return;
	std::atomic<tc::size_t>* rc = reinterpret_cast<std::atomic<tc::size_t>*>(_base) -1;
	rc->fetch_add(1);
}

void rc_block::release( void ) {
	if ( _base == nullptr )
		return;
	std::atomic<tc::size_t>* rc = reinterpret_cast<std::atomic<tc::size_t>*>(_base) -1;
	if ( rc->fetch_sub(1) == 1 ) {
		std::free( rc );
	}
}

int rc_block::ref_count(void){
	if ( _base == nullptr )
		return 0;
	std::atomic<tc::size_t>* rc = reinterpret_cast<std::atomic<tc::size_t>*>(_base) -1;
	return rc->load();
}

}}
