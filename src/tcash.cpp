#include <iostream>
#include <filesystem>
#include <array>
#include <string>
#include <vector>
#include <algorithm>

#include "config.hpp" 
#include "log.hpp" 
#include "str_ext.hpp"

//main(int argc, char **argv)
int
main()
{
    helper::config cfg;
    std::string level_as_string = cfg.get_node_by_tag("loglevel").attribute("type").value();
    std::optional<int> loglevel =  helper::str_ext::toint(level_as_string);
    if (loglevel == std::nullopt){
        return 0;
    } 
    helper::log log(1);
    log.write_log("First log! Hooray!");
    log.write_log(__func__);
    auto x = cfg.get_node_by_tag("username");
    auto y = cfg.get_node_by_tag("window_width");
    auto z = cfg.get_node_by_tag("window_height");
    auto c = cfg.get_node_by_tag("wordlist");

    std::vector<pugi::xml_node> node = cfg.get_children_by_tag("wordlist");
    node.at(0).child_value();
    std::array<std::string, 10> vals = { 
        x.child_value(), x.name(), 
        y.child_value(), y.name(), 
        z.child_value(), z.name(),
        c.first_child().value(), c.name()
    };

    return 0;
}
