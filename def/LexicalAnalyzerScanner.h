#ifndef _LexicalAnalyzerScanner_
#define _LexicalAnalyzerScanner_

#include "imports.h"
#include "RegularDefinition.h"
#include "RegularExpression.h"

class LexicalAnalyzerScanner
{
    public:
        void scan_input(string file_name);
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
        void extract_keywords(string line);
        void extract_punctuations(string line);
        void extract_regular_definition(string line);
        void extract_regular_expression(string line);
        string remove_spaces(string line);
};
#endif
