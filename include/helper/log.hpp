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
            // Singleton
            log();
            ~log() = default;
            log(const log&) = delete;
            log& operator=(const log&) = delete;

            // Static members
            static std::string _default_dir;
            static std::string get_init_log_file();
            static std::string get_init_log_path();
            static std::filesystem::path get_project_path();

            // Members
            std::filesystem::path _full_path;
            std::filesystem::path _full_file_path;
            std::mutex _write_mutex;
        public:
            // Singleton getter
            static log& get_instance(); 

            // Functions
            void create_log();
            void write_log(const std::string& message);

            // Getters
            std::string get_log_file();
            std::string get_log_path();
    };
}

#endif
