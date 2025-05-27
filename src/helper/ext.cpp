#include <string>
#include <algorithm>

#include "ext.hpp"

namespace helper::ext {

    std::string tolower(const char* c_str){
        std::string str(c_str);
        return tolower(str);
    }

    std::string toupper(const char* c_str){
        std::string str(c_str);
        return toupper(str);
    }

    std::string toproper(const char* c_str){
        std::string str(c_str);
        return toproper(str);
    }

    std::string tolower(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(),
                       [](unsigned char c){ return static_cast<char>(std::tolower(c)); });
        return result;
    }

    std::string toupper(const std::string& str) {
        std::string result = str;
        std::transform(result.begin(), result.end(), result.begin(),
                       [](unsigned char c){ return static_cast<char>(std::toupper(c)); });
        return result;
    }

    std::string toproper(const std::string& str) {
        if (str.empty()) {
            return str;
        }

        std::string result = str;
        result[0] = static_cast<char>(std::toupper(static_cast<unsigned char>(result[0])));
        if (result.length() > 1) { 
            std::transform(result.begin(), result.end(), result.begin(),
                           [](unsigned char c){ return static_cast<char>(std::tolower(c)); });
        }
        return result;
    }

    // English ASCII Only
    std::string tolower_ascii_word(std::string& str){
        std::string result = str;
        for (char& c: result) {
            if ('A' <= c && c <= 'Z') { 
                c = c - 'A' + 'a';
            }
        }
        return result;
    }

    std::string toupper_ascii_word(std::string& str){
        std::string result = str;
        for (char& c: result) {
            if ('a' <= c && c <= 'z') { 
                c = c - 'a' + 'A';;
            }
        }
        return result;
    }

    std::string toproper_ascii_word(std::string& str) {
        if (str.empty()) {
            return str;
        }

        std::string result = str;
        if (result[0] >= 'a' && result[0] <= 'z') {
            result[0] = result[0] - 'a' + 'A';
        }

        for (size_t i = 1; i < result.length(); ++i) {
            if (result[i] >= 'A' && result[i] <= 'Z') {
                result[i] = result[i] - 'A' + 'a';
            }
        }
        return result;
    }
}
