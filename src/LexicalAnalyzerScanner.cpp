#include "../def/LexicalAnalyzerScanner.h"


void LexicalAnalyzerScanner::scan_input(string file_name)
{
    fstream input_file;
    input_file.open (file_name, ios::out | ios::in);
    string line;


    if (input_file.is_open()){
        while (getline(input_file, line))
        {
            cout << line << endl;
            if (line.find("=") < line.size())
            {
                line = remove_spaces(line);
                extract_regular_definition(line);
            }
            else if (line.find(":") < line.size())
            {
                line = remove_spaces(line);
                extract_regular_expression(line);
            }
            else if (line[0] == '{')
            {
                extract_keywords(line);
            }
            else if (line[0] == '[')
            {
                extract_punctuations(line);
            } 
        }
    }
    input_file.close();
}
string LexicalAnalyzerScanner::remove_spaces(string line)
{
    string str = line;
    int index = 0, pos = 0;
    while ((index = str.find(" ", pos)) < line.size())
    {
        str.replace(index, 1, "" );
        pos = index + 1;        // or just index without adding 1??
    }
    return str;
}

void LexicalAnalyzerScanner::extract_regular_definition(string line)
{

}
void LexicalAnalyzerScanner::extract_regular_expression(string line)
{

}

void LexicalAnalyzerScanner::extract_keywords(string line)
{
    string str = line;
    str = str.substr(1, (int) str.size() - 2);
    cout<< str<<endl;

    stringstream ss(str);
    string token;
    while (ss >> token)
    {
        if (token == "")
            continue;
        add_to_keywords(token);
    }
}

void LexicalAnalyzerScanner::extract_punctuations(string line)
{
    string str = line;
    str = str.substr(1, (int) str.size() - 2);

    stringstream ss(str);
    string token;
    while (ss >> str)
    {
        if (token == "")
            continue;
        add_to_punctuations(token);
    }
}
