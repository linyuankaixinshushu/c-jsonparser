#include <jsonobject.h>

jsonobject::jsonobject() : data(nullptr), data_type(json_value_type::NULL_T) {}
jsonobject::jsonobject(int value) : data(value), data_type(json_value_type::INT_T) {}
jsonobject::jsonobject(double value) : data(value), data_type(json_value_type::DOUBLE_T) {}
jsonobject::jsonobject(std::string value) : data(value), data_type(json_value_type::STRING_T) {}
jsonobject::jsonobject(bool value) : data(value), data_type(json_value_type::BOOL_T) {}
jsonobject::jsonobject(list_t value): data_type(json_value_type::LIST_T) {
    data = std::move(value);
}
jsonobject::jsonobject(dict_t value) : data(value), data_type(json_value_type::DICT_T) {
    data = new std::unordered_map<std::string ,jsonobject>(*value);
} 
jsonobject::~jsonobject() {
    if(data_type == json_value_type::DICT_T) {
        delete std::get<dict_t>(data);
    }
}
jsonobject& jsonobject::operator[](int index) {
    if(data_type == json_value_type::LIST_T) {
        return std::get<list_t>(data)[index];
    }
    throw std::logic_error("this is no a list");
}
jsonobject& jsonobject::operator[](std::string key) {
    if(data_type == json_value_type::DICT_T) {
        return (*std::get<dict_t>(data))[key];
    }
    throw std::logic_error("this is no a dict");
}