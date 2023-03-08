#ifndef SIMPLEGAMEENGINE_STRINGUTILS_H
#define SIMPLEGAMEENGINE_STRINGUTILS_H

#include <algorithm>
#include <string>
#include <cctype>
#include <locale>
#include <list>

class StringUtils {
public:
// trim from start (in place)
    static void ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
            return !std::isspace(ch);
        }));
    }

    static std::string_view ltrim(std::string_view s) {
        return s.substr(s.find_first_not_of(' '));
    }

// trim from end (in place)
    static void rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
            return !std::isspace(ch);
        }).base(), s.end());
    }

    static std::string_view rtrim(std::string_view &s) {
        return s.substr(0, s.find_last_not_of(' '));
    }

// trim from both ends (in place)
    static void trim(std::string &s) {
        ltrim(s);
        rtrim(s);
    }

    static std::string_view trim(std::string_view s) {
       return s.substr(s.find_first_not_of(' '), s.find_last_not_of(' '));
    }

// trim from start (copying)
    static std::string ltrim_copy(std::string s) {
        ltrim(s);
        return s;
    }

// trim from end (copying)
    static std::string rtrim_copy(std::string s) {
        rtrim(s);
        return s;
    }

// trim from both ends (copying)
    static std::string trim_copy(std::string s) {
        trim(s);
        return s;
    }

    static void toupper(std::string &s) {
        std::transform(s.begin(), s.end(), s.begin(), ::toupper);
    }

    static std::string toupper_copy(std::string s) {
        toupper(s);
        return s;
    }

    static void split(std::list<std::string> *res, std::string_view s, std::string_view delimiter) {
        size_t pos; std::string token;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            res->push_back(token);
            s = s.substr(0, pos + delimiter.length());
        }
    }

    static unsigned int toUInt(std::string str) { return std::stoul(str); }
};

#endif //SIMPLEGAMEENGINE_STRINGUTILS_H
