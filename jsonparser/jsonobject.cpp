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

std::string jsonobject::to_string() {
    std::string json_str;
    switch (data_type)
    {
        case json_value_type::NULL_T: {
            json_str += "null";
            break;
        }
        case json_value_type::BOOL_T: {
            if(get_value<bool>()) 
                json_str += "true";
            else 
                json_str += "false";
            break;
        }
        case json_value_type::INT_T: {
            json_str += std::to_string(get_value<int>());
            break;
        }
        case json_value_type::DOUBLE_T: {
            json_str += std::to_string(get_value<double>());
            break; 
        }
        case json_value_type::STRING_T: {
            json_str += get_value<std::string>();
            break;
        }
        case json_value_type::LIST_T: {
            json_str += '[';
            auto list = std::get<list_t>(data);
            for(int i = 0; i < list.size(); i++) {
                json_str += list[i].to_string();
                if(i != list.size() - 1)
                    json_str += ',';
            }
            json_str.push_back(']');
            break;
        }
        case json_value_type::DICT_T: {
            json_str += '{';
            auto dict_ptr = std::get<dict_t>(data);
            for(auto i = dict_ptr->begin(); i != dict_ptr -> end(); i++) {
                json_str += '"';
                json_str += i -> first + '"' + ":" +i -> second.to_string() + ",";
            }
            json_str[json_str.size() - 1] = '}';
            break;
        }
    }
    return json_str;
}
