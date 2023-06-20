#include <jsonparser.h>
#include <string>
#include <string_view>
#include <iostream>
#include <variant>
#include <jsonobject.h>


struct test {
    int name1 = 3;
    int name2 = 4;
    START_CREATE_TO_JSON_FUNC
    MEMBER_TO_JSON(name1);
    MEMBER_TO_JSON(name2);
    END_CREATE_TO_JSON_FUNC
    
    START_CREATE_FROMJSON_FUNC
    MEMBER_ASSIGN_FROM_JSON(name1,int);
    MEMBER_ASSIGN_FROM_JSON(name2,int);
    END_CREATE_FROMJSON_FUNC
};


int main() {
    test a;
    std::cout << cppsimplejson::jsonparser::TO_JSON(a) << std::endl;
    a.form_json("{\"name1\":1,\"name2\":2}");
    std::cout << a.name1 << std::endl << a.name2 << std::endl;
}   