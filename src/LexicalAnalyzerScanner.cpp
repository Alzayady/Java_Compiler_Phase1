#include "../def/LexicalAnalyzerScanner.h"


void LexicalAnalyzerScanner::scan_input(string file_name)
{
    fstream input_file;
    input_file.open (file_name, ios::out | ios::in);
    string line;


    if (input_file.is_open()){
        while (getline(input_file, line))
        {
            cout << line << endl;
            if (line.find("=") < line.size())
            {
                line = remove_spaces(line);
                extract_regular_definition(line);
            }
            else if (line.find(":") < line.size())
            {
                line = remove_spaces(line);
                extract_regular_expression(line);
            }
            else if (line[0] == '{')
            {
                extract_keywords(line);
            }
            else if (line[0] == '[')
            {
                extract_punctuations(line);
            } 
        }
    }
    input_file.close();
}
string LexicalAnalyzerScanner::remove_spaces(string line)
{
    string str = line;
    int index = 0, pos = 0;
    while ((index = str.find(" ", pos)) < line.size())
    {
        str.replace(index, 1, "" );
        pos = index + 1;        // or just index without adding 1??
    }
    return str;
}
void LexicalAnalyzerScanner::extract_regular_definition(string line)
{
    RegularDefinition redef;
    int delimeter_index = line.find('=');
    string redef_type = line.substr(0, delimeter_index);
    string redef_value = line.substr(delimeter_index + 1, line.size() - delimeter_index);
    vector<RegularDefinition> regular_definitions = get_regular_definitions();
    vector<int> or_operators_indices = find_all(redef_value, '|');
    vector<char> values;
    int start_index = 0;
    int end_index = redef_value.size();
    redef.set_type(redef_type);
    if (or_operators_indices.empty())
    {
        vector<char> elements = extract_elements_of_redef(redef_value, start_index, end_index);
        update_regular_definition_value(redef, redef_value, elements, start_index);
    }

    for (int j = 0; j < or_operators_indices.size(); j++)
    {
        end_index = or_operators_indices[j];
        vector<char> elements = extract_elements_of_redef(redef_value, start_index, end_index);
        update_regular_definition_value(redef, redef_value, elements, start_index);
        redef.add_to_all_possible_chars(elements);

        start_index = end_index + 1;
        /*
            if it's the last iteration, do this:
        */
        if (j == or_operators_indices.size() - 1)
        {
            elements = extract_elements_of_redef(redef_value, start_index, redef_value.size());
            update_regular_definition_value(redef, redef_value, elements, start_index);
            redef.add_to_all_possible_chars(elements);
        }
    }
    add_to_regular_definitions(redef);
}
void LexicalAnalyzerScanner::extract_regular_expression(string line)
{
    has_definitions = false;
    int delimeter_index = line.find(':');
    string regex_type = line.substr(0, delimeter_index);
    string value = line.substr(delimeter_index + 1, line.size() - delimeter_index);
    vector<RegularDefinition> regular_definitions = get_regular_definitions();
    sort(regular_definitions.begin(), regular_definitions.end());//WHY??
    for (int i = 0; i < regular_definitions.size(); i++)
    {
        RegularDefinition regular_definition = regular_definitions[i];
        string redef_type = regular_definition.get_type();
        string replacement = regular_definition.get_value();
        value = remove_plus_operator(value, redef_type);
        value = replace_definitions(value, redef_type, replacement);

    }

    value = handle_special_operators(value);
    value = additional_manipulations(value);

    RegularExpression regex;
    regex.set_value(value);
    regex.set_type(regex_type);
    add_to_regular_expressions(regex);    
}

void LexicalAnalyzerScanner::extract_keywords(string line)
{
    string str = line;
    str = str.substr(1, (int) str.size() - 2);
    cout<< str<<endl;

    stringstream ss(str);
    string token;
    while (ss >> token)
    {
        if (token == "")
            continue;
        add_to_keywords(token);
    }
}

void LexicalAnalyzerScanner::extract_punctuations(string line)
{
    string str = line;
    str = str.substr(1, (int) str.size() - 2);

    stringstream ss(str);
    string token;
    while (ss >> str)
    {
        if (token == "")
            continue;
        add_to_punctuations(token);
    }
}
/*
    get all indices of a delimeter in a sting
*/
vector<int> LexicalAnalyzerScanner::find_all(string line, char delimeter)
{
    vector<int> results;
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == delimeter)
            results.push_back(i);
    }
    return results;
}
/*
    a-d ----> {a, b, c, d}
*/
vector<char> LexicalAnalyzerScanner::extract_elements_of_redef(string redef_value, int start_index, int start_index)
{
    vector<char> res;
    string str = redef_value.substr(start_index, start_index - start_index);
    int negative_index = str.find("-");
    // if it contains a -ve operator ex. a-z
    if(negative_index < str.size())
    {
        char first = str[negative_index - 1];
        char last = str[negative_index + 1];
        while (first <= last) {
            res.push_back(first);
            first++;
        }
    }
    else
    {
        if (redef_value.size() == 1) res.push_back(str[start_index]);
    }
    return res;
}   
string LexicalAnalyzerScanner::conver_char_elements_to_separated_str(vector<char> elements)
{
    string res = "";
	for (int i = 0; i < elements.size(); i++) {
		res = res + elements[i] ;
		if (i < elements.size() - 1) {
			res = res + "|";
		}
	}

	res = "(" + res + ")";
    return res;
}
void LexicalAnalyzerScanner::update_regular_definition_value(RegularDefinition redef, 
string redef_value,vector<char> elements, int start_index)
{
        if (elements.empty())
        {
            for (int i = 0; i < regular_definitions.size(); i++)
            {
                RegularDefinition regular_definition = regular_definitions[i];
                string type = regular_definition.get_type();
                string replacement = regular_definition.get_value();
                if (type + "+" == redef_value.substr(start_index, type.size() + 1))
                {
                    string temp_s = redef.get_value();
                    redef.append_to_redef_value(replacement + " " + replacement + "*");
                }
                else if(type == redef_value.substr(start_index, type.size())){
                    string temp_s = redef.get_value();
                    redef.append_to_redef_value(replacement);
                }
            }
        }
        else
        {
            string res = conver_char_elements_to_separated_str(elements);
            redef.append_to_redef_value(res);
        }
}