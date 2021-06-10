#include "../def/Imports.h"
#include "../def/LexicalAnalyzerScanner.h"
#include "Phase2/userInterface/File.h"
#include "Phase2/FirstAndFollowTester.h"

int main() {
    freopen("../out.txt", "w", stdout);
    LexicalAnalyzerScanner scanner;
    /*reading lexical rules*/
    scanner.scan_lexical_rules_file("../lexical_rules.txt");
    /*writing extracted regular expressions to out_testing.txt*/
    scanner.write_lexical_output("../out_testing.txt");
    /*
     *generating NFA out of regular expressions
     *converting NFA to its equivalent DFA
     *minimizing DFA
    */
    scanner.build_automata();

    freopen("../out2.txt", "w", stdout);

 //   FirstAndFollowTester firstAndFollowTester;
//    firstAndFollowTester.unit_test();
    File file("../input2.txt");
    try{
        file.go();
    } catch (std::string line) {
        std::cout << "Error in input file please review it and try again." << std::endl;
        std::cout << "In line " + line << std::endl;
    }

    /*
     *reading programs to be tested
     *writing tokens to out.txt
    */

    scanner.write_tokens_of("../testing_program2.txt");
    InputMatcher::getInstance().match("$");
    cout << "DONE!" << std::endl;
    return 0;
}
