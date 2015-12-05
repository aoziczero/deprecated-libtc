#ifndef __tc_buffer_external_block_h__
#define __tc_buffer_external_block_h__

#include <tc.common/tc.hpp>

namespace tc { namespace buffer {

/*!
 * \brief
 * \author tk
 * \date 20151201
 * \detail
 */
class external_block {
public:
	/*!
	 * ctor
	 */
	external_block( u8* b , tc::size_t sz );

	external_block( external_block&& rhs );
	external_block& operator=(external_block&& rhs);

	//external_block(const external_block& rhs);
	//external_block& operator=( const external_block& rhs );


	~external_block( void );

	u8* base( void ) const ;

	tc::size_t size( void ) const;

	void reserve( const tc::size_t sz );

	void cleanup( void );

	void swap( external_block& rhs );
private:
	u8* _base;
	tc::size_t _size;
};

}}

#endif
