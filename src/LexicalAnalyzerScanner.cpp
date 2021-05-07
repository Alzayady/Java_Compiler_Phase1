#include "../def/LexicalAnalyzerScanner.h"
#include "../analyze_to_tokens/LexicalAnalyzer.h"

void LexicalAnalyzerScanner::scan_lexical_rules_file(string file_name)
{
    fstream input_file;
    input_file.open (file_name, ios::out | ios::in);
    string line;


    if (input_file.is_open()){
        while (getline(input_file, line))
        {
            if (line[0] == '{')
            {
                extract_keywords(line);
            }
            else if (line[0] == '[')
            {
                extract_punctuations(line);
            } 
            else if (line.find(':') < line.size())
            {
                line = remove_spaces(line);
                extract_regular_expression(line);
            }

            else if (line.find('=') < line.size())
            {
                line = remove_spaces(line);
                extract_regular_definition(line);
            }

        }
    }
    reverse(regular_expressions.begin(), regular_expressions.end());
    convert_strings_to_regular_expressions(punctuations);
    convert_strings_to_regular_expressions(keywords);
    reverse(regular_expressions.begin(), regular_expressions.end());
    input_file.close();
}
void LexicalAnalyzerScanner::scan_input_program(string file_name)
{
    fstream input_file;
    input_file.open (file_name, ios::out | ios::in);
    string line;

    if (input_file.is_open()){
        while (getline(input_file, line))
        {
            string str = line;
            stringstream ss(str);
            string token;
            while (getline(ss, token, ' '))
            {
                if (token == "") 
                    continue;
                cout << token +"\t" ;
            }
            cout << endl;
        }
    }
}
void LexicalAnalyzerScanner::write_lexical_output()
{
    fstream output_file;
    output_file.open ("../out_testing.txt", ios::out | ios::trunc);
    output_file << "Regular Definitions" <<endl;
    output_file << "Type\t\tValue" <<endl;
    vector<RegularDefinition> rd = get_regular_definitions();
    for(int i = 0; i< rd.size(); i++)
    {
        output_file << rd[i].get_type() + "\t\t" + rd[i].get_value() << "" <<endl;
    }
    output_file << "Regular Expressions" <<endl;
    output_file << "Type\t\tValue" <<endl;
    vector<RegularExpression> re = get_regular_expressions();
    for(int i = 0; i< re.size(); i++)
    {
        output_file << re[i].get_type() + "\t\t" + re[i].get_value() << "" <<endl;
    }
    output_file << "Keywords" <<endl;
    vector<string> kw = get_keywords();
    for(int i = 0; i< kw.size(); i++)
    {
        output_file << kw[i] << "" <<endl;
    }
    output_file << "Punctuations" <<endl;
    vector<string> p = get_punctuations();
    for(int i = 0; i< p.size(); i++)
    {
        output_file << p[i] << "" <<endl;
    }

    output_file.close();
}
string LexicalAnalyzerScanner::remove_spaces(string line)
{
    string str = line;
    int index = 0, pos = 0;
    while ((index = str.find(' ', pos)) < line.size())
    {
        str.replace(index, 1, "" );
        pos = index + 1;        // or just index without adding 1??
    }
    return str;
}
void LexicalAnalyzerScanner::convert_strings_to_regular_expressions(vector<string> words)
{
    vector<RegularExpression>  res;
    for(int i = 0; i < words.size(); i++)
    {
        RegularExpression re;
        string word = words[i], value="(";
        string temp = word;
        if(word.size()==2 && word[0]=='\\')
            temp = word.substr(1,word.size()-1);
        re.set_type(temp);
        for(int j = 0; j< word.size(); j++)
        {
            value = value + word[j];
            if(word[j]=='\\' &&!(j>0 && word[j-1]=='\\'))
                continue;
            if(j != word.size()-1)
                value.append("&");
        }
        value.append(")");
        re.set_value(value);
        add_to_regular_expressions(re);
    }
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

        start_index = end_index + 1;
        /*
            if it's the last iteration, do this:
        */
        if (j == or_operators_indices.size() - 1)
        {
            elements = extract_elements_of_redef(redef_value, start_index, redef_value.size());
            update_regular_definition_value(redef, redef_value, elements, start_index);
        }
    }
    add_to_regular_definitions(redef);
}
void LexicalAnalyzerScanner::extract_regular_expression(string line)
{
    RegularExpression regex;
    has_definitions = false;
    int delimeter_index = line.find(':');
    string regex_type = line.substr(0, delimeter_index);
    string regex_value = line.substr(delimeter_index + 1, line.size() - delimeter_index);
    regex.set_type(regex_type);
    vector<RegularDefinition> regular_definitions = get_regular_definitions();
    sort(regular_definitions.begin(), regular_definitions.end());
    for (int i = 0; i < regular_definitions.size(); i++)
    {
        RegularDefinition regular_definition = regular_definitions[i];
        string redef_type = regular_definition.get_type();
        string replacement = regular_definition.get_value();
        regex_value = switch_positive_to_kleene_closure(regex_value, redef_type);
        regex_value = replace_regular_definitions(regex_value, redef_type, replacement);
    }

    regex_value = handle_special_symbols(regex_value);
    regex_value = handle_special_cases(regex_value);

    regex.set_value(regex_value);
    add_to_regular_expressions(regex);    
}

