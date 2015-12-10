#ifndef __tc_threading_h__
#define __tc_threading_h__

#include <tc.common/tc.hpp>

namespace tc { namespace threading{

#if defined( TC_WIN32 )
using thread_id = int;
#else
using thread_id = pthread_t;
#endif

thread_id current_thread_id(void);

}}


#endif
