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
            void log_set(std::unique_ptr<log> log);

            // Getter
            log& log_get();
            config get_config();
    };
}
#endif
