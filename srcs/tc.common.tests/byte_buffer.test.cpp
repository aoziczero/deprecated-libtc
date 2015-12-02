#include "stdafx.h"
#include <tc.common/byte_buffer.hpp>

TEST( byte_buffer , ctor_other_block_type ) {

	tc::buffer::byte_buffer<tc::buffer::simple_block> block(24);
	int val = 1000;
	ASSERT_EQ(block.write(&val, sizeof(int)), sizeof(int));
	ASSERT_EQ(block.length(), sizeof(int));
	tc::buffer::byte_buffer<tc::buffer::rc_block> block2(block);
	ASSERT_EQ(block2.length(), sizeof(int));
	int val2 = 0;
	ASSERT_EQ(block2.read(&val2, sizeof(int)), sizeof(int));
	ASSERT_EQ(val, val2);

}

TEST(byte_buffer, rc_block_refs) {
	tc::buffer::byte_buffer< tc::buffer::rc_block > buffer(24);
	tc::buffer::byte_buffer< tc::buffer::rc_block > buffer2(buffer);

	ASSERT_EQ(buffer.rd_ptr(), buffer2.rd_ptr());
	buffer2.reserve(buffer2.capacity());
	ASSERT_NE(buffer.rd_ptr(), buffer2.rd_ptr());
}

TEST(byte_buffer, external) {
	char buf1[128];
	char buf2[128];

	tc::buffer::byte_buffer< tc::buffer::external_block > buffer1((u8*)buf1, 128);
	tc::buffer::byte_buffer< tc::buffer::external_block > buffer2((u8*)buf2, 128);

	for (int i = 0; i < 128; ++i) {
		buffer1.write(&i, sizeof(char));
	}

	memcpy(buffer2.wr_ptr(), buffer1.rd_ptr(), buffer1.length());
	buffer2.wr_ptr(buffer1.length());

	ASSERT_EQ(buffer1.length(), buffer2.length());
	ASSERT_EQ(buffer1.length(), 128);
	ASSERT_EQ(0, std::memcmp(buf1, buf2, 128));
}

TEST(byte_buffer, fit) {
	tc::buffer::byte_buffer< tc::buffer::rc_block > buffer1(256);

	for (int i = 0; i < 128; ++i) {
		buffer1.write(&i, sizeof(char));
	}

	for (int i = 0; i < 128; ++i) {
		char val;
		buffer1.read(&val, sizeof(char));
		ASSERT_EQ(val, (char)i);
		ASSERT_EQ(buffer1.space(), 256 - (128 - i));
		buffer1.fit();
	}


}