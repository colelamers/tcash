#include <iostream>
#include <filesystem>
#include <array>
#include <string>
#include <vector>
#include <algorithm>

#include "str_ext.hpp"
#include "setup.hpp"

//main(int argc, char **argv)
int
main()
{
    helper::setup& def = helper::setup::instance();
    def.get_log().alert_log("Issue with this if this happens!");
    return 0;
}

/*
    helper::setup def;
    std::string level_as_string = def.get_config().get_node_by_tag("loglevel")
        .attribute("type").value();
    std::optional<int> loglevel =  helper::str_ext::toint(level_as_string);
    if (loglevel == std::nullopt){
        return 0;
    } 
    helper::log log(1);
    log.write_log("First log! Hooray!");
    log.write_log(__func__);
    auto x = def.get_config().get_node_by_tag("username");
    auto y = def.get_config().get_node_by_tag("window_width");
    auto z = def.get_config().get_node_by_tag("window_height");
    auto c = def.get_config().get_node_by_tag("wordlist");

    std::vector<pugi::xml_node> node = def.get_config().get_children_by_tag("wordlist");
    node.at(0).child_value();
    std::array<std::string, 10> vals = { 
        x.child_value(), x.name(), 
        y.child_value(), y.name(), 
        z.child_value(), z.name(),
        c.first_child().value(), c.name()
    };

*/
