#ifndef CONFIG_H
#define CONFIG_H

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

namespace helper
{
    class config
    {
    private:
        // Singleton
        config();
        ~config() = default;
        config(const config&) = delete;
        config(const std::string& fully_qualified_path);
        config& operator=(const config&) = delete;
        
        // Members
        std::filesystem::path _full_path;
        static std::string _default_dir;
        std::mutex _write_mutex;
        
        // Functions
        void create_config(); 

        // Getters
        pugi::xml_node get_node_by_tag_recursive(pugi::xml_node node, const std::string& find_str); 
        pugi::xml_node get_node_by_value_recursive(pugi::xml_node node, const std::string& find_str);     
    public:
        // Singleton getter
        static config& get_singleton(); 
        static config& get_singleton(const std::string& fully_qualified_path);

        // Members
        pugi::xml_document doc;

        // Accessors
        void xml_load();
        pugi::xml_document xml_load(const std::string& fully_qualified_path);
        void xml_write();
        void xml_write(const pugi::xml_document& doc, const std::string& fully_qualified_path);
        
        // Getters
        std::vector<pugi::xml_node> get_children_by_tag(const std::string& find_str);
        std::map<std::string, std::string> get_node_attributes(pugi::xml_node node);
        pugi::xml_node get_node_by_tag(const std::string& find_str);
        pugi::xml_node get_node_by_value(const std::string& find_str);

        // Static Getters
        static std::string get_config_file();
        static std::string get_config_path();
        static std::filesystem::path get_project_path();
    };
}

#endif
