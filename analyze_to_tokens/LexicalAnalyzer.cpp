//
// Created by HP-SYSTEMS on 5/5/2021.
//

#include "LexicalAnalyzer.h"
#include "../Phase2/def/InputMatcher.h"

LexicalAnalyzer::LexicalAnalyzer(Table *table) {
    this->table = table;
}

std::vector<Token *> LexicalAnalyzer::convert(std::string str) {
    std::string last_accepted_string;
    std::string acceptingName;
    int n = str.size();
    int cur_row = table->get_start_row();
    std::string last_token;
    std::vector<Token *> tokens;
    for (int i = 0; i < n;) {
        while (i < n and table->can_go(cur_row, str[i])) {
            last_token += str[i];
            cur_row = table->next_row(str[i], cur_row);
            if (table->isAcceptedRow(cur_row)) {
                last_accepted_string = last_token;
                acceptingName = table->getAcceptedName(cur_row);
            }
            i++;
        }

        if (last_token.empty()) {
            std::string tmp_str;
            tmp_str += str[i];
            Token *token = new Token("ERROR", tmp_str);
            token->set_Error();
            tokens.push_back(token);
            i++;
        } else {
            if (last_accepted_string.size()) {
                int dif = (int) last_token.size() - (int) last_accepted_string.size();
                i -= dif;
                Token *token = new Token(acceptingName, last_accepted_string);
                tokens.push_back(token);
                freopen("../action_logs.txt", "a", stdout);
                InputMatcher::getInstance().match(token->get_name_of_token());
            } else {
                i -= (int) last_accepted_string.size();
                std::string temp_name;
                temp_name += str[i];
                Token *token = new Token("ERROR", temp_name);
                token->set_Error();
                tokens.push_back(token);
                i++;
            }
        }
        cur_row = table->get_start_row();
        last_token = "";
        last_accepted_string ="";

    }
    return tokens;
}