#ifndef __tc_log_tag_h__
#define __tc_log_tag_h__

#ifndef log_tag 
#define log_tag( t ) tc::log::tag( t , __FILE__ , __FUNCTION__  , __LINE__ )
#endif

namespace tc{
namespace log{

struct tag {
	tag( const char* tag 
			, const char* file = "" 
			, const char* function = "" 
			, const int line = 0 );
	
	const char* name;
	const char* file;
	const char* function;
	const int line;
};

}}

#endif
