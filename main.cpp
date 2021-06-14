#include "../def/Imports.h"
#include "../def/LexicalAnalyzerScanner.h"
#include "Phase2/userInterface/File.h"
#include "Phase2/def/InputMatcher.h"
/*
 * The output files of the project
 * 1- first_follow_table -> the first and follow for each non_terminalf  (made in phase_2)
 * 2- ACTION_LOGS -> THE FINAL FILE AT WHICH THE STACK METHOD IS APPLIED TO THE INPUT
 * 3- MINIMIZATION_AND_TOKENS -> THE FINAL FILE OF PHASE_1
 * 4-
 * 5-
 * IN CASE THAT YOU WANT TO DEBUG THE INPUTMATCHER.CPP, YOU CAN MAKE THE DEBUG BOOLEAN TO BE TRUE AND ADDITIONAL LOGS WILL BE PRINTED
 *
 */
int main() {
    freopen("../minimization_and_tokens.txt", "w", stdout);
    LexicalAnalyzerScanner* scanner = new LexicalAnalyzerScanner;
    /*reading lexical rules*/
    scanner->scan_lexical_rules_file("../lexical_rules.txt");
    /*writing extracted regular expressions to out_testing.txt*/
    scanner->write_lexical_output("../out_testing.txt");
    /*
     *generating NFA out of regular expressions
     *converting NFA to its equivalent DFA
     *minimizing DFA
    */
    scanner->build_automata();

    freopen("../action_logs.txt", "w", stdout);

    File* file = new File("../phase2_rules.txt");
    bool ok = true;
    try{
        file->go();
    } catch (std::string line) {
        std::cout << "Error in input file please review it and try again." << std::endl;
        std::cout << "In line " + line << std::endl;
        ok = false;
    }


    delete file;
    /*
     *reading programs to be tested
     *writing tokens to out.txt
    */
    if (ok) {
        scanner->write_tokens_of("../testing_program2.txt");
        delete scanner;
        freopen("../action_logs.txt", "a", stdout);
        InputMatcher::getInstance().match("$");
        cout << "DONE!" << std::endl;
    }
    return 0;
}
