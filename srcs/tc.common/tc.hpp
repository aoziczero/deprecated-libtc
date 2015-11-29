#ifndef __tc_common_h__
#define __tc_common_h__

namespace tc {

	using s8 = int8_t;
	using u8 = uint8_t;

	using s16 = int16_t;
	using u16 = uint16_t;

	using s32 = int32_t;
	using u32 = uint32_t;

	using s64 = int64_t;
	using u64 = uint64_t;


    int init();

#if defined( _WIN32 )
#ifndef TC_WIN32
#define TC_WIN32
#endif

#ifndef TC_ALIGN
#define TC_ALIGN( n ) __declspec(align(n))
#endif

#pragma warning(disable: 4819)

#elif defined(__linux)

#ifndef TC_LINUX
#define TC_LINUX
#endif 

#ifndef TC_ALIGN
#define TC_ALIGN( n ) __attribute__ ((aligned(x)))
#endif

#elif defined(__APPLE__) 
#ifndef TC_APPLE
#define TC_APPLE
#endif

#include "TargetConditionals.h"

#if TARGET_IPHONE_SIMULATOR
	// iOS Simulator
#elif TARGET_OS_IPHONE

#elif TARGET_OS_MAC
	// Other kinds of Mac OS
#else
	// Unsupported platform
#endif

#ifndef TC_ALIGN
#define TC_ALIGN( n ) __attribute__ ((aligned(x)))
#endif

#elif defined(__ANDROID__)
#define TC_ANDROID
#endif

}

#endif
