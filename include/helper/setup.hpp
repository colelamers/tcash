#ifndef SETUP_H
#define SETUP_H

#include <string>
#include <algorithm>

#include "log.hpp"
#include "config.hpp"

namespace helper {
    class setup {
    public:
        // Access singleton instance
        static setup& instance();

        // Delete copy/move operations
        setup(const setup&) = delete;
        setup(setup&&) = delete;
        setup& operator=(const setup&) = delete;
        setup& operator=(setup&&) = delete;

        // Accessors
        log& get_log();
        config& get_config();

    private:
        // Private constructor
        setup();

        std::unique_ptr<log> _log;
        std::unique_ptr<config> _config;
    };
}
#endif
