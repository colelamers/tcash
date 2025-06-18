#ifndef STR_EXT_H
#define STR_EXT_H

#include <string>
#include <algorithm>

namespace helper::str_ext {
    // Char*
    std::string toupper(const char* c_str);
    std::string tolower(const char*  c_str);
    std::string toproper(const char*  c_str);

    // String
    std::string toupper(const std::string& str);
    std::string tolower(const std::string& str);
    std::string toproper(const std::string& str);

    // English ASCII
    std::string tolower_ascii_word(std::string& str);
    std::string toupper_ascii_word(std::string& str);
    std::string toproper_ascii_word(std::string& str);

    // String to Number
    std::optional<int> toint(std::string& str);
    std::optional<double> todouble(std::string& str);
    std::optional<float> tofloat(std::string& str);
}

#endif
