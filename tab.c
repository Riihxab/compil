#include "tab.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Fonction d'initialisation des tables de symboles


void initialisation()
{
  int i;
  for (i=0;i<TABLE_SIZE;i++)
  {
  
  separatorTable[i]->name=0;
    keywordTable[i]->name=0;
    separatorTable[i]->type=strdup("");
    keywordTable[i]->type=strdup("");
  }
   

  printf("initialisation termine \n");
  }


void initSymbolTables() {
    int i;

    // Initialisation de la table pour les mots-clés
    for (i = 0; i < TABLE_SIZE; i++) {
        keywordTable[i] = NULL;
    }

    // Initialisation de la table pour les identifiants et les constantes
    for (i = 0; i < TABLE_SIZE; i++) {
        idfconstTable[i] = NULL;
    }

    // Initialisation de la table pour les séparateurs
    for (i = 0; i < TABLE_SIZE; i++) {
        separatorTable[i] = NULL;
    }
}

/*void inserer(void*table, char *name, char *type) {
    unsigned int index = hash(name);
    // Vérification du pointeur de la table et insertion appropriée 


    if (table == keywordTable || table == separatorTable) {
        TableSymbol **table_keywords = (TableSymbol **)table;
        TableSymbol *new_entry = malloc(sizeof(TableSymbol));
        if (new_entry == NULL) {
            fprintf(stderr, "Erreur: Impossible d'allouer de la mémoire.\n");
            exit(EXIT_FAILURE);
        }
        new_entry->name = strdup(name);
        new_entry->type = strdup(type);
        new_entry->next = table_keywords[index];
        table_keywords[index] = new_entry;
    } else if (table == idfconstTable) {
        TableSymboli **table_identifiers = (TableSymboli **)table;
        TableSymboli *new_entry = malloc(sizeof(TableSymboli));
        if (new_entry == NULL) {
            fprintf(stderr, "Erreur: Impossible d'allouer de la mémoire.\n");
            exit(EXIT_FAILURE);
        }
        new_entry->name = strdup(name);
        new_entry->type = strdup(type);
        new_entry->next = table_identifiers[index];
        table_identifiers[index] = new_entry;
    } else {
        fprintf(stderr, "Erreur: Table non reconnue.\n");
        exit(EXIT_FAILURE);
    }
}*/
void inserer(void* table, char *name, char *type) {
    unsigned int index = hash(name);

    // Vérification du pointeur de la table et insertion appropriée
    if (table == keywordTable || table == separatorTable) {
        TableSymbol **table_keywords = (TableSymbol **)table;
        TableSymbol *entry = table_keywords[index];

        // Recherche si l'entité existe déjà dans la table
        while (entry != NULL) {
            if (strcmp(entry->name, name) == 0 && strcmp(entry->type, type) == 0) {
                // L'entité existe déjà, donc on ne fait rien
                return;
            }
            entry = entry->next;
        }

        // L'entité n'existe pas dans la table, on l'insère
        TableSymbol *new_entry = malloc(sizeof(TableSymbol));
        if (new_entry == NULL) {
            fprintf(stderr, "Erreur: Impossible d'allouer de la mémoire.\n");
            exit(EXIT_FAILURE);
        }
        new_entry->name = strdup(name);
        new_entry->type = strdup(type);
        new_entry->next = table_keywords[index];
        table_keywords[index] = new_entry;
    } else if (table == idfconstTable) {
        TableSymboli **table_identifiers = (TableSymboli **)table;
        TableSymboli *entry = table_identifiers[index];

        // Recherche si l'entité existe déjà dans la table
        while (entry != NULL) {
            if (strcmp(entry->name, name) == 0 && strcmp(entry->type, type) == 0) {
                // L'entité existe déjà, donc on ne fait rien
                return;
            }
            entry = entry->next;
        }

        // L'entité n'existe pas dans la table, on l'insère
        TableSymboli *new_entry = malloc(sizeof(TableSymboli));
        if (new_entry == NULL) {
            fprintf(stderr, "Erreur: Impossible d'allouer de la mémoire.\n");
            exit(EXIT_FAILURE);
        }
        new_entry->name = strdup(name);
        new_entry->type = strdup(type);
        new_entry->next = table_identifiers[index];
        table_identifiers[index] = new_entry;
    } else {
        fprintf(stderr, "Erreur: Table non reconnue.\n");
        exit(EXIT_FAILURE);
    }
}
void inserer_idf_const(char *name, char *type, char *code, double value) {
    unsigned int index = hash(name);
    TableSymboli *entry = idfconstTable[index];

    // Vérifier si l'identifiant existe déjà dans la table
    while (entry != NULL) {
        if (strcmp(entry->name, name) == 0) {
            // L'identifiant existe déjà, donc on ne fait rien
            return;
        }
        entry = entry->next;
    }

    // L'identifiant n'existe pas dans la table, on l'insère
    TableSymboli *newEntry = malloc(sizeof(TableSymboli));
    if (newEntry == NULL) {
        fprintf(stderr, "Erreur: Impossible d'allouer de la mémoire.\n");
        exit(EXIT_FAILURE);
    }
    newEntry->name = strdup(name);
    newEntry->code = strdup(code);
    newEntry->type = strdup(type);
    newEntry->value = value;
    newEntry->next = idfconstTable[index];
    idfconstTable[index] = newEntry;
}
/*void inserer_idf_const(char *name, char *type, char *code, double value) {
    unsigned int index = hash(name);
    TableSymboli *newEntry = malloc(sizeof(TableSymboli));
    if (newEntry == NULL) {
        fprintf(stderr, "Erreur: Impossible d'allouer de la mémoire.\n");
        exit(EXIT_FAILURE);
    }
   
    newEntry->name = strdup(name);
    newEntry->code = strdup(code);
    newEntry->type = strdup(type);
    newEntry->value = value;
    /*newEntry->next = idfconstTable[index];
    idfconstTable[index] = newEntry; 
    newEntry->next = NULL;
   
    // Insertion de la nouvelle entrée dans la table
    if (idfconstTable[index] == NULL) {
        // Si la case est vide, la nouvelle entrée devient la première
        idfconstTable[index] = newEntry;
    } else {
        // Sinon, parcourir la liste chaînée et ajouter la nouvelle entrée à la fin
        TableSymboli *current = idfconstTable[index];
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newEntry;
    }
    
    
}*/


