#ifndef _RegularExpression_
#define _RegularExpression_

#include "Imports.h"

class RegularExpression
{

    public:
        void set_value(string val);
        string get_value();
        void set_type(string ty);
        string get_type();
    private:
        string value;
        string type;
};
#endif