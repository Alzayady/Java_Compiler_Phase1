#include "./def/LexicalAnalyzerScanner.h"

int main() {
    freopen("./out.txt", "w", stdout);
    LexicalAnalyzerScanner scanner;
    /*reading lexical rules*/
    scanner.scan_lexical_rules_file("./lexical_rules.txt");
    /*writing extracted regular expressions to out_testing.txt*/
    scanner.write_lexical_output("./out_testing.txt");
    /*
     *generating NFA out of regular expressions
     *converting NFA to its equivalent DFA
     *minimizing DFA
    */
    scanner.build_automata();
    /*
     *reading programs to be tested
     *writing tokens to out.txt
    */
    scanner.write_tokens_of("./testing_program.txt");
    cout << "DONE!" << std::endl;
    return 0;
}
