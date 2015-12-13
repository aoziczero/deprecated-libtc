#include "stdafx.h"
#include "xml_context.hpp"
#include "logger.hpp"
#include "registry.hpp"
#include "factory.hpp"

namespace tc {
namespace log {

xml_context::xml_context(const std::string& xml) {
	// 
	if (_configs.find("logger") == _configs.end()) {
		logger_config* lc = new logger_config();
		lc->levels = tc::log::all;
		_configs["logger"] = lc;
	}
}

xml_context::~xml_context( void ) {
}

log::logger* xml_context::load_logger_from_config(const std::string& name) {
	if (_configs.find(name) != _configs.end()) {
		context::logger_config* cfg = _configs[name];
		log::logger* logger = new log::logger();
		logger->levels() = cfg->levels;
		for each(context::sink_config* scfg in cfg->sinks) {
			log::encoder* encoder = nullptr;
			if (scfg->encoder.source == "factory") {
				encoder = tc::log::factory::instance().create_encoder(scfg->encoder.id, scfg->encoder.param);
			} else {
				encoder = tc::log::registry::instance().encoder(scfg->encoder.id);
				if (encoder == nullptr) {
					encoder = tc::log::factory::instance().create_encoder(scfg->encoder.id, scfg->encoder.param);
					if (encoder) {
						tc::log::registry::instance().encoder(scfg->encoder.id , encoder);
					}
				}
			}
			if (encoder) {
				logger->add_encoder(encoder);
				for each(const context::config& cfg in scfg->writers) {
					tc::log::writer* writer = nullptr;
					if (cfg.source == "factory") {
						writer = tc::log::factory::instance().create_writer(cfg.id, cfg.param);
					} else {
						writer = tc::log::registry::instance().writer(cfg.id);
						if (writer == nullptr) {
							writer = tc::log::factory::instance().create_writer(cfg.id, cfg.param);
							if (writer) {
								tc::log::registry::instance().writer(cfg.id, writer);
							}
						}
					}
					if (writer) {
						logger->add_writer(encoder->name(), writer);
					}
				}
			}
		}
		tc::log::registry::instance().logger(name, logger);
		return logger;
	}
	return nullptr;
}

log::logger & xml_context::logger(const std::string & name)
{
	log::logger* logger = registry::instance().logger(name);
	if (!logger) {
		logger = load_logger_from_config(name);
	}
	if (logger) {
		return *logger;
	}
	logger = registry::instance().logger("logger");
	if (!logger) {
		logger = load_logger_from_config("logger");
	}
	return *logger;
}


}}
