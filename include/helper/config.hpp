#ifndef CONFIG_H
#define CONFIG_H

#include <string>
#include <vector>
#include <filesystem>

#include "pugixml.hpp"

namespace helper
{
    class config
    {
    private:
        std::filesystem::path _full_path;
        static std::string _default_dir;
        void create_config(); 
        pugi::xml_node get_node_by_tag_recursive(pugi::xml_node node, const std::string& find_str); 
        pugi::xml_node get_node_by_value_recursive(pugi::xml_node node, const std::string& find_str);     
    public:
        pugi::xml_document doc;

        config();
        config(const std::string& fully_qualified_path);

        void xml_load();
        pugi::xml_document xml_load(const std::string& fully_qualified_path);
        
        void xml_write();
        void xml_write(const pugi::xml_document& doc, const std::string& fully_qualified_path);
        
        std::vector<pugi::xml_node> get_children_by_tag(const std::string& find_str);

        pugi::xml_node get_node_by_tag(const std::string& find_str);
        pugi::xml_node get_node_by_value(const std::string& find_str);
        static std::string get_config_file();
        static std::string get_config_path();
        static std::filesystem::path get_project_path();
    };
}

#endif