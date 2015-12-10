// tc.log.test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#if defined( TC_WIN32 )
#pragma comment( lib ,"gtest")
#pragma comment( lib ,"tc.common.lib")
#pragma comment( lib ,"tc.log.lib")
#endif


int main( int argc , char* argv[] )
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

