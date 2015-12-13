#include "stdafx.h"
#include "registry.hpp"
#include "factory.hpp"
#include "logger.hpp"
#include "tinyxml2/tinyxml2.h"

namespace tc { namespace log {

tc::log::encoder* registry::encoder( const std::string& id ) {
	tc::threading::spinlock::guard guard(_lock);
	if ( _encoders.find( id ) != _encoders.end() ) {
		return _encoders[id];
	}
	return nullptr;
}

tc::log::writer* registry::writer( const std::string& id ) {
	tc::threading::spinlock::guard guard(_lock);
	if ( _writers.find( id ) != _writers.end() ) {
		return _writers[id];
	}
	return nullptr;
}

void registry::encoder(const std::string& id,  tc::log::encoder* e ) {
	tc::threading::spinlock::guard guard(_lock);
	_encoders[id] = e;
}

void registry::writer(const std::string& id , tc::log::writer* w ) {
	tc::threading::spinlock::guard guard(_lock);
	_writers[id] = w;
}

tc::log::logger* registry::logger(const std::string& id) {
	tc::threading::spinlock::guard guard(_lock);
	if (_loggers.find(id) != _loggers.end()) {
		return _loggers[id];
	}
	return nullptr;
}
void registry::logger(const std::string& id , tc::log::logger* logger) {
	tc::threading::spinlock::guard guard(_lock);
	_loggers[id] = logger;
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
