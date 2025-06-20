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
#include "loglevel.hpp"

///////////////////////////////////////////////////////////////////////////////
// 2025, Cole Lamers <colelamers@gmail.com>
// 
// Provide access to file logging actions
///////////////////////////////////////////////////////////////////////////////

namespace helper {
    //---------------------------------PUBLIC---------------------------------//

    //
    // Constructors
    //
    log::log() : 
        _full_path(get_init_log_path()), 
        _full_file_path(get_init_log_file()),
        _log_level(1)
    {
    }

    log::log(int log_level) : 
        _full_path(get_init_log_path()), 
        _full_file_path(get_init_log_file()),
        _log_level(log_level)
    {
        // Make the folder
        create_log();
    }

    //
    // Getters
    //

    std::string log::get_log_path() {
        // project_root/log
        return _full_path;
    }

    std::string log::get_log_file() {
        // project_root/log
        return _full_file_path;
    }

    //
    // Accessors
    //
    void log::alert_log(std::string message) {
        write(loglevel::ALERT, message);
    }

    void log::critical_log(std::string message) {
        write(loglevel::CRITICAL, message);
    }

    void log::debug_log(std::string message) {
        write(loglevel::DEBUG, message);
    }

    void log::error_log(std::string message) {
        write(loglevel::ERROR, message);
    }
    
    void log::fatal_log(std::string message) {
        write(loglevel::FATAL, message);
    }

    void log::info_log(std::string message) {
        write(loglevel::INFO, message);
    }
    
    void log::notice_log(std::string message) {
        write(loglevel::NOTICE, message);
    }

    void log::todo_log(std::string message) {
        write(loglevel::TODO, message);
    }
    
    void log::trace_log(std::string message) {
        write(loglevel::TRACE, message);
    }

    void log::warning_log(std::string message) {
        write(loglevel::WARNING, message);
    }


    //--------------------------------PRIVATE---------------------------------//

    //
    // Static Members
    //

    std::string log::_default_dir = "logs";

    //
    // Static Getters
    //

    std::filesystem::path log::get_project_path() {
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
        auto now = std::chrono::system_clock::now();
        // Convert now to local time zone
        std::chrono::zoned_time local_time{std::chrono::current_zone(), now};

        // Floor to days to get local midnight
        std::chrono::year_month_day ymd{floor<std::chrono::days>(local_time.get_local_time())};

        std::string date_str = std::format("{:%Y%m%d}", ymd);

        std::string base_filename = log::get_project_path().filename().string();
        std::string log_filename = date_str + "_" + base_filename + ".log";
        std::filesystem::path root_path = log::get_project_path();
        std::filesystem::path final_path = root_path / _default_dir / log_filename;
        return final_path.string();
    }

    void log::write(loglevel loglev, const std::string& message) {
        std::lock_guard<std::mutex> lock(_write_mutex); // lock

        std::string log_type = "[" + log::get_log_type(loglev) + "] ";
        std::string log_msg = log_type + log::get_time() + " " + message + "\n";
        std::ofstream ofs(log::get_log_file(), std::ios::app);

        // Append escape char at end
        if (ofs.is_open()) {
            ofs << log_msg;
        }
        ofs.close();
    }

    std::string log::get_log_type(loglevel loglev) {
        switch (loglev){
            case loglevel::ALERT:
                return "ALERT";
            case loglevel::CRITICAL:
                return "CRITICAL";
            case loglevel::DEBUG:
                return "DEBUG";
            case loglevel::ERROR:
                return "ERROR";
            case loglevel::FATAL:
                return "FATAL";
            case loglevel::INFO:
                return "INFO";
            case loglevel::NOTICE:
                return "NOTICE";
            case loglevel::TODO:
                return "TODO";
            case loglevel::TRACE:
                return "TRACE";
            case loglevel::WARNING:
                return "WARNING";
            default:
                return "TYPE UNKNOWN! CRITICAL LOG ERROR!";
        }
    }

    std::string log::get_time() {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        std::tm buf;
    #ifdef _WIN32
        localtime_s(&buf, &in_time_t);
    #else
        localtime_r(&in_time_t, &buf);
    #endif

        // Get Milliseconds
        std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                now.time_since_epoch()) % std::chrono::milliseconds(1000);
            
        // Set timestamp
        std::ostringstream timestamp;
        timestamp << std::put_time(&buf, "[%H:%M.")
                  << std::setw(3) 
                  << std::setfill('0') 
                  << ms.count();

        // Log and Write to file
        return timestamp.str() + "]";
    }

    void log::create_log() {
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
}
