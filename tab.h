#ifndef TAB_H
#define TAB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define TABLE_SIZE 100


typedef struct TableSymboli {
    char *name;   // Nom de l'identificateur ou de la constante
    char *code;     // Code pour identifier le type de l'entité (par exemple : IDF, CONST)
    char *type;   // Type de l'entité (par exemple : INTEGER, FLOAT)
    double value; // Valeur de la constante (uniquement pour les constantes numériques)
    struct TableSymboli *next; // Pointeur vers l'entrée suivante dans la table (en cas de collision)
} TableSymboli;

typedef struct TableSymbol {
    char *name;
    char *type;
    struct TableSymbol *next;
} TableSymbol;



TableSymbol *keywordTable[TABLE_SIZE];
TableSymbol *separatorTable [TABLE_SIZE];
TableSymboli *idfconstTable [TABLE_SIZE];
 
void inserer_idf_const(char *name, char *type, char *code, double value);
void initSymbolTables();
void  inserer(void *table, char *nom,  char *type);
unsigned int hash(char *str);
void afficher();
void afficherTable(void*table);
void ajouter_code_idf(char *idf, char *code);
int double_declaration_idf(char* idf);
void inserer_type(char *entite, char *type);
char *GetCode(char*entite);
void inserervaleur(char* entite, double val);
char *GetType(char *entite);
double GetValue(char* entite);
#endif