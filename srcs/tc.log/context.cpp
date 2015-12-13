#include "stdafx.h"
#include "context.hpp"

namespace tc {
namespace log {
namespace {
	context* _instance = nullptr;
}

context::context( void ) {
}

context::~context( void ) {
}

context& context::instance() {
	return *_instance;
}

void context::instance( context* ctx ) {
	if (_instance == ctx)
		return;
	if (_instance) {
		delete _instance;
	}
	_instance = ctx;
}

context::config::config(void) {

}

context::config::config(const context::config& rhs)
	: id(rhs.id), param(rhs.param)
{
}

context::config& context::config::operator=(const context::config& rhs) {
	id = rhs.id;
	param = rhs.param;
	return *this;
}

}}
