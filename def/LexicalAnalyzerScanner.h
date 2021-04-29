#include "./def/Imports.h"

class LexicalAnalyzerScanner
{
    public:
        vector<string> keywords;
        vector<string> punctuations;
        void scan_input(string file_name);

    private: 

        void extract_keywords(string line);
        void extract_punctuations(string line);
        string remove_spaces(string line);
};