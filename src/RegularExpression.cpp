#include "../def/RegularDefinition.h"

void RegularExpression::set_value(string val)
{
    value = val;
}
string RegularExpression::get_value()
{
    return value;
}
void RegularExpression::set_type(string ty)
{
    type = ty;
}
string RegularExpression::get_type()
{
    return type;
}
