#ifndef _RegularDefinition_
#define _RegularDefinition_

#include "Imports.h"

class RegularDefinition
{

    public:
        RegularDefinition();
        void append_to_redef_value(string str);
        bool is_value_empty();
        string get_value();
        void set_type(string ty);
        string get_type();
        bool operator < (RegularDefinition rd) {
            return (rd.get_type().size() < type.size());
        }

    private:
        string value;
        string type;
};
#endif