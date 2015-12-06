#include "stdafx.h"
#include <tc.common/function.hpp>

void test_function( void ) {
	gout << "call" << gendl;
}

TEST( tc_function , function_ptr ){
    tc::function< void () > f( &test_function );
    f();
    tc::function< void () > f2(f);
    f2();
    f = test_function;
    f();
    f = [] { gout << "call2" << gendl; };
    gout << "!!" << gendl;
    f();
}

TEST( tc_function , lambda ) {
    tc::function<void ()> f( [] {
            gout<<"Call2!"<<gendl;
            });
    f();
    tc::function<void ()> f2(f);
    f2();
}

int test_return( int ret ){
    return ret;
}

TEST( tc_function , return_val ) {
    tc::function< int (int) > f(&test_return);
    ASSERT_EQ( f(2) , 2 );
    f = [] ( int ret ) {
        return ret + 2;
    };
    ASSERT_EQ( f(2) , 4 );
}

