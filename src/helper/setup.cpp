#include <string>
#include <algorithm>
#include <memory>

#include "log.hpp"
#include "config.hpp"
#include "setup.hpp"

///////////////////////////////////////////////////////////////////////////////
// 2025, Cole Lamers <colelamers@gmail.com>
// 
// Contains the default object for the project which contains logging 
// capabilities and config initialization.
///////////////////////////////////////////////////////////////////////////////

namespace helper {
    // Constructors
    setup::setup() 
        : _log(std::make_unique<log>()), 
          _config(std::make_unique<config>()) {}

    setup& setup::instance() {
        static setup s;
        return s;
    }

    log& setup::get_log() {
        return *_log;
    }

    config& setup::get_config() {
        return *_config;
    }
}

