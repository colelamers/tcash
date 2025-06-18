#include <string>
#include <algorithm>
#include <memory>

#include "log.hpp"
#include "config.hpp"
#include "setup.hpp"

namespace helper {
        // Constructors
    setup::setup() : 
        _log(std::make_unique<log>()), 
        _config(std::make_unique<config>())
    {

    }

    log& setup::get_log(){
        return *_log;
    }

    void setup::set_log(std::unique_ptr<log> lg) {
            _log = std::move(lg);
    }

    config& setup::get_config(){
        return *_config;
    }

    void setup::set_config(std::unique_ptr<config> cfg) {
            _config = std::move(cfg);
    }
}

