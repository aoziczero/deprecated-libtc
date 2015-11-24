#include "stdafx.h"

#include "tc.common/container_of.hpp"

namespace {

	struct list_entry {
		list_entry* prev;
		list_entry* next;
	};

	struct test_container_of {
		void* value;
		list_entry entry;
	};

}

TEST(container_of, get_value) {
	test_container_of tco = { nullptr,  {nullptr,nullptr}};
	list_entry* pentry = &tco.entry;

	

	ASSERT_EQ(tc_offset_of(test_container_of, entry)
		, sizeof(void*));
	ASSERT_EQ(tc_offset_of(test_container_of, entry)
		, tc::offset_of(&test_container_of::entry));

	test_container_of* tco2 = tc_container_of( pentry , test_container_of , entry );

	ASSERT_EQ(tc_container_of(pentry, test_container_of, entry)
		, tc::container_of(pentry, &test_container_of::entry));
	ASSERT_EQ(tc_container_of(pentry, test_container_of, entry)
		, &tco);
}
