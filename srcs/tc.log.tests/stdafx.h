// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#if defined( _WIN32 )
#pragma once

#pragma warning( disable : 4091 )
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN         
#define NOMINMAX
#include <WinSock2.h>
#include <MSWSOCK.h>
#include <WS2tcpip.h>
#include <windows.h>
#include <winbase.h>
#include <tchar.h>
#include <dbghelp.h>
#include <process.h>
#endif

#include <stdint.h>
#include <iostream>
#include <cassert>
#include <cstring>
#include <functional>
#include <algorithm>
#include <vector>
#include <map>
#include <string>
#include <iterator>
#include <ctime>
#include <system_error>

#include <gtest/gtest.h>
#include <tc.common/tc.hpp>
#include <tc.log/writer.hpp>

// TODO: reference additional headers your program requires here


namespace testing
{
	namespace internal
	{
		enum GTestColor {
			COLOR_DEFAULT,
			COLOR_RED,
			COLOR_GREEN,
			COLOR_YELLOW
		};
		extern void ColoredPrintf(GTestColor color, const char* fmt, ...);
	}
}
#define gprintf(...)  do {\
testing::internal::ColoredPrintf(\
	testing::internal::COLOR_GREEN, "[   USER   ] "); \
testing::internal::ColoredPrintf(\
	testing::internal::COLOR_YELLOW, __VA_ARGS__); } while(0)

class gendl_impl {
};

class gout_impl {
public:
	gout_impl& operator<< (const std::string& msg) {
		_message += msg;
		return *this;
	}

	gout_impl& operator<< (const int& val) {
		_message += std::to_string(val);
		return *this;
	}

	gout_impl& operator<< (const std::size_t& val) {
		_message += std::to_string(val);
		return *this;
	}
	gout_impl& operator<< (const gendl_impl&) {
		testing::internal::ColoredPrintf(testing::internal::COLOR_GREEN, "[   USER   ] ");
		testing::internal::ColoredPrintf(testing::internal::COLOR_YELLOW, _message.c_str());
		testing::internal::ColoredPrintf(testing::internal::COLOR_YELLOW, "\n");
		_message.clear();
		return *this;
	}
private:
	std::string _message;
};

static gout_impl gout;
static gendl_impl gendl;


class gtest_console_writer : public tc::log::writer {
public:
	gtest_console_writer(void) {}
	virtual ~gtest_console_writer(void) {}
	virtual const char* name(void) {
		return "gtest_console_writer";
	}
	virtual void write(const tc::log::record& r
		, const tc::buffer::byte_buffer<>& out)
	{
		testing::internal::ColoredPrintf(
			testing::internal::COLOR_GREEN, "[   USER   ] ");
		testing::internal::GTestColor color = testing::internal::COLOR_YELLOW;
		if (r.type == tc::log::debug) {
			color = testing::internal::COLOR_RED;
		}
		if (r.type == tc::log::error) {
			color = testing::internal::COLOR_GREEN;
		}
		testing::internal::ColoredPrintf(color, reinterpret_cast<char*>(out.rd_ptr()));

	}
};