%{
#include <stdio.h>
%}

%option noyywrap

%%

[0-9]+    { printf("%s\n", yytext); }

.         { }

%%

int main() {
    printf("Enter input string:\n");
    yylex(); // Call the lexer
    return 0;
}
