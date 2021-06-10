#include "../def/RegularDefinition.h"

RegularDefinition::RegularDefinition(){
    value = "";
    type = "";
}
void RegularDefinition::set_value(string val)
{
    value = val;
}
void RegularDefinition::append_to_redef_value(string str)
{
    if (is_value_empty())
        value = str;
    else
        value.append("|" + str);
}
bool RegularDefinition::is_value_empty()
{
    return value == "";
}
string RegularDefinition::get_value()
{
    return value;
}
void RegularDefinition::set_type(string ty)
{
    type = ty;
}
string RegularDefinition::get_type()
{
    return type;
}
