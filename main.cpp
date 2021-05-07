#include "./def/Imports.h"
#include "./def/LexicalAnalyzerScanner.h"
#include "./src/LexicalAnalyzerScanner.cpp"
#include "./NFA/NFA_Generator.h"
#include "./NFA/NFA_Generator.cpp"

int main() {
    cout <<"HELLO WORLD" << endl;
    freopen("./out.txt", "w", stdout);
    LexicalAnalyzerScanner scanner;
    /*
        reading lexical rules
    */
    scanner.scan_lexical_rules_file("./lexical_rules.txt");
    scanner.write_lexical_output();
    /*
        generating NFA out of regular expressions
    */
    //I will remove this from the main function once we are satisfied with our model.
    cout <<"HELLO WORLD" << endl;
    vector<RegularExpression> regular_expressions = scanner.get_regular_expressions();
    NFA_Generator nfa_genarator;
    for(int i =0; i < regular_expressions.size(); i++)
    {
        RegularExpression re = regular_expressions[i];
        string value = re.get_value();
        nfa_genarator.add_expression(re.get_type(), value);
    }
    cout <<"HELLO" << endl;

    LexicalAnalyzer* lexicalAnalyzer = nfa_genarator.go();
    /*
        converting NFA to its equivalent DFA
    */
    /*
        minimizing DFA
    */
    /*
        reading programs to be tested
    */
    //scanner.scan_input_program("testing_program.txt");
    fstream input_file;
    input_file.open ("testing_program.txt", ios::out | ios::in);
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
                vector<Token * > tokens = lexicalAnalyzer->convert(token);
                for(auto it : tokens){
                    cout<<it->toString()<<endl;
                }
            }
        }
    }
    cout << "DONE!" << std::endl;
    return 0;
}
