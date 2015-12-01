#include "stdafx.h"
#include "tc.common/rc_block.hpp"

TEST( rc_block , ctor ) {

	tc::buffer::rc_block block;
	ASSERT_EQ( block.base() , nullptr );
	ASSERT_EQ( block.size() , 0 );
	ASSERT_EQ( block.ref_count() , 0 );
}

TEST( rc_block , alloc_ctor ){

	tc::buffer::rc_block block(24);

	u8* buffer = block.base();
	ASSERT_NE( buffer , nullptr );
	ASSERT_EQ( block.size() , 24 );
	ASSERT_EQ( block.ref_count() , 1 );

	block.reserve(32);

	ASSERT_NE( buffer , block.base());
	ASSERT_NE( block.base() , nullptr );
	ASSERT_EQ( block.size() , 32 );
	ASSERT_EQ( block.ref_count() , 1 );
}

TEST( rc_block , assign ) {
	tc::buffer::rc_block block(24);
	tc::buffer::rc_block block2( block );

	ASSERT_EQ( block.base() , block2.base());
	ASSERT_EQ( block.size() , block2.size());
	ASSERT_EQ( block.ref_count() , 2 );

	tc::buffer::rc_block block3( std::move( block2 ));

	ASSERT_EQ( block3.ref_count() , 2 );
	ASSERT_EQ( block2.base() , nullptr );
	block2 = std::move( block3 );

	ASSERT_EQ( block3.ref_count() , 0 );
	ASSERT_EQ( block2.ref_count() , 2 );
	
	ASSERT_EQ( block3.base() , nullptr );
	block3 = block2;
	ASSERT_NE( block3.base() , nullptr );
	ASSERT_EQ( block3.ref_count() , 3 );
}

