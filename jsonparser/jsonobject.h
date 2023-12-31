#pragma once
#include <variant>
#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>
#include <stdexcept>


namespace cppsimplejson {

class jsonobject;

using dict_t = std::unordered_map<std::string ,jsonobject>*;
using list_t = std::vector<jsonobject>;
using null = std::nullptr_t;

enum json_value_type {
    NULL_T,
    BOOL_T,
    INT_T,
    DOUBLE_T,
    STRING_T,
    LIST_T,
    DICT_T,
};


class jsonobject {
    private:
        json_value_type data_type;
        std::variant
        <std::nullptr_t //null }
        ,bool
        ,int
        ,double
        ,std::string
        ,list_t
        ,dict_t                  // {"你好":1}
        > data;
    public:
        jsonobject();
        jsonobject(int);
        jsonobject(double);
        jsonobject(std::string);
        jsonobject(bool);
        jsonobject(list_t);
        jsonobject(dict_t);
        ~jsonobject();

        template<class T>
        const T& get_value() {
            if constexpr (std::is_same<T,std::nullptr_t>::value) {
                if(data_type != json_value_type::NULL_T)
                    throw new std::logic_error("type error in get null value!");
            }
            else if constexpr (std::is_same<T,bool>::value) {
                if(data_type != json_value_type::BOOL_T)
                    throw new std::logic_error("type error in get bool value!");
            }
            else if constexpr (std::is_same<T,std::string>::value) {
                if(data_type != json_value_type::STRING_T)
                    throw new std::logic_error("type error in get string value!");
            }
            else if constexpr (std::is_same<T,double>::value) {
                if(data_type != json_value_type::DOUBLE_T)
                    throw new std::logic_error("type error in get double value!");
            }
            else if constexpr (std::is_same<T,int>::value) {
                if(data_type != json_value_type::INT_T)
                    throw new std::logic_error("type error in get int value!");
            }
            else if constexpr (std::is_same<T,list_t>::value) {
                if(data_type != json_value_type::LIST_T)
                    throw new std::logic_error("type error in get list value!");
            }
            else if constexpr (std::is_same<T,dict_t>::value) {
                if(data_type != json_value_type::DICT_T)
                    throw new std::logic_error("type error in get dict value!");
            }
            return std::get<T>(data);
        }
        template<class T>
        void set_value(const T &value) {
            if constexpr (std::is_same<T,std::nullptr_t>::value) {
                data = value;
                data_type = json_value_type::NULL_T;
            }
            else if constexpr (std::is_same<T,bool>::value) {
                data = value;
                data_type = json_value_type::BOOL_T;
            }
            else if constexpr (std::is_same<T,std::string>::value) {
                data = value;
                data_type = json_value_type::STRING_T;
            }
            else if constexpr (std::is_same<T,double>::value) {
                data = value;
                data_type = json_value_type::DOUBLE_T;
            }
            else if constexpr (std::is_same<T,int>::value) {
                data = value;
                data_type = json_value_type::INT_T;
            }
            else if constexpr (std::is_same<T,list_t>::value) {
                data = value;
                data_type = json_value_type::LIST_T;
            }
            else if constexpr (std::is_same<T,dict_t>::value) {
                data = new std::unordered_map<std::string ,jsonobject>(*value);
                data_type = json_value_type::NULL_T;
            }
            else {
                std::string cur_type_name = typeid(T).name();
                throw new std::logic_error(std::string("type") + cur_type_name + std::string("is not support type"));
            }
            if(data_type == json_value_type::DICT_T) {
                delete std::get<dict_t>(data);
            }
        }

        std::string to_string();

        jsonobject& operator[](int index);
        jsonobject& operator[](std::string key);
};


}