#ifndef _RegularDefinition_
#define _RegularDefinition_

#include "Imports.h"

class RegularDefinition
{

    public:
        void set_value(string val)
        {
            value = val;
        }
        void append_to_redef_value(string str)
        {
            if (is_value_empty())
                value = str;
            else
                value = value + "|" + str;
        }
        bool is_value_empty()
        {
            return value == "";
        }
        string get_value()
        {
            return value;
        }
        void set_type(string ty)
        {
            type = ty;
        }
        string get_type()
        {
            return type;
        }
        void add_to_all_possible_chars(vector<char> elements)
        {
            for (int i = 0; i < elements.size(); i++) {
                all_possible_chars.push_back(elements[i]);
            }
        }
        vector<char> get_to_all_possible_chars()
        {
            return all_possible_chars;
        }
    private:
        string value;
        string type;
        vector<char> all_possible_chars;
};
#endif
