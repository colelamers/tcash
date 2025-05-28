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

///////////////////////////////////////////////////////////////////////////////
// 2025, Cole Lamers <colelamers@gmail.com>
// 
// The intent of this file is to provide access to file logging capabilities
///////////////////////////////////////////////////////////////////////////////

namespace helper {
    std::string log::_default_dir = "logs";

    log::log() : _full_path(get_log_path()), _full_file_path(get_log_file())
    {
        // Make the folder
        create_log();
    }

    log& log::get_instance() {
        static log instance;
        return instance;
    }

    std::filesystem::path log::get_project_path(){
        // Process:
        // project_root/src/helper/log.cpp
        // project_root/src/helper
        // project_root/src
        // project_root
        return std::filesystem::absolute(__FILE__)
            .parent_path()
            .parent_path()
            .parent_path();
    }

    std::string log::get_init_log_path(){
        // project_root/log
        return log::get_project_path() / _default_dir;
    }

    std::string log::get_init_log_file() {
        // now
        // today date time
        // yyyymmdd of today
        // 20250527
        // tcash
        auto now = std::chrono::system_clock::now();
        auto today = std::chrono::floor<std::chrono::days>(now);
        std::chrono::year_month_day ymd = std::chrono::year_month_day{today};
        std::string date_str = std::format("{:%Y%m%d}", ymd);
        std::string base_filename = log::get_project_path().filename().string();

        // 20250527_tcash.log
        // ~/project_root/
        // ~/project_root/logs/20250527_tcash.log
        std::string log_filename = date_str + "_" + base_filename + ".log";
        std::filesystem::path root_path = log::get_project_path();
        std::filesystem::path final_path = root_path / _default_dir / log_filename;
        return final_path.string();
    }

    std::string log::get_log_path(){
        // project_root/log
        return _full_path;
    }

        std::string log::get_log_file(){
        // project_root/log
        return _full_file_path;
    }


    void log::create_log(){
        // Create Folder if it doesn't exist
        if (!std::filesystem::exists(_full_path)) {
            std::filesystem::create_directories(_full_path);
        }

        // Create the file if it doesn't exist
        std::string log_file = log::get_log_file();
        if (!std::filesystem::exists(log_file)) {
            std::ofstream ofs(log_file);
            ofs.close();
        }
    }

    void log::write_log(const std::string& message) {
        std::lock_guard<std::mutex> lock(_write_mutex); // lock

        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        std::tm buf;
    #ifdef _WIN32
        localtime_s(&buf, &in_time_t);
    #else
        localtime_r(&in_time_t, &buf);
    #endif

        std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                now.time_since_epoch()) % 1000;
        std::ostringstream timestamp;
        timestamp << std::put_time(&buf, "%Y_%m_%d-%H_%M_")
                << std::setw(3) << std::setfill('0') << ms.count();

        // Compose log line
        std::string log_line = timestamp.str() + ": " + message + "\n";

        // Append to file
        std::ofstream ofs(log::get_log_file(), std::ios::app);
        if (ofs.is_open()) {
            ofs << log_line;
        }
        ofs.close();
    }
}
