// tc.common.test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#pragma comment( lib ,"gtest")


int main( int argc , char* argv[] )
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

