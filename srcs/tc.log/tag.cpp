#include "stdafx.h"
#include "tag.hpp"

namespace tc{
namespace log{

tag::tag( const char* t 
			, const char* file  
			, const char* function 
			, const int line )
	: name(t) , file(file) , function(function) , line(line)
{
}

}}
