#define QUADR_H



#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

typedef struct {
char op[100];
char arg1[100];
char arg2[100];
char result[100];
} qdr;

qdr quad[1000];

typedef struct element_pile{
	char *donnee;
	struct element_pile *prc;
}pile;


pile *pile1,*pile2;

void quadr(char *opr,char *op1,char *op2,char *res);
void update_quad(int num_quad, int colon_quad, char *val );
void print_quad();
char* depiler_Pile(pile**p);
void empiler_Pile(pile **p,int donne);
char* tostr(int m);
void OptPropCopie(qdr * quad);
void optimiser();
void OptSimplifAlg(qdr *quad);
void OptExpRedondantes(qdr * q);