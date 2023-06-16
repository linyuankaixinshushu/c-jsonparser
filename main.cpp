#include <jsonparser.h>
#include <string>
#include <string_view>
#include <iostream>
#include <variant>

void print(jsonobject& );

void print(jsonobject& json)
{
    if(json.data.index() == 0) {
        std::cout << "null" << std::endl;
    }
    if(json.data.index() == 1)
    {
        bool res = std::get<1>(json.data);
        std::cout << res << std::endl;
    }
    if(json.data.index() == 2)
    {
        int res = std::get<2>(json.data);
        std::cout << res << std::endl;
    }
    if(json.data.index() == 3)
    {
        double res = std::get<3>(json.data);
        std::cout << res << std::endl;
    }
    if(json.data.index() == 4)
    {
        std::string res = std::get<4>(json.data);
        std::cout << res << std::endl;
    }
    if(json.data.index() == 5) {
       auto const & a = std::get<5>(json.data);
       for(auto i : a) {
            print(i);
       }
    }
    if(json.data.index() == 6) {
        auto const & a = std::get<6>(json.data);
        for(auto i = a->begin(); i != a->end(); i++){
            std::cout << i ->first << " : ";
            print(i -> second);
        }
    }
}

int main() {
    std::string test("{\"nihao\" : 123 , \"woshi\": 1231e3}");
    jsonparser parser(test);
    jsonobject j = parser.parse();
    print(j);
}   