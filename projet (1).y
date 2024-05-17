%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "projet.tab.h"
#include "tab.h"
#include "quadr.h"

int yylex();
int yyerror( char *msg);
FILE *yyin;
extern int ligne, colonne;
char* sauvtype ;
int val;
int end_if=0, end_if2=0;
int branchement=0;
int begin_else=0;
int start_while=0;
int end_while=0;
int qc=0;
char tmp[20]="";
int ntemp=1;

%}

%union {
int     entier;
char*   str;
float  reel;
struct {
            char* type;
            char* res;
            }NT;
}


%token <entier> INTEGER <str> MC_INTEGER
%token <reel> FLOAT  <str> MC_FLOAT
%token CONST  CHAINE

%token <str> IDF
%token READ WRITE
%token IF
%token ELSE
%token FOR
%token WHILE
%token VARGLOBAL
%token DECLARATION
%token INSTRUCTION
%token LESSTHAN
%token LESSTHANEQUAL
%token GREATERTHAN
%token GREATERTHANEQUAL
%token EQUAL  EQUAL2
%token NOTEQUAL
%token AND
%token OR
%token NOT

%left OR
%left AND
%right NOT
%left '+' '-'
%left '*'  '/'

%left  GREATERTHAN GREATERTHANEQUAL LESSTHAN  LESSTHANEQUAL NOTEQUAL 
%type<NT>expression
%type<NT>constant
%type<NT>condition
%type<NT>expressioncomp
%type<NT>assignment


%%



program : VARGLOBAL '{' declarations '}' DECLARATION '{' declarations '}' INSTRUCTION '{' instructions '}'
        {
        printf("programme correct"); YYACCEPT;
}
        ;

declarations: declarations declaration 
            |
            ;
declaration : type variable_list ';'
            | type IDF '[' INTEGER ']' ';' {if (double_declaration_idf($2)!=0) {
                    // Si l'identifiant a deja ete declare, affichez un message d'erreur
                    printf("Erreur: L'identifiant %s est deja declare.\n", $2);
                    YYABORT; // Arrêtez l'analyse syntaxique
                } if ($4<0) {
        printf("%d:erreur: taille du tableau %s < 0 \n",ligne,$2); YYABORT;} else{
                        ajouter_code_idf($2, "idf_tab");
                         inserer_type($2,sauvtype);}}
            | CONST IDF EQUAL INTEGER ';' {if (double_declaration_idf($2)!=0) {
                    // Si l'identifiant a deja ete declare, affichez un message d'erreur
                    printf("Erreur: L'identifiant %s est deja declare.\n", $2);
                    YYABORT; // Arrêtez l'analyse syntaxique
                } else{
                        ajouter_code_idf($2, "const");
                         inserer_type($2,"INTEGER");
                         val=$4;
                         inserervaleur($2,val);
                        }}

            | CONST IDF EQUAL FLOAT ';' {if (double_declaration_idf($2)!=0) {
                    // Si l'identifiant a deja ete declare, affichez un message d'erreur
                    printf("Erreur: L'identifiant %s est deja declare.\n", $2);
                    YYABORT; // Arrêtez l'analyse syntaxique
                } else{
                        ajouter_code_idf($2, "const");
                        inserer_type($2,"FLOAT");
                        val=$4;
                        inserervaleur($2,val);
                        }}
                
            ;

type : MC_INTEGER {sauvtype=strdup($1);}
      | MC_FLOAT {sauvtype=strdup($1);}
      ;

variable_list : IDF { if (double_declaration_idf($1)!=0) {
                    // Si l'identifiant a deja ete declare, affichez un message d'erreur
                    printf("Erreur: L'identifiant %s est deja declare.\n", $1);
                    YYABORT; // Arrêtez l'analyse syntaxique
                } else{
                        ajouter_code_idf($1, "idf");
                        inserer_type($1,sauvtype);
                        }
                        }
              | variable_list ',' IDF { if (double_declaration_idf($3)!=0) {
                    // Si l'identifiant a deja ete declare, affichez un message d'erreur
                    printf("Erreur: L'identifiant %s est deja declare.\n", $3);
                    YYABORT; // Arrêtez l'analyse syntaxique
                } else{
                        ajouter_code_idf($3, "idf");
                        inserer_type($3,sauvtype);
                        }}
              ;
