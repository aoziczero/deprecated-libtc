#include "stdafx.h"
#include "factory.hpp"
#include "simple_encoder.hpp"

namespace tc {
namespace log {


factory& factory::instance(void){
	static factory ins;
	return ins;
}

factory::factory( void ){
	register_encoder( simple_encoder::class_name() , 
			[] (const std::string& )-> tc::log::encoder*  {
				return new simple_encoder();
			});
}

factory::~factory( void ) {
}

tc::log::encoder* factory::create_encoder( const std::string& name
		, const std::string& param ) 
{
	auto it = _encoders.find(name);
	if ( it != _encoders.end() ) {
		return it->second( param );
	}
	return nullptr;
}

tc::log::writer* factory::create_writer( const std::string& name
		, const std::string& param ) 
{
	auto it = _writers.find(name);
	if ( it != _writers.end() ) {
		return it->second( param );
	}
	return nullptr;
}
void factory::register_encoder( const std::string& name 
		, const tc::function< tc::log::encoder* ( const std::string& param ) >& encoder_create )
{
	_encoders[name] = encoder_create;
}
void factory::register_writer( const std::string& name 
		, const tc::function< tc::log::writer* ( const std::string& param ) >& write_create )
{
	_writers[name] = write_create;
}


}}
