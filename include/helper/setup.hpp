#ifndef SETUP_H
#define SETUP_H

#include <string>
#include <algorithm>

#include "log.hpp"
#include "config.hpp"

namespace helper {
    class setup {
        private:
            std::unique_ptr<log> _log;
            std::unique_ptr<config> _config;
        public:
            // Constructors
            setup();

            // Accessor
            void set_log(std::unique_ptr<log> lg);
            void set_config(std::unique_ptr<config> cfg);
            // Getter
            log& get_log();
            config& get_config();
    };
}
#endif
