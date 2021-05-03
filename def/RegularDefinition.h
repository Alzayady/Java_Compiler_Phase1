#ifndef _RegularDefinition_
#define _RegularDefinition_

#include "Imports.h"

class RegularDefinition
{

    public:
        RegularDefinition(){
            value = "";
            type = "";
        }
        void set_value(string val)
        {
            value = val;
        }
        void append_to_redef_value(string str)
        {
            if (is_value_empty())
                value = str;
            else
                value.append("|" + str);
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
        bool operator < (RegularDefinition rd) {
            return (rd.get_type().size() < type.size());
        }

    private:
        string value;
        string type;
};
#endif