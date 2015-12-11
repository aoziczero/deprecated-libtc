#include "stdafx.h"
#include "registry.hpp"
#include "factory.hpp"

namespace tc { namespace log {

tc::log::encoder* registry::singleton_encoder( const std::string& name ) {
	if ( _encoders.find( name ) != _encoders.end() ) {
		return _encoders[name];
	}
	return nullptr;
}

tc::log::writer* registry::singleton_writer( const std::string& name ) {
	if ( _writers.find( name ) != _writers.end() ) {
		return _writers[name];
	}
	return nullptr;

}

void registry::register_encoder( const std::string& name , tc::log::encoder* e ) {
	_encoders[name] = e;
}

void registry::register_writer( const std::string& name , tc::log::writer* e ) {
	_writers[name] = e;
}


registry& registry::instance( void ){
	static registry ins;
	return ins;
}

registry::registry( void ) {

}

registry::~registry( void ) {

}



}}