//*****************************partie instruction *************************************************************/


instructions : instructions instruction
             |
             ;
instruction :  assignment 
             | conditional
             | loop
             | rwinstruction
             ;

assignment : IDF EQUAL expression ';' {
        
        if(double_declaration_idf($1)==0){
                     printf("erreur Semantique: %s n'est pas declare, a la ligne %d et la colonne%d\n",$1, ligne,colonne);YYABORT;
         
         }if(strcmp(GetType($1),$3.type)!=0){ 
                        printf("erreur Semantique:incompatibilite de type  a la ligne %d et la colonne %d\n",ligne,colonne);YYACCEPT;      
         }if(strcmp("const",GetCode($1))==0){ 
                printf("erreur Semantique: %s est une constante  on peut pas la modifier, a la ligne %d et la colonne %d\n",$1,ligne,colonne);
                        YYABORT;
         } if (strcmp(GetType($1), sauvtype) != 0) {
            printf("erreur Semantique: %s ne recoit pas une valeur de son type, a la ligne %d et la colonne %d\n", $1, ligne, colonne);
            YYABORT;

        } else{inserervaleur($1,val);
        { 
          quadr("=",$3.res,"empty",$1);
}
        }
      
}

        
         ;
 
         
           
expression : expression '+' expression {$$.type=$1.type; sprintf(tmp,"T%d",ntemp); ntemp++; $$.res = strdup(tmp);   quadr("+", $1.res, $3.res, $$.res);
;  }
           | expression '-' expression {$$.type=$1.type;  sprintf(tmp,"T%d",ntemp); ntemp++; $$.res = strdup(tmp);   quadr("-", $1.res, $3.res, $$.res);  }
           | expression '*' expression {$$.type=$1.type; sprintf(tmp,"T%d",ntemp); ntemp++; $$.res = strdup(tmp);   quadr("*", $1.res, $3.res, $$.res);}
           | expression '/' INTEGER { $$.type=$1.type;  if ($3==0) {printf("erreur:ligne:%d: division par 0\n",ligne); YYABORT;}}
           | expression'/' FLOAT {$$.type=$1.type;  if ($3==0) {printf("erreur:ligne:%d: division par 0\n",ligne); YYABORT; }}
           | '(' expression ')' { $$.type=$2.type; }
           | '-' expression  { $$.type=$2.type; }
           | IDF  {$$.type=GetType($1);$$.res=strdup($1);if(double_declaration_idf($1)==0){
                     printf("erreur Semantique: %s n'est pas declare, a la ligne %d et la colonne%d\n",$1, ligne,colonne);YYABORT;
           }
         }
           |constant {$$.type=sauvtype; $$.res=$1.res;
                 }
           |expression '/' IDF {if(GetValue($3)==0){printf("%d:erreur : division par 0\n",ligne); YYABORT;}
 $$.type=$1.type;}
           ;

constant :  INTEGER {sauvtype=strdup("INTEGER"); val=$1;  sprintf(tmp, "%d", $1); // Convertir l'entier en chaîne de caractères
                     $$.res = strdup(tmp);}
           |FLOAT {sauvtype=strdup("FLOAT"); val=$1; sprintf(tmp, "%f", $1); // Convertir le flottant en chaîne de caractères
    $$.res = strdup(tmp); }
           ;
conditional :  B ELSE '{' instruction '}' {
        sprintf(tmp, "%d", qc);
        update_quad(end_if, 1, tmp);
        printf("program correct");
        YYACCEPT;
    }
    |  A '{' instruction '}' {
                            sprintf(tmp,"%d",qc);  
                            update_quad(end_if,1,tmp);
			    printf("pgm juste\n");}
;

B: A '{' instruction '}' {
        
        end_if = qc;
        
        quadr("BR", "", "empty", "empty");
        sprintf(tmp, "%d", qc);
        update_quad(begin_else, 1, tmp);
    }
;

A : IF '(' condition ')' {
        end_if = qc;
       begin_else = qc;
        quadr("BZ", "", "temp_cond", "empty");
         
    }
