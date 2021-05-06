%{
    // Definitions
%}
  
%%
[a-zA-Z]([a-zA-Z]|[0-9])* {printf("id\n")}
digit+ | digit+ . digits ( \L | E digits) {printf("num\n")}
(==|!=|>|>=|<|<=) {printf("relop\n")}
= {printf("assign\n")}
\+|- {printf("addop\n")}
\*|/ [a-zA-Z]([a-zA-Z]|[0-9])* {printf("mulop\n")}
\n    {return 0;}
%%
  
int yywrap(){}
int main(){
  
    // Explanation:
    // yywrap() - wraps the above rule section
    /* yyin - takes the file pointer 
            which contains the input*/
    /* yylex() - this is the main flex function
            which runs the Rule Section*/
    // yytext is the text in the buffer
    
    // Uncomment the lines below 
    // to take input from file
    FILE *fp;
    char filename[50];
    printf("Enter the filename: \n");
    scanf("%s",filename);
    fp = fopen(filename,"r");
    yyin = fp;
    
    yylex();  
    return 0;
}