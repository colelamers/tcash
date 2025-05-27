#include <chrono>
#include <filesystem>
#include <format>
#include <fstream>
#include <iostream>
#include <string>

#include "log.hpp"
#include "str_ext.hpp"

///////////////////////////////////////////////////////////////////////////////
// 2025, Cole Lamers <colelamers@gmail.com>
// 
// The intent of this file is to provide access to file logging capabilities
///////////////////////////////////////////////////////////////////////////////

namespace helper {
    std::string log::_default_dir = "logs";

    log::log() : _full_path(get_log_path())
    {
        // Make the folder
        create_log();
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

    std::string log::get_log_path(){
        // project_root/log
        return log::get_project_path() / _default_dir;
    }

    std::filesystem::path get_project_path();  // Assuming you have this implemented
    constexpr const char* _default_dir = "logs";

    std::string get_log_file() {
        using namespace std::chrono;

        // Get current date
        auto now = system_clock::now();
        auto today = floor<days>(now);
        std::chrono::year_month_day ymd = std::chrono::year_month_day{today};

        // Format date as yyyymmdd
        std::string date_str = std::format("{:%Y%m%d}", ymd);

        // Compose log filename
        std::string base_filename = log::get_project_path().filename().string(); // e.g., "tcash"
        std::string log_filename = date_str + "_" + base_filename + ".log";      // e.g., "20250527_tcash.log"

        // Compose final path
        std::filesystem::path root_path = log::get_project_path();
        std::filesystem::path final_path = root_path / _default_dir / log_filename;

        return final_path.string();
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
            ofs << "<log></log>\n";
            ofs.close();
        }
    }
}