unsigned int hash(char *str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash * 31) + *str;
        str++;
    }
    return hash % TABLE_SIZE;
}

void afficher() {
    printf("\n\n/********Table des symboles mots cles***********/\n\n");
    printf("__________________________________________\n");
    printf("\t NomEntite         |  CodeEntite        \n");
    printf("__________________________________________\n");
    afficherTable(keywordTable);
    printf("------------------------------------\n");

    printf("\n\n/*****Table des symboles separateurs**********/\n\n");
    printf("___________________________________\n");
    printf("\t NomEntite |  CodeEntite  \n");
    printf("___________________________________\n");
    afficherTable(separatorTable);

     printf("------------------------------------\n");

    printf("\n\n/*****Table des symboles idf et constants**********/\n\n");
    printf("_____________________________________________________________\n");
    printf("\t| Nom_Entite |  Code_Entite  |type_Entite   |valeur_Entite     \n");
    printf("______________________________________________________________\n");
    afficherTable(idfconstTable);
}

void afficherTable(void*table) {

    if (table == keywordTable) {
        TableSymbol **table_keywords = (TableSymbol **)table;
       
        for (int i = 0; i < TABLE_SIZE; i++) {
            TableSymbol *entry = table_keywords[i];
            while (entry != NULL) {
                printf("%27s| %12s| \n", entry->name, entry->type);
                entry = entry->next;
            }
        }
        printf("------------------------------------\n");
        } else if (table == separatorTable) {
        TableSymbol **table_separators = (TableSymbol **)table;
       
        for (int i = 0; i < TABLE_SIZE; i++) {
            TableSymbol *entry = table_separators[i];
            while (entry != NULL) {
                printf("%20s| %12s| \n", entry->name, entry->type);
                entry = entry->next;
            }
        }
       
    } else if (table == idfconstTable) {
        TableSymboli **table_identifiers = (TableSymboli **)table;
       
        for (int i = 0; i < TABLE_SIZE; i++) {
            TableSymboli *entry = table_identifiers[i];
            while (entry != NULL) {
                printf(" %18s |%15s | %12s | %12f \n", entry->name, entry->code, entry->type, entry->value);
                
                entry = entry->next;
            }
        }
        printf("------------------------------------\n");
    } else {
        fprintf(stderr, "Erreur: Table non reconnue.\n");
        exit(EXIT_FAILURE);
    }
    /*for (int i = 0; i < TABLE_SIZE; i++) {
        TableSymbol *entry = table[i];
        while (entry != NULL) {
            printf("%27s| %12s| \n", entry->name, entry->type);
            entry = entry->next;
        }
    }*/
}


