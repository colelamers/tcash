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
            // Static Members
            static std::string _default_dir;

            // Members
            std::filesystem::path _full_path;
            std::filesystem::path _full_file_path;
            std::mutex _write_mutex;

            // Singleton
            log();
            ~log() = default;
            log(const log&) = delete;
            log& operator=(const log&) = delete;
            
            // Static Getters
            static std::filesystem::path get_project_path();
            static std::string get_init_log_path();
            static std::string get_init_log_file();
        public:
            // Singleton Getter
            static log& get_singleton(); 

            // Getters
            std::string get_log_path();
            std::string get_log_file();
            
            // Accessors
            void create_log();
            void write_log(const std::string& message);
    };
}

#endif
