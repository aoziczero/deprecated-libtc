#ifndef __tc_buffer_byte_buffer_h__
#define __tc_buffer_byte_buffer_h__

#include <tc.common/tc.hpp>
#include <tc.common/simple_block.hpp>
#include <tc.common/rc_block.hpp>
#include <tc.common/external_block.hpp>

namespace tc { namespace buffer {

struct position {
	tc::size_t read;
	tc::size_t write;

	position(void);
	position(const position& rhs);
	position& operator=(const position& rhs);
	void swap(position& rhs);
};

template < class Block >
class byte_buffer {
public:
	byte_buffer(void) {
	}

	byte_buffer( const tc::size_t sz )
		: _block(sz)
	{}

	byte_buffer(u8* b, const tc::size_t sz)
		: _block(b, sz)
	{
	}

	byte_buffer(const byte_buffer& rhs)
		: _block(rhs._block)
		, _pos(rhs._pos)
	{
	}

	byte_buffer(byte_buffer&& rhs)
		: _block(std::move(rhs._block))
		, _pos(rhs._pos)
	{
	}

	byte_buffer& operator=(const byte_buffer& rhs) {
		_block = rhs._block;
		_pos = rhs._pos;
		return *this;
	}

	byte_buffer& operator=( byte_buffer&& rhs) {
		_block = std::move(rhs._block);
		_pos = rhs._pos;
		return *this;
	}

	~byte_buffer(void) {

	}
public:
	template < class BlockType >
	byte_buffer(const byte_buffer<BlockType>& rhs)
		: _block(rhs.length())
	{
		write(rhs.rd_ptr(), rhs.length());
	}

	template < class BlockType >
	byte_buffer& operator=(const byte_buffer<BlockType>& rhs) {
		clear();
		_block.reserve(rhs.length());
		write(rhs.rd_ptr(), rhs.length());
	}
public:
	u8* rd_ptr(void) const {
		return _block.base() + _pos.read;
	}

	tc::int_t rd_ptr(const tc::int_t move ) {
		tc::int_t realmove = 0;
		if (move >= 0) {
			realmove = std::min(move, (tc::int_t)length());
			_pos.read += realmove;
		}
		else {
			realmove = std::max(move, -(tc::int_t)_pos.read);
			_pos.read += realmove;
		}
		return realmove;
	}

	u8* wr_ptr(void) const {
		return _block.base() + _pos.write;
	}

	tc::int_t wr_ptr(const tc::int_t move) {
		tc::int_t realmove = 0;
		if (move >= 0) {
			realmove = std::min(move, (tc::int_t)space());
			_pos.write += realmove;
		}
		else {
			realmove = std::max(move, -(tc::int_t)length());
			_pos.write += realmove;
		}
		return realmove;
	}

	tc::size_t length(void) const {
		return _pos.write - _pos.read;
	}

	tc::size_t space(void) const {
		return _block.size() - _pos.write;
	}
	
	void clear(void) {
		_pos.read = _pos.write = 0;
	}

	void reserve(const tc::size_t sz) {
		_block.reserve(sz);
	}

public:
	tc::size_t read(void* dst, const tc::size_t sz) {
		tc::size_t cpysize = peak(dst, sz);
		rd_ptr(static_cast<int>(cpysize));
		return cpysize;
	}
	tc::size_t peak(void* dst, const tc::size_t sz) {
		tc::size_t cpysize = std::min(sz, length());
		memcpy(dst, rd_ptr(), cpysize);
		return cpysize;
	}
	tc::size_t write(void* src, const tc::size_t sz) {
		tc::size_t cpysize = std::min(sz, space());
		memcpy(wr_ptr(), src, cpysize);
		return wr_ptr(static_cast<int>(cpysize));
	}
public:
	void fit(bool buffer_fit = false) {
		if (buffer_fit) {
			byte_buffer nb(length());
			nb.write(rd_ptr(), length());
			swap(nb);
		} else {
			reserve(_block.size());
			std::size_t len = length();
			memmove(_block.base(), rd_ptr(), len);
			_pos.read = 0;
			_pos.write = len;
		}
	}
	void swap(byte_buffer& rhs) {
		_block.swap(rhs._block);
		_pos.swap(rhs._pos);
	}
private:
	Block _block;
	position _pos;
};

}}

#endif
