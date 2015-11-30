#ifndef __tc_buffer_rc_block_h__
#define __tc_buffer_rc_block_h__

#include <tc.common/tc.hpp>

namespace tc { namespace buffer {

/*!
 * \brief
 * \author tk
 * \date 20151130
 * \detail
 */
class rc_block {
public:
	rc_block( void );

	rc_block( const tc::size_t sz );

	rc_block( const rc_block& rhs );

	rc_block( rc_block&& rhs );

	rc_block& operator=( const rc_block& rhs );

	rc_block& operator=( rc_block&& rhs );

	~rc_block( void );

	u8* base( void ) const ;

	tc::size_t size( void ) const;

	void reserve( const tc::size_t sz );

	void cleanup( void );

	void swap( rc_block& rhs );

	void add_ref( void );
	void release( void );
private:
	u8* _base;
	tc::size_t _size;
};

}}

#endif
