#include "stdafx.h"
#include "tc.common/simple_block.hpp"
#include "tc.common/rc_block.hpp"

TEST( simple_block , ctor ) {

	tc::buffer::simple_block block;
	ASSERT_EQ( block.base() , nullptr );
	ASSERT_EQ( block.size() , 0 );

}

TEST( simple_block , alloc_ctor ){

	tc::buffer::simple_block block(24);

	u8* buffer = block.base();
	ASSERT_NE( buffer , nullptr );
	ASSERT_EQ( block.size() , 24 );

	// mac osx use pool? 24 -> 32 reserve has same buffer
	block.reserve(2048);

	ASSERT_NE( buffer , block.base());
	ASSERT_NE( block.base() , nullptr );
	ASSERT_EQ( block.size() , 2048 );

}

TEST( simple_block , assign ) {
	tc::buffer::simple_block block(24);
	tc::buffer::simple_block block2( block );

	ASSERT_NE( block.base() , block2.base());
	ASSERT_EQ( block.size() , block2.size());

	tc::buffer::simple_block block3( std::move( block2 ));

	ASSERT_EQ( block2.base() , nullptr );
	block2 = std::move( block3 );
	ASSERT_EQ( block3.base() , nullptr );
	block3 = block2;
	ASSERT_NE( block3.base() , nullptr );
}

