//
// Created by HP-SYSTEMS on 5/5/2021.
//

#ifndef JAVA_COMPILER_TOKEN_H
#define JAVA_COMPILER_TOKEN_H


#include <string>

class Token {
public:
    Token(std::string , std::string){
        this->name_of_token = name_of_token;
        this->token = token;
        this->ErrorString = false;
    }
    std::string get_name_of_token(){
        return name_of_token;
    }
    std::string get_token(){
        return token;
    }
    bool IsError(){
        return this->ErrorString;
    }
    void set_Error(){
        this->ErrorString = true;
    }
    std::string toString(){
        std::string ans = "name  : ";
        ans+= this->name_of_token ;
        ans+="   token : ";
        ans+= this->token;
        return ans;
    }
private:
    std::string name_of_token;
    std::string token;
    bool  ErrorString;

};


#endif //JAVA_COMPILER_TOKEN_H
