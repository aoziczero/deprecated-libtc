#include "stdafx.h"
#include "spinlock.hpp"

namespace tc {
namespace threading {


#if defined( TC_WIN32 )

spinlock::spinlock(void) {
	BOOL ret = InitializeCriticalSectionAndSpinCount(&_lock, 4000);
}

spinlock::~spinlock(void) {
	DeleteCriticalSection(&_lock);
}

void spinlock::lock(void) {
	EnterCriticalSection(&_lock);
}

void spinlock::unlock(void) {
	LeaveCriticalSection(&_lock);
}

bool spinlock::trylock(void) {
	return TryEnterCriticalSection(&_lock) == TRUE;
}

#elif defined( TC_APPLE )

spinlock::spinlock(void) {
	_lock = OS_SPINLOCK_INIT;
}

spinlock::~spinlock(void) {
}

void spinlock::lock(void) {
	OSSpinLockLock(&_lock);
}

void spinlock::unlock(void) {
	OSSpinLockUnlock(&_lock);
}

bool spinlock::trylock(void) {
	return OSSpinLockTry(&_lock);
}

#else

spinlock::spinlock(void) {
	pthread_spin_init(&_lock, PTHREAD_PROCESS_PRIVATE);
}

spinlock::~spinlock(void) {
	pthread_spin_destroy(&_lock);
}

void spinlock::lock(void) {
	pthread_spin_lock(&_lock);
}

void spinlock::unlock(void) {
	pthread_spin_unlock(&_lock);
}

bool spinlock::trylock(void) {
	return  pthread_spin_trylock(&_lock) == 0;
}

#endif


}
}