#include "stdafx.h"
#include "tc.log.hpp"
#include "simple_encoder.hpp"
#include "factory.hpp"
#include "registry.hpp"

bool tc::log::init(void)
{
	std::string name = tc::log::simple_encoder::class_name();
	factory::instance().register_encoder(name
		,  factory::creater_no_param< simple_encoder >() );

	tc::log::registry::instance().encoder( name 
		, tc::log::factory::instance().create_encoder(name, ""));
	return true;
}
