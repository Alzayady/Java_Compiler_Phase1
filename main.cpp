#include "./def/Imports.h"
#include "./def/LexicalAnalyzerScanner.h"
#include "./src/LexicalAnalyzerScanner.cpp"

int main() {
    LexicalAnalyzerScanner scanner;
    scanner.scan_input("lexical_rules.txt");
    scanner.write_output();
    cout << "DONE!" << std::endl;
    return 0;
}
