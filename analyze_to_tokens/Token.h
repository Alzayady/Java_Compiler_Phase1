//
// Created by HP-SYSTEMS on 5/5/2021.
//

#ifndef JAVA_COMPILER_TOKEN_H
#define JAVA_COMPILER_TOKEN_H


#include <string>

class Token {
public:
    Token(std::string , std::string);
    std::string get_name_of_token();
    std::string get_token();
    bool IsError();
    void set_Error();
    std::string toString();
private:
    std::string name_of_token;
    std::string token;
    bool  ErrorString;

};


#endif //JAVA_COMPILER_TOKEN_H
