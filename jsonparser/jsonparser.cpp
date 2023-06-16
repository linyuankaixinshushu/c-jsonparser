#include "jsonparser.h"
#include <stdexcept>
#include <regex>
#include <optional>
#include <charconv>
#include <unordered_map>

jsonparser::jsonparser(std::string_view jsonstring):json_str(jsonstring) {
    cur_index = 0;
}

jsonobject jsonparser::parse() {
    if(json_str.empty()) {
        throw std::logic_error("empty string!");
    }
    cur_index = get_next_sign(json_str,cur_index);
    char sign = json_str[cur_index];
    if(sign == '"') {
        auto res = parse_str(json_str,cur_index);
        if(res.has_value()) {
            return jsonobject{*res};
        }
    }
    if(sign == 'n') {
        if(json_str.compare(cur_index, 4, "null") == 0) {
            cur_index += 4;
            return jsonobject{nullptr};
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
                return jsonobject{*res};
            }
            else {
                auto res = parse_num<int>(match_res[0].str());
                cur_index += match_res[0].length();
                return jsonobject{*res};
            }
        }
        throw std::logic_error("unexpected character in parse json");
    }
    if(sign == 't' || sign == 'f') {
        auto res = parse_bool(json_str,cur_index);
        if(res.has_value()) {
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
            obj_vec.emplace_back(parse());
            cur_index = get_next_sign(json_str,cur_index);
            if(json_str[cur_index] == ']') {
                cur_index++;
                break;
            }
            if(json_str[cur_index] != ',') {
                throw new std::logic_error("expected ',' in parse list");
            }
            cur_index++;
        }
        return jsonobject{std::move(obj_vec)};
    }
    if(sign == '{') {
        auto obj = new std::unordered_map<std::string,jsonobject>();
        cur_index = get_next_sign(json_str, cur_index + 1);
        if(json_str[cur_index] == '}') {
            return jsonobject();
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
                obj -> emplace(std::pair<std::string,jsonobject>(key,parse()));
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
            cur_index++;
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
                throw std::logic_error("Invalid array length");
            }
            isnewline = true;
            start_index++;
        }//用于跳过注释
    } while(isnewline);
    return start_index;
}
std::optional<bool> jsonparser::parse_bool(std::string_view str,int& start_index) {
    if(str.compare(start_index, 4, "true") == 0)
    {
        start_index += 4;
        if(start_index)
        return {true};
    }
    if(str.compare(start_index, 5, "false") == 0)
    {
        return {false};
        start_index += 5;
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

template<typename T>
std::optional<T> jsonparser::parse_num(std::string_view str) {
    auto value = T{};
    auto res = std::from_chars(str.data(),str.data() + str.length(),value);
    if(res.ec == std::errc()) {
        return value;
    }
    return std::nullopt;
}