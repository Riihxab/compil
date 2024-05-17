%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projet.tab.h"
#include "tab.h"

int ligne = 1;
int colonne = 0,j;

extern YYSTYPE yylval;

%}
%option noyywrap

commentaire "%%".*$

lettre [a-z]
chiffre [0-9]
idf [a-zA-Z][a-z0-9]*
CSTFLOAT \([+-]({chiffre}+"."{chiffre}+)\)|({chiffre}+"."{chiffre}+)
CSTINTEGER "("[+-]{chiffre}+")"|{chiffre}+
chaine \"[^"]*\"

space ("\t"|" ")+
saut "\n"+

%%
"VARGLOBAL"         {inserer(keywordTable, yytext, "KEYWORD"); printf("%s est un mot cle\n", yytext);colonne+=yyleng; yylval.str=strdup(yytext);return VARGLOBAL;}
"DECLARATION"        {inserer(keywordTable, yytext, "KEYWORD"); printf("%s est un mot cle\n", yytext) ; colonne+=yyleng; yylval.str=strdup(yytext);return DECLARATION; }
"INSTRUCTION"        {inserer(keywordTable, yytext, "KEYWORD"); printf("%s est un mot cle\n", yytext); colonne+=yyleng; yylval.str=strdup(yytext);return INSTRUCTION; }
"READ"          { inserer(keywordTable, yytext, "KEYWORD");printf("%s est un mot cle\n", yytext); colonne+=yyleng; yylval.str=strdup(yytext); return READ; }
"WRITE"         {inserer(keywordTable, yytext, "KEYWORD");printf("%s est un mot cle\n", yytext);colonne+=yyleng; yylval.str=strdup(yytext); return  WRITE; }
"FOR"           {inserer(keywordTable, yytext, "KEYWORD");printf("%s est un mot cle\n", yytext);colonne+=yyleng; yylval.str=strdup(yytext); return  FOR; }
"WHILE"         {inserer(keywordTable, yytext, "KEYWORD");printf("%s est un mot cle\n", yytext);colonne+=yyleng; yylval.str=strdup(yytext); return  WHILE;colonne+=yyleng;yylval.str=strdup(yytext); }
"IF"            {inserer(keywordTable, yytext, "KEYWORD");printf("%s est un mot cle\n", yytext); colonne+=yyleng; yylval.str=strdup(yytext);return IF;}
"ELSE"          {inserer(keywordTable, yytext, "KEYWORD");printf("%s est un mot cle\n", yytext); colonne+=yyleng; yylval.str=strdup(yytext);return  ELSE;}
"CONST"         {inserer(keywordTable, yytext, "KEYWORD");printf("%s est un mot cle\n", yytext);colonne+=yyleng; yylval.str=strdup(yytext); return  CONST; colonne+=yyleng;yylval.str=strdup(yytext);}
"INTEGER"       {inserer(keywordTable, yytext, "KEYWORD");printf("%s est un mot cle\n", yytext); colonne+=yyleng; yylval.str=strdup(yytext);return MC_INTEGER;  }
"FLOAT"         {inserer(keywordTable, yytext, "KEYWORD");printf("%s est un mot cle\n", yytext); colonne+=yyleng; yylval.str=strdup(yytext);return MC_FLOAT;}

"("                  { inserer(separatorTable, yytext, "separateur");colonne+=yyleng; yylval.str=strdup(yytext);return '('; }
")"                  { inserer(separatorTable, yytext, "separateur");colonne+=yyleng; yylval.str=strdup(yytext);return ')'; }
"{"                  { inserer(separatorTable, yytext, "separateur");colonne+=yyleng; yylval.str=strdup(yytext);return '{'; }
"}"                  { inserer(separatorTable, yytext, "separateur");colonne+=yyleng; yylval.str=strdup(yytext);return '}'; }
","                  { inserer(separatorTable, yytext, "separateur");colonne+=yyleng; yylval.str=strdup(yytext);return ','; }
";"                  {inserer(separatorTable, yytext, "separateur");colonne+=yyleng; yylval.str=strdup(yytext); return ';';}
":"                  {inserer(separatorTable, yytext, "separateur"); colonne+=yyleng; yylval.str=strdup(yytext); return ':'; }
"["                  { inserer(separatorTable, yytext, "separateur");colonne+=yyleng; yylval.str=strdup(yytext); return '['; }
"]"                  { inserer(separatorTable, yytext, "separateur");colonne+=yyleng; yylval.str=strdup(yytext); return ']' ;}


