#ifndef _RegularExpression_
#define _RegularExpression_

#include "Imports.h"

class RegularExpression
{

    public:
        void set_value(string val)
        {
            value = val;
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
    private:
        string value;
        string type;
};
#endif