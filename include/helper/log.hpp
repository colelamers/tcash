#ifndef LOG_H
#define LOG_H

#include <chrono>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <mutex>

#include "log.hpp"
#include "str_ext.hpp"

namespace helper
{
    class log
    {
        private:
            static std::string _default_dir;
            std::filesystem::path _full_path;
            std::mutex _write_mutex;
        public:
            // Constructors
            log();

            // Functions
            void create_log();
            void write_log(const std::string& message);

            // Static Getters
            static std::string get_log_path();
            static std::filesystem::path get_project_path();
            static std::string get_log_file();
    };
}

#endif
