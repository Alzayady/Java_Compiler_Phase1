//
// Created by HP-SYSTEMS on 5/5/2021.
//

#include "Token.h"

Token::Token(std::string name_of_token, std::string token) {
    this->name_of_token = name_of_token;
    this->token = token;
    this->ErrorString = false;

}

std::string Token::get_name_of_token() {
    return name_of_token;
}

std::string Token::get_token() {
    return token;
}

bool Token::IsError() {
    return this->ErrorString;
}

void Token::set_Error() {
    this->ErrorString = true;
}
std::string Token::toString(){
    std::string ans = "name  : ";
    ans+= this->name_of_token ;
    ans+="   token : ";
    ans+= this->token;
    return ans;
}
