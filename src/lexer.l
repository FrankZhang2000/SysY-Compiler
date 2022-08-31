%{

#define YYSTYPE void*

#include <string>
#include "parser.tab.hpp"

using namespace std;

%}
%option yylineno

octnumber   0[0-7]+
decnumber   [0-9]+
hexnumber   (0x|0X)[0-9a-fA-F]+
identifier  [a-zA-Z_][a-zA-Z0-9_]*
newline     \n
whitespace  [ \n\t\r]+
comment1    "//".*\n
comment2    "/*"([^\*]|(\*)*[^\*/])*(\*)*"*/"

%%

"if"                {return IF;}
"else"              {return ELSE;}
"while"             {return WHILE;}
"break"             {return BREAK;}
"continue"          {return CONTINUE;}
"return"            {return RETURN;}
"int"               {return INT;}
"void"              {return VOID;}
"const"             {return CONST;}
"=="                {return EQ;}
"!="                {return NE;}
"<="                {return LE;}
">="                {return GE;}
"<"                 {return LT;}
">"                 {return GT;}
"+"                 {return PLUS;}
"-"                 {return MINUS;}
"*"                 {return TIMES;}
"/"                 {return OVER;}
"%"                 {return MOD;}
"="                 {return ASSIGN;}
"!"                 {return NOT;}
"&&"                {return AND;}
"||"                {return OR;}
"("                 {return LPAREN;}
")"                 {return RPAREN;}
"["                 {return LSQBRKET;}
"]"                 {return RSQBRKET;}
"{"                 {return LFLBRKET;}
"}"                 {return RFLBRKET;}
";"                 {return SEMI;}
","                 {return COMMA;}
{octnumber}         {
                        yylval = new int;
                        *(int *)yylval = (int)stol(yytext, 0, 8);
                        return NUM;
                    }
{decnumber}         {
                        yylval = new int;
                        *(int *)yylval = (int)stol(yytext, 0, 10);
                        return NUM;
                    }
{hexnumber}         {
                        yylval = new int;
                        *(int *)yylval = (int)stol(yytext, 0, 16);
                        return NUM;
                    }
{identifier}        {
                        yylval = new string(yytext);
                        return IDENT;
                    }
{newline}           {}
{whitespace}        {}
{comment1}          {}
{comment2}          {}
.                   {}

%%

int yywrap() {
    return 1;
}