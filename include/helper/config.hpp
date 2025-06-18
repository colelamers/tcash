#ifndef CONFIG_H
#define CONFIG_H

#include <filesystem>
#include <string>
#include <vector>
#include <map>
#include <mutex>

#include "pugixml.hpp"

namespace helper
{
    class config
    {
    private:
        // Static Members
        static std::string _default_dir;
        
        // Members
        std::filesystem::path _full_path;
        std::mutex _write_mutex;

        // Getters
        pugi::xml_node get_node_by_tag_recursive(pugi::xml_node node, const std::string& find_str); 
        pugi::xml_node get_node_by_value_recursive(pugi::xml_node node, const std::string& find_str);     
        
        // Accessors
        void create_config(); 

    public:
        // Constructors
        config();
        config(const std::string& fully_qualified_path);

        // Members
        pugi::xml_document doc;

        // Static Utility Functions (optional to keep)
        static std::filesystem::path get_project_path();
        static std::string get_config_path();
        static std::string get_config_file();
        
        // Getters
        pugi::xml_node get_node_by_tag(const std::string& find_str);
        pugi::xml_node get_node_by_value(const std::string& find_str);
        std::vector<pugi::xml_node> get_children_by_tag(const std::string& find_str);
        std::map<std::string, std::string> get_node_attributes(pugi::xml_node node);

        // Accessors
        void xml_load();
        pugi::xml_document xml_load(const std::string& fully_qualified_path);
        void xml_write();
        void xml_write(const pugi::xml_document& t_doc, const std::string& fully_qualified_path);
    };
}

#endif
