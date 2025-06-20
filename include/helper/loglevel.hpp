#ifndef LOGLEVEL_H
#define LOGLEVEL_H

#include <string>
#include <mutex>
#include <filesystem> 

namespace helper {
    enum class loglevel {
        ALERT,
        CRITICAL,
        DEBUG,
        ERROR,
        FATAL,
        INFO,
        NOTICE,
        TODO,
        TRACE,
        WARNING,
    };
}
#endif
