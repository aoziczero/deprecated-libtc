#include "stdafx.h"
#include "threading.hpp"

namespace tc { namespace threading{

thread_id current_thread_id(void){
#if defined(TC_WIN32)
	return GetCurrentThreadId();
#else
	return pthread_self();
#endif
}

}}


