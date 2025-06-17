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

    log& setup::log_get(){
        return *_log;
    }

    void setup::log_set(std::unique_ptr<log> log) {
            _log = std::move(log);
    }
}

