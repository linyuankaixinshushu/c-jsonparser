#include "jsonparser.h"
#include <stdexcept>
#include <regex>
#include <optional>
#include <unordered_map>

jsonparser::jsonparser():json_str(""),cur_index(0) {}

void jsonparser::init(std::string_view str) {
    cur_index = 0;
    json_str = str;
}

jsonobject jsonparser::parse(int parse_dict_or_list = 0) {
    if(json_str.empty()) {
        throw std::logic_error("empty string!");
    }
    cur_index = get_next_sign(json_str,cur_index);
    char sign = json_str[cur_index];
    if(sign == '"') {
        auto res = parse_str(json_str,cur_index);
        if(res.has_value()) {
            if(parse_dict_or_list == 0) {
                if(check_useless_tail(json_str,cur_index)) {
                    throw std::logic_error("unexpected character in parse json");
                }
            }
            return jsonobject{*res};
        }
    }
    if(sign == 'n') {
        if(json_str.compare(cur_index, 4, "null") == 0) {
            cur_index += 4;
            if(parse_dict_or_list == 0) {
                if(check_useless_tail(json_str,cur_index)) {
                    throw std::logic_error("unexpected character in parse json");
                }
            }    
            return jsonobject{};
        }
    }
    if((sign >='0' && sign <= '9') || sign == '-') {
        std::regex num_re("-?[0-9]+(\\.[0-9]+)?([eE][+-]?[0-9]+)?");
        std::cmatch match_res;
        if(std::regex_search(json_str.data() + cur_index, json_str.data() + json_str.size(), match_res, num_re))
        {
            if(match_res[0].str().find_first_of(".eE")!= -1) {
                auto res = parse_num<double>(match_res[0].str());
                cur_index += match_res[0].length();
                if(parse_dict_or_list == 0) {
                    if(check_useless_tail(json_str,cur_index)) {
                        throw std::logic_error("unexpected character in parse json");
                }
            }  
                return jsonobject{*res};
            }
            else {
                auto res = parse_num<int>(match_res[0].str());
                cur_index += match_res[0].length();
                if(parse_dict_or_list == 0) {
                    if(check_useless_tail(json_str,cur_index)) {
                        throw std::logic_error("unexpected character in parse json");
                    }
            }  
                return jsonobject{*res};
            }
        }
        throw std::logic_error("unexpected character in parse json");
    }
    if(sign == 't' || sign == 'f') {
        auto res = parse_bool(json_str,cur_index);
        if(res.has_value()) {
            if(parse_dict_or_list == 0) {
                if(check_useless_tail(json_str,cur_index)) {
                    throw std::logic_error("unexpected character in parse json");
                }
            }  
            return jsonobject{res.value()};
        }
    }
    if(sign == '[') {
        std::vector<jsonobject> obj_vec;
        cur_index = get_next_sign(json_str, cur_index + 1);
        if(json_str[cur_index] == ']') {
            return jsonobject{std::move(obj_vec)};
        }
        while(true) {
            cur_index = get_next_sign(json_str,cur_index);
            obj_vec.emplace_back(parse(1));
            cur_index = get_next_sign(json_str,cur_index);
            if(json_str[cur_index] == ']') {
                cur_index++;
                break;
            }
            if(json_str[cur_index] != ',') {
                throw new std::logic_error("expected ',' in parse list");
            }
            if(json_str[cur_index + 1] == ']') {
                cur_index += 2;
                break;
            }
            cur_index++;
        }
        if(parse_dict_or_list == 0) {
            if(check_useless_tail(json_str,cur_index)) {
                throw std::logic_error("unexpected character in parse json");
            }
        }  
        return jsonobject{std::move(obj_vec)};
    }
    if(sign == '{') {
        auto obj = new std::unordered_map<std::string,jsonobject>();
        cur_index = get_next_sign(json_str, cur_index + 1);
        if(json_str[cur_index] == '}') {
            return jsonobject{obj};
        }
        while(true) {
            cur_index = get_next_sign(json_str, cur_index);
            if(json_str[cur_index] != '"') {
                throw std::logic_error("expected '\"' in parse dict");
                delete obj;
            }
            std::string key(std::get<4>(parse().data));
            if(obj -> find(key) != obj -> end()) {
                throw std::logic_error("repeat key in object!");
                delete obj;
            }
            cur_index = get_next_sign(json_str, cur_index);
            if(json_str[cur_index] != ':') {
                throw std::logic_error("expected '\"' in parse dict");
                delete obj;
            }
            else {
                cur_index = get_next_sign(json_str, cur_index + 1);
                obj -> emplace(std::pair<std::string,jsonobject>(key,parse(1)));
            }
            cur_index = get_next_sign(json_str, cur_index);
            if(json_str[cur_index] == '}') {
                cur_index++;
                break;
            }
            if(json_str[cur_index] != ',') {
                throw new std::logic_error("expected ',' in parse list");
                delete obj;
            }
            if(json_str[cur_index + 1] == '}') { //{"nihjao" : 1,}
                cur_index += 2;
                break;
            }
            cur_index++;
        }
        if(parse_dict_or_list == 0) {
            if(check_useless_tail(json_str,cur_index)) {
                throw std::logic_error("unexpected character in parse json");
            }
        }  
        return jsonobject{obj};
    }
    throw std::logic_error("unexpected character in parse json");
}

int jsonparser::get_next_sign(std::string_view str,int start_index) {
    bool isnewline = false;
    do {
        isnewline = false; 
        while(std::isspace(str[start_index])) {
            start_index++;
        }
        if(start_index >= str.size()) {
            throw std::logic_error("Invalid array length");
        }
        if(str[start_index] == '/' && start_index + 1 < str.size() && str[start_index + 1] == '/') {
            while(str[start_index] != '\n' && str[start_index] != '\0') {
                start_index++;
            }
            if(start_index >= str.size()) {
                return false;
            }
            isnewline = true;
            start_index++;
        }//用于跳过注释
    } while(isnewline);
    return start_index;
}

bool jsonparser::check_useless_tail(std::string_view str,int start_index) {
    bool isnewline = false;
    do {
        isnewline = false; 
        while(std::isspace(str[start_index])) {
            start_index++;
        }
        if(start_index >= str.size()) {
            return false;
        }
        if(str[start_index] == '/' && start_index + 1 < str.size() && str[start_index + 1] == '/') {
            while(str[start_index] != '\n' && str[start_index] != '\0') {
                start_index++;
            }
            if(start_index >= str.size()) {
                return false;
            }
            isnewline = true;
            start_index++;
        }//用于跳过注释
    } while(isnewline);
    return true;
}

std::optional<bool> jsonparser::parse_bool(std::string_view str,int& start_index) {
    if(str.compare(start_index, 4, "true") == 0)
    {
        start_index += 4;
        return {true};
    }
    if(str.compare(start_index, 5, "false") == 0)
    {
        start_index += 5;
        return {false};
    }
    return std::nullopt;
}

std::optional<std::string> jsonparser::parse_str(std::string_view str, int& start_index) {
    int cur_index = start_index;
    int end_index = -1;
    if((end_index = str.find('"', start_index + 1)) != str.npos) {
        start_index = end_index + 1;
        return std::string(str.substr(cur_index + 1, end_index - cur_index -1));
    }
    return std::nullopt;
}

jsonobject jsonparser::FROM_STRING(std::string_view str) {
    static jsonparser parser;
    parser.init(str);
    return parser.parse();
}