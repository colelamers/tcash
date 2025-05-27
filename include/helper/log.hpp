#ifndef LOG_H
#define LOG_H

namespace helper
{
    class log
    {
        private:
            static std::string _default_dir;
            std::filesystem::path _full_path;

        public:
            // Constructors
            log();

            // Functions
            void create_log();

            // Static Getters
            static std::string get_log_path();
            static std::filesystem::path get_project_path();
            static std::string get_log_file();
    };
}

#endif