void ajouter_code_idf(char *idf, char *code) {
    unsigned int index = hash(idf);
    TableSymboli *entry = idfconstTable[index];

    // Parcourir la liste chaînée pour trouver l'identifiant correspondant
    while (entry != NULL) {
        if (strcmp(entry->name, idf) == 0) {
            // Mettre à jour le code de l'identifiant
            free(entry->code); // Libérer l'ancien code s'il existe
            entry->code = strdup(code); // Mettre à jour le nouveau code
            return;
        }
        entry = entry->next;
    }

    // Si l'identifiant n'est pas trouvé, vous pouvez choisir de lever une erreur ou simplement ne rien faire
    // printf("Erreur : Identifiant '%s' non trouvé dans la table des symboles.\n", idf);
}

int double_declaration_idf(char* idf) {
    
     unsigned int index = hash(idf);

    // Recherche de l'entité dans la table des symboles
    while (idfconstTable[index]->name != NULL) {
       
            
            if (strcmp(idfconstTable[index]->type, "") == 0) {
                
                return 0; // pas Double déclaration détectée
            } else {
               
                return -1; //  double déclaration
            }
        }
        // Gestion des collisions en utilisant le linéaire probing
        index = (index + 1) % TABLE_SIZE;
    }
    
void inserer_type(char *entite, char *type) {
    unsigned int index = hash(entite);
    TableSymboli *entry = idfconstTable[index];

    // Parcourir la liste chaînée pour trouver l'entité correspondante
    while (entry != NULL) {
        if (strcmp(entry->name, entite) == 0) {
            // Mettre à jour le type de l'entité
            
            entry->type = strdup(type); // Mettre à jour le nouveau type
            return;
        }
        entry = entry->next;
    }
    }
   
char *GetCode(char*entite){
		unsigned int index = hash(entite);
    TableSymboli *entry = idfconstTable[index];
    while (entry != NULL) {
        if (strcmp(entry->name, entite) == 0) {
            // Retourner le code si l'entité est trouvée
            return entry->code;
        }
        entry = entry->next;
    }
} 
char *GetType(char *entite) {
    unsigned int index = hash(entite);
    TableSymboli *entry = idfconstTable[index];
    while (entry != NULL) {
        if (strcmp(entry->name, entite) == 0) {
            // Retourner le type si l'entité est trouvée
            return entry->type;
        }
        entry = entry->next;
    }
    return NULL;
}
void inserervaleur(char *entite, double val) {
    unsigned int index = hash(entite);
    TableSymboli *entry = idfconstTable[index];
    while (entry != NULL) {
        if (strcmp(entry->name, entite) == 0) {
            // Mettre à jour la valeur de l'entité
            entry->value = val;
            return; // Sortir de la fonction après la mise à jour
        }
        entry = entry->next;
    }
	     
    
	}

double GetValue(char* entite)
		{
		    unsigned int index = hash(entite);
    TableSymboli *entry = idfconstTable[index];
    while (entry != NULL) {
        if (strcmp(entry->name, entite) == 0) {
            // Mettre à jour la valeur de l'entité
            
            return entry->value ; // Sortir de la fonction après la mise à jour
        }
        entry = entry->next;
    }
		
	
	}