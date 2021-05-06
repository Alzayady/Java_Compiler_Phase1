/* Declarations */

%{
	#include <stdio.h>
%}

/* regular definitions */

letter  [A-Za-z]
digit   [0-9]
id      ({letter})({letter}|{digit})*
digits  {digit}+
num     {digit}+|(({digit}+).({digits})((E)({digits})))
relop   ["=="|"!="|">"|">="|"<"|"<="]
addop   [+|-]
mulop   [*|/]
assign  (=)
boolean (b)(o){2}(l)(e)(a)(n)


/* Rules */

%%

(boolean) {printf("boolean\n");}
(int)     {printf("int\n");}
(float)   {printf("float\n");}
(if)      {printf("if\n");}
(else)    {printf("else\n");}
(while)   {printf("while\n");}
{assign}  {printf("assign\n");}

{num}     {printf("num\n");}
{id}      {printf("id\n");}
{relop}   {printf("relop\n");}
{addop}   {printf("addop\n");}
{mulop}   {printf("mulop\n");}


"("       {printf("(\n");}
")"       {printf(")\n");}
"{"       {printf("{\n");}
"}"       {printf("}\n");}
";"       {printf(";\n");}
","       {printf(",\n");}

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
    
    FILE *fp;
    char filename[50] = "testing_program.txt";
    fp = fopen(filename,"r");
    yyin = fp;
    
    yylex();  
    return 0;
}