void LexicalAnalyzerScanner::extract_keywords(string line)
{
    string str = line;
    str = str.substr(1, str.size() - 2);
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
    str = str.substr(1, str.size() - 2);

    stringstream ss(str);
    string token;
    while (getline(ss, token, ' '))
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
vector<char> LexicalAnalyzerScanner::extract_elements_of_redef(string redef_value, int start_index, int end_endex)
{
    vector<char> res;
    string str = redef_value.substr(start_index, end_endex - start_index);
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
string LexicalAnalyzerScanner::convert_char_elements_to_str(vector<char> elements)
{
    string res = "";
	for (int i = 0; i < elements.size(); i++)
    {
		res = res + elements[i] ;
		if (i < elements.size() - 1)
        {
			res = res + "|";
		}
	}

	res = "(" + res + ")";
    return res;
}
void LexicalAnalyzerScanner::update_regular_definition_value(RegularDefinition &redef, 
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
                redef.append_to_redef_value(replacement + "&" + replacement + "*");
            }
            else if(type == redef_value.substr(start_index, type.size()))
            {
                string temp_s = redef.get_value();
                redef.append_to_redef_value(replacement);

            }
        }
    }
    else
    {
        string res = convert_char_elements_to_str(elements);
        redef.append_to_redef_value(res);
    }
}
string LexicalAnalyzerScanner::switch_positive_to_kleene_closure(string line, string redef_type)
{
        string value = line;
        int index = 0, last_found = 0;
        while ((index = value.find(")+", last_found)) < value.size())
        {
            int start_index;
            for (int j = index; j >= 0; j--)
            {
                if (value[j] == '(') {
                    start_index = j;
                    break;
                }
            }
            string trimmed_value = value.substr(start_index, index - start_index + 1);
            value.replace(start_index, index - start_index + 2, trimmed_value + "&" + trimmed_value + "*");
            last_found = index + 1;
        }

        last_found = 0;
        while ((index = value.find(redef_type + "+", last_found)) < value.size()) {
            value.replace(index, redef_type.size() + 1, redef_type + redef_type + "*");
            last_found = index + 1;
        }

        return value;
}
string LexicalAnalyzerScanner::replace_regular_definitions(string line, string redef_type, string replacement)
{
    string res_value = line;
    int index = 0, last_found = 0;
    while ((index = res_value.find(redef_type, last_found)) < res_value.size())
    {
        has_definitions = true;
        //check if the regular definition has or operator
        if (replacement.find(")|") < replacement.size()){
            res_value.replace(index, redef_type.size(), "(" + replacement + ")" + "&");
        }
        else {
            res_value.replace(index, redef_type.size(), replacement + "&");
        }

        last_found = index + 1;
    }
    return res_value;
}
string LexicalAnalyzerScanner::handle_special_symbols(string regex_value)
{
string res_value = regex_value;
    int index =0, last_found = 0;
    while ((index = res_value.find("\\L", last_found)) < res_value.size())
    {
        // DO NOTHONG UNTIL ANY UPDATES
        last_found = index + 2;
    }

    last_found = 0;
    while ((index = res_value.find("\\", last_found)) < res_value.size())
    {
        if(index<res_value.size()-1 && res_value[index+1]=='L')
        {
            //do nothing
        }
        else
        {
            res_value.replace(index, 1, "" );
        }
        last_found = index + 1;
    }

    if (!has_definitions)
    {
        res_value = add_backslash_before_symbol(res_value, "*");
        //res_value = add_backslash_before_symbol(res_value, "+");
        res_value = add_backslash_before_symbol(res_value, "&");
        last_found = 0;
        while ((index = res_value.find("|", last_found)) < res_value.size()) {
            if (index - last_found > 1){
                res_value = add_concatenation_symbol(res_value, last_found, index - last_found);
            }
            last_found = index + 1;
        }
        if (last_found != 0){
            res_value = add_concatenation_symbol(res_value, last_found, res_value.size() - last_found + 1);
        }
    }
    return res_value;
}
string LexicalAnalyzerScanner::handle_special_cases(string regex_value)
{
    string res_value = regex_value;
    int index = 0, last_found = 0;
    while ((index = res_value.find("&)", last_found)) < res_value.size())
    {
        res_value.replace(index, 2, ")");
        last_found = index + 1;
    }

    last_found = 0;
    while ((index = res_value.find("&*", last_found)) < res_value.size())
    {
        res_value.replace(index, 2, "*");
        last_found = index + 1;
    }

    last_found = 0;
    while ((index = res_value.find("&|", last_found)) < res_value.size())
    {
        res_value.replace(index, 2, "|");
        last_found = index + 1;
    }

    /*
        ex. )(--> )&(
    */
    string temp = res_value;
    for (int i = 1; i < temp.size(); i++)
    {
        if (temp[i] == '(')
        {
            if (temp[i - 1] != '(' && temp[i - 1] != '|' && temp[i - 1] != '&')
            {
                res_value = "";
                for (int j = 0; j < i; j++)
                {
                    res_value.push_back(temp[j]);
                }
                res_value.push_back('&');
                for (int j = i; j <  temp.size(); j++)
                {
                    res_value.push_back(temp[j]);
                }
                temp = res_value;
           }
        }
        if (temp[i] == ')' && i !=  temp.size() - 1)
        {
            if (temp[i + 1] != '|' && temp[i + 1] != '*' && temp[i + 1] != '&'  && temp[i + 1] != ')')
            {
                res_value = "";
                for (int j = 0; j <= i; j++)
                {
                    res_value.push_back(temp[j]);
                }
                res_value.push_back('&');
                for (int j = i + 1; j <  temp.size(); j++)
                {
                    res_value.push_back(temp[j]);
                }
                temp = res_value;
           }
        }
    }

    /*
        ex. A*() ---> A*&()
    */
    last_found = 0;
    while ((index = res_value.find("*(", last_found)) < res_value.size())
    {
        string left = res_value.substr(0, index);
        string right = res_value.substr(index + 1, res_value.size() - index - 1);
        res_value = left + "*&" + right;
        last_found = index + 2;
    }

    /*
        ex. A*B ---> A*&B
    */
    last_found = 0;
    while ((index = res_value.find("*", last_found)) < res_value.size())
    {
        if (index !=  res_value.size() - 1){
            if (res_value[index + 1] != ')' && res_value[index + 1] != '|' && res_value[index + 1] != '&'){
                string left = res_value.substr(0, index + 1);
                string right = res_value.substr(index + 1, res_value.size() - index - 1);
                res_value = left + "&" + right;
            }
        }
        last_found = index + 1;
    }

    /*
        ex. A& --> A
    */
    if (res_value[res_value.size() - 1] == '&') {
        res_value.replace(res_value.size() - 1, 1, "");
    }

    return res_value;
}
string LexicalAnalyzerScanner::add_backslash_before_symbol(string line, string symbol)
{
    string res_str = line;
    int index =0, last_found = 0;
    while ((index = res_str.find(symbol, last_found)) < res_str.size())
    {
        res_str.replace(index, 1, "\\" + symbol );
        last_found = index + 2;
    }
    return res_str;
}
/*
    ex. ==|!=|>|>=|<|<= ---> =&=|!&=|>|>&=|<|<&=
*/
string LexicalAnalyzerScanner::add_concatenation_symbol(string line, int st, int length)
{
    string str = line;
    int index = st, i = length - 1;
    while (i > 0)
    {
        string left_part = str.substr(0, index + 1);
        if (left_part[left_part.size() - 1] == '\\')
        {
            i--;
            continue;
        }
        string right_part = str.substr(index + 1, str.size() - index);
        str = left_part + '&' + right_part;
        index += 2;
        i--;
    }
    return str;
}
