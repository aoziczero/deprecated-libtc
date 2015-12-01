#include "stdafx.h"
#include "rc_block.hpp"
#include <tc.common/tc.hpp>
#include <atomic>

namespace tc { namespace buffer {

namespace {

union block_header {
	std::atomic<tc::size_t> ref_count;
	void* align;
};

}

rc_block::rc_block( void )
	: _base(nullptr) , _size(0){
}

rc_block::rc_block( const tc::size_t sz )
	: _base(nullptr) , _size(0){
	reserve( sz );
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

void rc_block::reserve(const tc::size_t sz) {
	if (ref_count() != 1) {
		block_header* hdr = reinterpret_cast<block_header*>(
			std::malloc(sizeof(block_header) + sz));
		hdr->ref_count.store(1);
		u8* new_base = tc::payload_cast< block_header > (hdr);
		if (_base) {
			memcpy(new_base, _base, _size);
			release();
		}
		_base = new_base;
		_size = sz;
		return;
	}

	if (sz > _size) {
		block_header* hdr = tc::header_cast<block_header>(_base);
		hdr = reinterpret_cast<block_header*>(
				std::realloc(hdr, sizeof(block_header) + sz));
		_base = tc::payload_cast< block_header > (hdr);
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
	block_header* hdr = tc::header_cast<block_header>(_base);
	hdr->ref_count.fetch_add(1);
}

void rc_block::release( void ) {
	if ( _base == nullptr )
		return;
	block_header* hdr = tc::header_cast<block_header>(_base);
	if (hdr->ref_count.fetch_sub(1) == 1 ) {
		std::free(hdr);
	}
}

int rc_block::ref_count(void){
	if ( _base == nullptr )
		return 0;
	block_header* hdr = tc::header_cast<block_header>(_base);
	return hdr->ref_count.load();
}

}}
