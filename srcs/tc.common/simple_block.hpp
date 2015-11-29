#ifndef __tc_buffer_simple_block_h__
#define __tc_buffer_simple_block_h__

#include <tc.common/tc.hpp>

namespace tc { namespace buffer {

/*!
 * \brief
 * \author tk
 * \date 20151130
 * \detail
 */
class simple_block {
public:
	/*!
	 * ctor
	 */
	simple_block( void );

	simple_block( const tc::size_t sz );

	simple_block( const simple_block& rhs );

	simple_block( simple_block&& rhs );

	simple_block& operator=( const simple_block& rhs );

	simple_block& operator=( simple_block&& rhs );

	~simple_block( void );

	u8* base( void ) const ;

	tc::size_t size( void ) const;

	void reserve( const tc::size_t sz );

	void cleanup( void );

	void swap( simple_block& rhs );
private:
	u8* _base;
	tc::size_t _size;
};

}}

#endif
