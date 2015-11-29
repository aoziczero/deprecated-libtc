#include "stdafx.h"

#include "tc.common/spinlock.hpp"
#include <thread>

TEST(spinlock, lock) {
	struct thread_context {
		tc::threading::spinlock lock;
		int counter;
	};

	thread_context ctx;
	ctx.counter = 0;

	std::vector< std::thread > threads;

	for (int i = 0; i < 8; ++i) {
		threads.push_back(std::thread([&ctx] {
			for (int x = 0; x < 100000; ++x) {
				tc::threading::spinlock::guard guard(ctx.lock);
				ctx.counter += 1;
			}
		}));
	}
	for (int i = 0; i < 8; ++i) {
		threads[i].join();
	}

	ASSERT_EQ(ctx.counter, 100000 * 8);

}