"+"  {inserer(separatorTable, yytext, "separateur");printf("addition \n");  colonne+=yyleng;  yylval.str=strdup(yytext); return '+';}
"-" { inserer(separatorTable, yytext, "separateur"); printf("soustraction \n");   colonne+=yyleng;  yylval.str=strdup(yytext); return '-';}
"*" {inserer(separatorTable, yytext, "separateur"); printf("multiplication \n");   colonne+=yyleng;  yylval.str=strdup(yytext); return '*';}
"/" {inserer(separatorTable, yytext, "separateur"); printf("division \n");   colonne+=yyleng; yylval.str=strdup(yytext); return '/';}

">="                 { inserer(separatorTable, yytext, "separateur");colonne+=yyleng;yylval.str=strdup(yytext);return GREATERTHANEQUAL; }
">"                  {inserer(separatorTable, yytext, "separateur"); colonne+=yyleng;yylval.str=strdup(yytext);return GREATERTHAN; }
"<="                 {inserer(separatorTable, yytext, "separateur"); colonne+=yyleng;yylval.str=strdup(yytext);return LESSTHANEQUAL;}
"<"                  {inserer(separatorTable, yytext, "separateur"); colonne+=yyleng;yylval.str=strdup(yytext);return LESSTHAN; }
"=="                 {inserer(separatorTable, yytext, "separateur");colonne+=yyleng;yylval.str=strdup(yytext); return EQUAL2;}
"!="                 {inserer(separatorTable, yytext, "separateur"); colonne+=yyleng;yylval.str=strdup(yytext);return NOTEQUAL; }
"="                  {inserer(separatorTable, yytext, "separateur"); colonne+=yyleng;yylval.str=strdup(yytext);return EQUAL;}
"&&"                 {inserer(separatorTable, yytext, "separateur"); colonne+=yyleng;yylval.str=strdup(yytext);return AND;}
"||"                 {inserer(separatorTable, yytext, "separateur"); colonne+=yyleng;yylval.str=strdup(yytext);return OR; }
"!"                  { inserer(separatorTable, yytext, "separateur");colonne+=yyleng;yylval.str=strdup(yytext);return NOT;}



{commentaire}  { colonne += yyleng; printf("C'est un commentaire\n"); ligne++;   }
{CSTINTEGER} {  char myStr[100]="";
                            if(yytext[0]=='(')
                             {
                             for(j=1;j<yyleng-1;j++)
                             {
                              myStr[j-1] =yytext[j];
                             }
                            
                             colonne=colonne+ strlen(yytext);
                             if (atoi(myStr) <(-32768)  || atoi(myStr)>32767  )  {printf("erreur lexical dans la ligne : %d colonne :%d \n",ligne,colonne);
                             break;}
                              printf("%s est entier signé\n" ,yytext);
                             yylval.entier= atoi(myStr);
                             return (INTEGER);
                             }
                             else {
                             colonne=colonne+ strlen(yytext);
                             if (atoi(yytext) <(-32768)  || atoi(yytext)>32767  )  {printf("erreur lexical dans la ligne : %d colonne :%d \n",ligne,colonne);
                             break;}
                             printf("%s est entier\n" ,yytext);
                             yylval.entier= atoi(yytext);
                             return (INTEGER);
                             }
                             }
{CSTFLOAT} {  char myStr[100]="";
                             if(yytext[0]=='(')
                             {
                             for(j=1;j<yyleng-1;j++)
                             {
                              myStr[j-1] =yytext[j];
                             }
                             colonne+=yyleng;
                             
                            printf("%s est reel signé\n" ,yytext);
                             yylval.reel= atof(myStr);
                            return(FLOAT);

                             }
                             else{
                             colonne+=yyleng;
                            printf("%s est reel\n" ,yytext); 
                             yylval.reel= atof(yytext);
                             return (FLOAT);
                             }
                             }

{idf}          { colonne+=yyleng;yylval.str=strdup(yytext);
                  if (yyleng > 8) {
                     printf("Erreur lexicale : la taille de l'IDF '%s' est superieure a 8 dans la ligne %d colonne %d \n", yytext, ligne, colonne);  
                      }
                      else{printf("%s est un identificateur\n", yytext); 
                                            yylval.str=strdup(yytext);
                      inserer_idf_const(yytext, "", "", -1);
                       return IDF;
                       }
  }
 {chaine}   { printf("une chaine de caractere\n"); colonne += yyleng;return CHAINE;}
{space} {colonne+=yyleng;}
{saut}  {ligne+=yyleng;}
.              { printf("Erreur lexicale ligne %d, colonne %d sur l'entite %s \n", ligne, colonne, yytext); }


