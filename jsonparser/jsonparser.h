#pragma once
#include <jsonobject.h>
#include <optional>

class jsonparser {
        std::string_view json_str;
        int cur_index;
    // public:
        int get_next_sign(std::string_view str,int start_index);
        std::optional<bool> parse_bool(std::string_view str,int& start_index);
        std::optional<std::string> parse_str(std::string_view str, int& start_index);
    template<class T>
        std::optional<T> parse_num(std::string_view);
    public:
        jsonobject parse();
        jsonparser(std::string_view jsonstring);
};