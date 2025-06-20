#ifndef LOG_H
#define LOG_H

#include <string>
#include <mutex>
#include <filesystem> 
#include "log.hpp"
#include "loglevel.hpp"

namespace helper {
    class log {
    public:
        // Constructors
        log();
        log(int log_level);
        
        // Getters
        std::string get_log_path();
        std::string get_log_file();
        
        // Accessors
        void set_log_level(int log_lev);
        void alert_log(std::string message);
        void critical_log(std::string message);
        void debug_log(std::string message);
        void error_log(std::string message);
        void fatal_log(std::string message);
        void info_log(std::string message);
        void notice_log(std::string message);
        void todo_log(std::string message);
        void trace_log(std::string message);
        void warning_log(std::string message);

    private:
        // Static Members
        static std::string _default_dir;

        // Members
        std::filesystem::path _full_path;
        std::filesystem::path _full_file_path;
        std::mutex _write_mutex;
        int _log_level;
        
        // Static Getters
        static std::filesystem::path get_project_path();
        static std::string get_init_log_path();
        static std::string get_init_log_file();
        static std::string get_time();
        static std::string get_log_type(loglevel loglev);
        // Accessors
        void create_log();
        void write(loglevel loglev, const std::string& message);
    };
}

#endif
