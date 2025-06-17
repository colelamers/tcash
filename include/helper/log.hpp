#ifndef LOG_H
#define LOG_H

#include <string>
#include <mutex>

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
            int _log_level;
            
            // Static Getters
            static std::filesystem::path get_project_path();
            static std::string get_init_log_path();
            static std::string get_init_log_file();
        public:

            // Constructors
            log();
            log(int log_level);
            
            // Getters
            std::string get_log_path();
            std::string get_log_file();
            
            // Accessors
            void create_log();
            void write_log(const std::string& message);
            void set_log_level(int log_lev);
    };
}

#endif
