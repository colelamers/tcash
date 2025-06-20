#include <filesystem>
#include <iostream>
#include <string>
#include <fstream> 
#include <vector>
#include <map>
#include <mutex>

#include "config.hpp"
#include "pugixml.hpp"
#include "str_ext.hpp"

///////////////////////////////////////////////////////////////////////////////
// 2025, Cole Lamers <colelamers@gmail.com>
// 
// The intent of this file is to provide a wrapper for the pugixml library to
// access xml configuration files. This allows access to a reliable config
// file that will be static throughout the life of the application.
///////////////////////////////////////////////////////////////////////////////

namespace helper {
    //---------------------------------PUBLIC---------------------------------//

    //
    // Constructors
    // 

    config::config() : _full_path(get_config_path()) {
        create_config();
        xml_load();
    }

    config::config(const std::string& fully_qualified_path)
        : _full_path(fully_qualified_path) {

    }

    //
    // Static Getters
    //

    std::filesystem::path config::get_project_path() {
        // Process:
        // project_root/src/helper/config.cpp
        // project_root/src/helper/
        // project_root/src/
        // project_root/
        return std::filesystem::absolute(__FILE__)
            .parent_path()
            .parent_path()
            .parent_path();
    }

    std::string config::get_config_path() {
        // project_root/config
        return config::get_project_path() / _default_dir;
    }

    std::string config::get_config_file() {
        // Process:
        // ~/project
        // project_config.xml
        // ~/project/config/project_config.xml
        std::filesystem::path root_path = config::get_project_path();
        std::string cfg_filename = config::get_project_path().filename().string() + "_config.xml";
        std::filesystem::path final_path = root_path / _default_dir / cfg_filename;

        return final_path.string();
    }

    //
    // Getters
    //

    pugi::xml_node config::get_node_by_tag(const std::string& find_str) {
        // "config" is currently hardcoded in my app
        return get_node_by_tag_recursive(doc.child("config"), find_str);
    }
    
    pugi::xml_node config::get_node_by_value(const std::string& find_str) {
        return get_node_by_value_recursive(doc.child("config"), find_str);
    }

    std::vector<pugi::xml_node> config::get_children_by_tag(const std::string& find_str) {
        std::vector<pugi::xml_node> children;
        pugi::xml_node parent_node = get_node_by_tag(find_str);
        
        if (!parent_node) { 
            return children;
        }
        
        for (pugi::xml_node child : parent_node.children()) {
            children.push_back(child);
        }

        return children;
    }

    std::map<std::string, std::string> config::get_node_attributes(pugi::xml_node node) {
        std::map<std::string, std::string> attributes;
        for (pugi::xml_attribute attr = node.first_attribute(); attr; attr = attr.next_attribute()) {
            attributes[attr.name()] = attr.value();
        }
        return attributes;
    }

    //
    // Accessors
    //

    void config::xml_load() {
        std::lock_guard<std::mutex> lock(_write_mutex); // lock
        doc.load_file(config::get_config_file().c_str());
    }

    pugi::xml_document config::xml_load(const std::string& fully_qualified_path) {
        std::lock_guard<std::mutex> lock(_write_mutex); // lock
        pugi::xml_document t_doc;
        t_doc.load_file(fully_qualified_path.c_str());
        return t_doc;
    }

    void config::xml_write() {
        std::lock_guard<std::mutex> lock(_write_mutex); // lock
        doc.save_file(config::get_config_file().c_str());
    }

    void config::xml_write(
        const pugi::xml_document& t_doc, 
        const std::string& fully_qualified_path) {
        std::lock_guard<std::mutex> lock(_write_mutex); // lock
        t_doc.save_file(fully_qualified_path.c_str());
    }

    //--------------------------------PRIVATE---------------------------------//

    //
    // Static Members
    //

    std::string helper::config::_default_dir = "config";

    //
    // Accessors
    //

    void config::create_config() {
        // Create Folder if it doesn't exist
        if (!std::filesystem::exists(_full_path)) {
            std::filesystem::create_directories(_full_path);
        }

        // Create the file if it doesn't exist
        std::string config_file = config::get_config_file();
        if (!std::filesystem::exists(config_file)) {
            std::ofstream ofs(config_file);
            ofs << "<config>\n<subitem type=\"int\"></subitem>\n</config>";
            ofs.close();
        }
    }

    //
    // Getters
    //

    pugi::xml_node config::get_node_by_tag_recursive(
        pugi::xml_node node, const std::string& find_str) {
        if (!node) { 
            return {};
        }

        // Compare recursive node with node trying to find
        if (str_ext::tolower(node.name()) == str_ext::tolower(find_str)) {
            return node;
        }

        // Node not found, then recurse
        for (pugi::xml_node child : node.children()) {
            pugi::xml_node found = get_node_by_tag_recursive(child, find_str);
            if (found) {
                return found;
            }
        }

        return {};
    }

    pugi::xml_node config::get_node_by_value_recursive(
        pugi::xml_node node, const std::string& find_str) {
        if (!node) { 
            return {};
        }
        if (str_ext::tolower(node.child_value()) == str_ext::tolower(find_str)) {
            return node;
        }

        for (pugi::xml_node child : node.children()) {
            pugi::xml_node found = get_node_by_value_recursive(child, find_str);
            if (found) {
                return found;
            }
        }

        return {};
    }
}
