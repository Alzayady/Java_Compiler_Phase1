#include "Imports.h"
#include "LexicalAnalyzerScanner.h"
#include "NFA_Generator.h"

int main() {
    freopen("../out.txt", "w", stdout);
    LexicalAnalyzerScanner scanner;
    /*
        reading lexical rules
    */
    scanner.scan_lexical_rules_file("../lexical_rules.txt");
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
        string value = re.get_value();
        nfa_genarator.add_expression(re.get_type(), value);
    }
    LexicalAnalyzer* lexicalAnalyzer = nfa_genarator.go();
    vector<Token * > tokens = lexicalAnalyzer->convert("while(elzyady) { print('ana')}");
    for(auto it : tokens){
        cout<<it->toString()<<endl;
    }
    /*
        converting NFA to its equivalent DFA
    */
    /*
        minimizing DFA
    */
    /*
        reading programs to be tested
    */
    scanner.scan_input_program("../testing_program.txt");
    cout << "DONE!" << std::endl;
    return 0;
}
