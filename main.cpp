#include "./def/Imports.h"
#include "./def/LexicalAnalyzerScanner.h"
#include "./src/LexicalAnalyzerScanner.cpp"
#include "./NFA/NFA_Generator.h"

int main() {
    LexicalAnalyzerScanner scanner;
    /*
        reading lexical rules
    */
    scanner.scan_lexical_rules_file("lexical_rules.txt");
    scanner.write_lexical_output();
    /*
        generating NFA out of regular expressions
    */
    //I will remove this from the main function once we are satisfied with our model.
    vector<RegularExpression> regular_expressions = scanner.get_regular_expressions();
    NFA_Generator nfa_genarator;
    for(int i =0; i < regular_expressions.size(); i++)
    {
        RegularExpression re = regular_expressions[i];
        string* value = &re.get_value();
        nfa_genarator.add_expression(re.get_type(),*value);
    }
    nfa_genarator.go();
    /*
        converting NFA to its equivalent DFA
    */
    /*
        minimizing DFA
    */
    /*
        reading programs to be tested
    */
    scanner.scan_input_program("testing_program.txt");
    cout << "DONE!" << std::endl;
    return 0;
}
