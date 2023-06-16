#pragma once
#include <variant>
#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>



struct jsonobject {
    std::variant
    <std::nullptr_t //null 
    ,bool
    ,int
    ,double
    ,std::string
    ,std::vector<jsonobject>
    ,std::unordered_map<std::string ,jsonobject>* // {"你好":1}
    > data;
};