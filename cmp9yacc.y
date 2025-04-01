%{
#include <stdio.h>
#include <stdlib.h>
%}

%token I B T A E

%%

S  : I E T S S1 { printf("Valid string\n"); }
   | A { printf("Valid string\n"); }
   ;

S1 : E S
   | /* empty */
   ;

E  : B
   ;

%%

int yyerror(char *msg) {
    printf("Invalid string\n");
    exit(0);
}

int main() {
    yyparse();
    return 0;
}
