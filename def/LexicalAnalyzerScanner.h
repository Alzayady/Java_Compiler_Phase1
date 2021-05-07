#ifndef _LexicalAnalyzerScanner_
#define _LexicalAnalyzerScanner_

#include "imports.h"
#include "RegularDefinition.h"
#include "RegularExpression.h"
#include "../src/RegularDefinition.cpp"
#include "../src/RegularExpression.cpp"

class LexicalAnalyzerScanner
{
    public:
        bool has_definitions;
        void scan_lexical_rules_file(string file_name);
        void scan_input_program(string file_name);
        void write_lexical_output();
        void add_to_keywords(string str)
        {
            keywords.push_back(str);
        }
        vector<string> get_keywords()
        {
            return keywords;
        }
        void add_to_punctuations(string str)
        {
            punctuations.push_back(str);
        }
        vector<string> get_punctuations()
        {
            return punctuations;
        }
        void add_to_regular_definitions(RegularDefinition reg_def)
        {
            regular_definitions.push_back(reg_def);
        }
        vector<RegularDefinition> get_regular_definitions()
        {
            return regular_definitions;
        }
        void set_regular_expressions(vector<RegularExpression> re)
        {
            regular_expressions = re;
        }
        void add_to_regular_expressions(RegularExpression reg_exp)
        {
            regular_expressions.push_back(reg_exp);
        }
        vector<RegularExpression> get_regular_expressions()
        {
            return regular_expressions;
        }

    private: 
        vector<string> keywords;
        vector<string> punctuations;
        vector<RegularDefinition> regular_definitions;
        vector<RegularExpression> regular_expressions;
        vector<RegularExpression> keywords_expression;
        void extract_keywords(string line);
        void extract_punctuations(string line);
        void extract_regular_definition(string line);
        void extract_regular_expression(string line);
        string remove_spaces(string line);
        vector<int> find_all(string line, char delimeter);
        vector<char> extract_elements_of_redef(string redef_value, int start_index, int end_index);
        string convert_char_elements_to_str(vector<char> elements);
        void update_regular_definition_value(RegularDefinition &redef, string redef_value, vector<char> elements, int start_index);
        string switch_positive_to_kleene_closure(string line, string redef_type);
        string replace_regular_definitions(string line, string redef_type, string replacement);
        string handle_special_symbols(string regex_value);
        string handle_special_cases(string regex_value);
        string add_backslash_before_symbol(string line, string symbol);
        string add_concatenation_symbol(string line, int st, int length);
        void convert_strings_to_regular_expressions(vector<string> words);
};
#endif