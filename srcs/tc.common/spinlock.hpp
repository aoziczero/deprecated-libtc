#ifndef __tc_threading_spinlock_h__
#define __tc_threading_spinlock_h__

#include "tc.common/tc.hpp"

#if defined( TC_WIN32 )

#elif defined( TC_APPLE )
#include <libkern/OSAtomic.h>
#else
#include <pthread.h>
#endif

namespace tc {
namespace threading {

/*!
*  \class  spinlock
*  \brief  spinlock wrapper
*/
class spinlock {
public:
	spinlock(void);
	~spinlock(void);

	void lock(void);
	void unlock(void);
	bool trylock(void);

	/*!
	*  \class  guard
	*  \bried  raii lock guard
	*/
	class guard {
	public:
		guard(spinlock& lock)
			: _lock(lock){
			_lock.lock();
		}

		~guard(void) {
			_lock.unlock();
		}
	private:
		spinlock& _lock;
	};

private:
#if defined( TC_WIN32 )
	CRITICAL_SECTION _lock;
#elif defined( TC_APPLE )
	OSSpinLock _lock;
#else
	pthread_spinlock_t _lock;
#endif
};

}}

#endif