;
             



;                                                          


loop :  FOR '(' IDF ':' INTEGER':' INTEGER':' IDF ')' '{' 

                                                          {  
                                                                sprintf(tmp, "%d", $5); // Convertir l'entier en chaîne de caractères
                                                                      
                                                                quadr("=", strdup(tmp),"",$3);
                                                                branchement=qc;
                                                                quadr("BR","", "", "");
                                                            empiler_Pile(&pile1,qc);
                                                            sprintf(tmp, "%d", $7);
                                                        
                                                            quadr("+",$3,strdup(tmp),"temp_cond");
                                                            empiler_Pile(&pile2,qc);
                                                            update_quad(branchement, 1, tostr(qc));
                                                            quadr("BG",tostr(qc),"temp",$9); 
                                                          }
 instruction '}' {char* arg = depiler_Pile(&pile1);
quadr("BR", arg, "", "") ;char* index = depiler_Pile(&pile2);int idx = atoi(index);
update_quad(idx, 1, tostr(qc));}
     |  w co '{' instruction '}' {  

sprintf(tmp,"%d",start_while);
quadr("BR", tmp, "empty", "empty"); 
sprintf(tmp,"%d",qc);
update_quad(end_while,1,tmp);


  } ;
co: '(' condition ')' {end_while=qc;quadr("BZ", "","temp_cond", "empty");  }
     ;
w: WHILE { start_while=qc;
        }
        ;

rwinstruction : READ '(' IDF ')' ';'
              | WRITE '('  CHAINE  ',' IDF ','  CHAINE  ')' ';'
              ;

condition :expression
          |expressioncomp {$$.res=$1.res;}
          
          ;

expressioncomp:   expression GREATERTHAN expression { $$.type=$1.type;  sprintf(tmp,"T%d",ntemp); ntemp++; $$.res = strdup(tmp); quadr(">",$1.res,$3.res,$$.res)}
          | expression LESSTHAN expression  { $$.type=$1.type;  sprintf(tmp,"T%d",ntemp); ntemp++; $$.res = strdup(tmp); quadr("<",$1.res,$3.res,$$.res)}
          | expression GREATERTHANEQUAL expression { $$.type=$1.type;  sprintf(tmp,"T%d",ntemp); ntemp++; $$.res = strdup(tmp); quadr(">=",$1.res,$3.res,$$.res)}
          | expression LESSTHANEQUAL expression { $$.type=$1.type;  sprintf(tmp,"T%d",ntemp); ntemp++; $$.res = strdup(tmp); quadr("<=",$1.res,$3.res,$$.res)}
          | expression EQUAL2 expression { $$.type=$1.type;  sprintf(tmp,"T%d",ntemp); ntemp++; $$.res = strdup(tmp); quadr("==",$1.res,$3.res,$$.res)}
          |expression EQUAL expression  { $$.type=$1.type;  sprintf(tmp,"T%d",ntemp); ntemp++; $$.res = strdup(tmp); quadr("=",$1.res,$3.res,$$.res)}
          | expression NOTEQUAL expression { $$.type=$1.type;  sprintf(tmp,"T%d",ntemp); ntemp++; $$.res = strdup(tmp); quadr("!=",$1.res,$3.res,$$.res)}
          |expression AND expression { $$.type=$1.type;  sprintf(tmp,"T%d",ntemp); ntemp++; $$.res = strdup(tmp); quadr("AND",$1.res,$3.res,$$.res)}
          | expression OR expression { $$.type=$1.type;  sprintf(tmp,"T%d",ntemp); ntemp++; $$.res = strdup(tmp); quadr("OR",$1.res,$3.res,$$.res)}
          //| NOT expression
          ;


%%
int yyerror (char* msg)
{
	printf ("erreur syntaxique %s ligne: %d colonne: %d \n",msg,ligne,colonne);return 1;
}


int main() {
     initSymbolTables();
    yyin = fopen("code.txt", "r");
    yyparse();
    fclose(yyin);
    afficher();
    print_quad();
    optimiser();
	printf("---------------||LISTE QUADS APRES OPTIMISATION ||---------------\n");
    print_quad();
    return 0;
}

int yywrap() {
    return 1;
}