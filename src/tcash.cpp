#include <iostream>
#include <filesystem>
#include <array>
#include <string>
#include <vector>

#include "config.hpp" 

// https://www.boost.org/doc/libs/latest/libs/libraries.htm

int
main(int argc, char **argv)
{
    helper::config cfg;

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