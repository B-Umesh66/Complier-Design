%{
#include "node.h"
#include "y.tab.h"
%}

LETTER [A-Za-z]
DIGIT [0-9]
IF "if"
ELSE "else"
WHILE "while"

%%
{LETTER}			{snprintf(yylval.id, sizeof(yylval.id), "%s", yytext); return LETTER;}
{DIGIT}+"."{DIGIT}+	{snprintf(yylval.id, sizeof(yylval.id), "%s", yytext); return FLOAT;}
{DIGIT}+ 			{snprintf(yylval.id, sizeof(yylval.id), "%s", yytext); return INTEGER;}
{IF} 				{return IF;}
{ELSE} 				{return ELSE;}
{WHILE}				{return WHILE;}
[ \t\n]*	 			;
"end" 				{return 0;}
.					{return yytext[0];}
%%
int yywrap()
{
return 1;
}

