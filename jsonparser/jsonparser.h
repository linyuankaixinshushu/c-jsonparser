#pragma once
#include <jsonobject.h>
#include <optional>
#include <charconv>

class jsonparser {

        std::string_view json_str;
        int cur_index;
        
        void init(std::string_view);
        bool check_useless_tail(std::string_view str,int start_index);
        int get_next_sign(std::string_view str,int start_index);
        std::optional<bool> parse_bool(std::string_view str,int& start_index);
        std::optional<std::string> parse_str(std::string_view str, int& start_index);   
        template<class T>
        std::optional<T> parse_num(std::string_view str) {
            auto value = T{};
            auto res = std::from_chars(str.data(),str.data() + str.length(),value);
            if(res.ec == std::errc()) {
                return value;
            }
            return std::nullopt;
        }
        jsonobject parse(int flag);
    public:
        jsonparser();
        static jsonobject FROM_STRING(std::string_view str);
};