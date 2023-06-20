#pragma once
#include <jsonobject.h>
#include <optional>
#include <charconv>


#define START_CREATE_TO_JSON_FUNC cppsimplejson::dict_t to_Jobject() const { \
    auto res = new std::unordered_map<std::string,cppsimplejson::jsonobject>();
#define MEMBER_TO_JSON(name) res->insert(std::pair<std::string,cppsimplejson::jsonobject>(#name,cppsimplejson::jsonobject(name)))
#define END_CREATE_TO_JSON_FUNC return res;}
#define START_CREATE_FROMJSON_FUNC void form_json(std::string_view json) { \
    auto obj = cppsimplejson::jsonparser::FROM_STRING(json);\
    auto map = obj.get_value<cppsimplejson::dict_t>();
#define MEMBER_ASSIGN_FROM_JSON(name,type) name = (*map->find(#name)).second.get_value<type>();
#define END_CREATE_FROMJSON_FUNC }


namespace cppsimplejson {

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
        static jsonobject FROM_STRING(std::string_view str);\
        template<class T>
        static std::string TO_JSON(const T& value) {
            if constexpr(std::is_same<T, std::nullptr_t>::value) {
                jsonobject object(value);
                return object.to_string();
            } 
            if constexpr(std::is_same<T, int>::value) {
                jsonobject object(value);
                return object.to_string();
            } 
            else if constexpr(std::is_same<T, double>::value) {
                jsonobject object(value);
                return object.to_string();
            } 
            else if constexpr(std::is_same<T, bool>::value) {
                jsonobject object(value);
                return object.to_string();
            } 
            else if constexpr(std::is_same<T, std::string>::value) {
                jsonobject object(value);
                return object.to_string();
            }
            dict_t tmp = value.to_Jobject();
            jsonobject obj (tmp);
            delete tmp;
            return obj.to_string();
        }
};

}