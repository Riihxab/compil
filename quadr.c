#include "quadr.h"
#include <stdlib.h>
#include <stdio.h> 
#include <string.h>

extern int qc;

void quadr(char op[],char arg1[],char arg2[],char result[])
{
strcpy(quad[qc].op,op);
strcpy(quad[qc].arg1,arg1);
strcpy(quad[qc].arg2,arg2);
strcpy(quad[qc].result,result);
qc++;
} 


void update_quad(int num_quad, int column_quad, char val[]) {
switch (column_quad) {
case 0: strcpy(quad[num_quad].op,val); break;
case 1: strcpy(quad[num_quad].arg1,val); break;
case 2: strcpy(quad[num_quad].arg2,val); break;
case 3: strcpy(quad[num_quad].result,val); break;
}
}



void print_quad()
{
printf("*********************Les quadruplets***********************\n");
int i;
for(i=0;i<qc;i++)
{
printf("\n %d - ( %s , %s , %s , %s )",i,quad[i].op,quad[i].arg1,quad[i].arg2,
quad[i].result);
printf("\n______________________________\n");
}
}


//fonction pour empiler daans la pile
void empiler_Pile(pile **p,int donne){
	pile *new;
	char str[10];
	new=(pile*)malloc(sizeof(pile));
	sprintf(str,"%d",donne);
	new->donnee=strdup(str);
	new->prc=*p;
	*p=new;
}
//fonction pour dépiler 
char* depiler_Pile(pile**p){
	char *res;
	pile *H;
	H=*p;
	res=strdup(H->donnee);
	*p=H->prc;
	free(H);
	return res;
}

// tranformer un entier en string
char* tostr(int m){ 
    char s[15];
    sprintf(s,"%d",m);
    return strdup(s);
}

//************************************************partie optimisation***********************

//fonction pour la propagation des copies 
/*void OptPropCopie(qdr * quad) //meme fonction pour propagation d'expression
{
    int i, j, k;

    for (i = 0; quad[i].op[0] != '\0'; i++) {
        if (strcmp(quad[i].op, "=") == 0 && strcmp(quad[i].arg1, "") != 0) {
            for (j = i + 1; quad[j].op[0] != '\0'; j++) {
                if (strcmp(quad[i].result, quad[j].arg1) == 0) {
                    strcpy(quad[j].arg1, quad[i].arg1);
                } else if (strcmp(quad[i].result, quad[j].arg2) == 0) {
                    strcpy(quad[j].arg2, quad[i].arg1);
                }
            }

            // Supprimer le quadruplet i
            for (k = i; quad[k].op[0] != '\0'; k++) {
                strcpy(quad[k].op, quad[k + 1].op);
                strcpy(quad[k].arg1, quad[k + 1].arg1);
                strcpy(quad[k].arg2, quad[k + 1].arg2);
                strcpy(quad[k].result, quad[k + 1].result);
            }
        }
    }
    }
*/
/*
void OptPropCopie(qdr *quad) {
    for (int i = 0; quad[i].op[0] != '\0'; i++) {
        if (strcmp(quad[i].op, "=") == 0 && strcmp(quad[i].arg1, "") != 0) {
            for (int j = i + 1; quad[j].op[0] != '\0'; j++) {
                if (strcmp(quad[i].result, quad[j].arg1) == 0) {
                    strcpy(quad[j].arg1, quad[i].arg1);
                } else if (strcmp(quad[i].result, quad[j].arg2) == 0) {
                    strcpy(quad[j].arg2, quad[i].arg1);
                }
            }
            // Supprimer le quadruplet i
            for (int k = i; quad[k].op[0] != '\0'; k++) {
                strcpy(quad[k].op, quad[k + 1].op);
                strcpy(quad[k].arg1, quad[k + 1].arg1);
                strcpy(quad[k].arg2, quad[k + 1].arg2);
                strcpy(quad[k].result, quad[k + 1].result);
            }
        }
    }
}
*/

/*void OptPropCopie(qdr *quad) {
    for (int i = 0; quad[i].op[0] != '\0'; i++) {
        if (strcmp(quad[i].op, "=") == 0 && strcmp(quad[i].arg1, "") != 0) {
            char result[100];
            strcpy(result, quad[i].result);
            
            // Parcourir les quadruplets suivants
            for (int j = i + 1; quad[j].op[0] != '\0'; j++) {
                if (strcmp(quad[j].arg1, result) == 0) {
                    strcpy(quad[j].arg1, quad[i].arg1);
                }
                if (strcmp(quad[j].arg2, result) == 0) {
                    strcpy(quad[j].arg2, quad[i].arg1);
                }
                if (strcmp(quad[j].result, result) == 0) {
                    strcpy(quad[j].result, quad[i].arg1);
                }
            }
        }
    }
}
*/


// la fonction pour optimiser 
void optimiser(){ // fonction qui appel toutes les fonctions d'optimisations
   
    OptSimplifAlg(quad);
    OptPropCopie(quad);
    OptExpRedondantes(quad); 
      
    int i=0;
    for(i=0;i<qc-1;i++)
    {
        if(strcmp(quad[i].op,"")==0)
        {
            int j = 0;
            for(j=i;j<qc-1;j++)
            {
                quad[j].op==strdup(quad[j+1].op);
                quad[j].arg1==strdup(quad[j+1].arg1);
                quad[j].arg2==strdup(quad[j+1].arg2);
                quad[j].result==strdup(quad[j+1].result);
            }
            qc--;
        }
    } 
}


//fonction pour la propagation des copies 
void OptPropCopie(qdr * quad) //meme fonction pour propagation d'expression
{
    int i=0;
    for (i=0;i<qc;i++)
    {
        if(quad[i].op[0]=='=')
        {
            int k=0;
            for(k=i+1;k<qc;k++)
            {
                if(strcmp(quad[i].arg1,quad[k].result)==0 || strcmp(quad[i].result,quad[k].result)==0)
                    break;
                if(quad[k].op[0]=='+' || quad[k].op[0]=='*' || quad[k].op[0]=='-' || quad[k].op[0]=='/' || quad[k].op[0]=='^' )
                {
                    if(strcmp(quad[i].result,quad[k].arg1)==0)
                    {
                        quad[k].arg1==strdup(quad[i].arg1);
                        quad[i].op==strdup("");
                        quad[i].arg1==strdup("");
                        quad[i].arg2==strdup("");
                        quad[i].result==strdup("");
                    }
                    else if(strcmp(quad[i].result,quad[k].arg2)==0)
                    {
                         quad[k].arg2==strdup(quad[i].arg1);
                        quad[i].op==strdup("");
                        quad[i].arg1==strdup("");
                        quad[i].arg2==strdup("");
                        quad[i].result==strdup("");
                    }
                }
            }
        }
    }
}
//fonction simplifiaction algébrique
void OptSimplifAlg(qdr *quad)
{
    int i=0;
    for (i=0;i<qc;i++)
    {
        if(quad[i].op[0]=='*') //exemple A*2 ==> A+A
        {
            if(quad[i].arg1[0]=='2') // cas 2*A ==> (+,A,A,X)
            {
                quad[i].op==strdup("+");
                quad[i].arg1==strdup(quad[i].arg2);
                quad[i].arg2==strdup(quad[i].arg2);
            }
            else if (quad[i].arg2[0]=='2') // cas A*2 ==> tweli (+,A,A,X)
            {
                quad[i].op==strdup("+");
                quad[i].arg1==strdup(quad[i].arg1);
                quad[i].arg2==strdup(quad[i].arg1);
            }
        }
        //Calcul inutile
        if(quad[i].op[0]=='+'){ // x=A+0 ==> (+,A,0,T1),(=,T1,,B)
                    if(strcmp(quad[i].arg1,"0")==0 ){     // cas ou 0 est dans le 2eme champs des quads(op1)==>(+,0,A,T1) 
                    int k=0;
                    for(k=i+1;k<qc;k++)
                    {   if(quad[k].op[0]=='=' && strcmp(quad[i].result,quad[k].arg1)==0){ //(=,T1,,B) ==> (=,A,,B)
                        quad[k].arg1==strdup(quad[i].arg2);
                        quad[i].op==strdup("");    //supprime loperation inutile 
                        quad[i].arg1==strdup("");
                        quad[i].arg2==strdup("");
                        quad[i].result==strdup("");
                        }
                    }
                }
        else if(strcmp(quad[i].arg2,"0")==0 ){ // ccas ou 0 est dans le 3eme champs des quads(op2)(+,A,0,T1)
                    int k=0;
                    for(k=i+1;k<qc;k++)
                    {   if(quad[k].op[0]=='=' && strcmp(quad[i].result,quad[k].arg1)==0){ //(=,T1,,B) ==> (=,A,,B)
                        quad[k].arg1==strdup(quad[i].arg1);
                        quad[i].op==strdup("");    //supprime loperation inutile 
                        quad[i].arg1==strdup("");
                        quad[i].arg2==strdup("");
                        quad[i].result==strdup("");
                        }
                    }
                }
        }

            
        // cas : x=a-a ==> (-,A,A,T1);(=,T1,,X)
        if(quad[i].op[0]=='-'){ 
            if(strcmp(quad[i].arg1,quad[i].arg2)==0){ //comparer si op1 && op2 identiques
                 int k=0;
                 for(k=i+1;k<qc;k++)
            {       if(quad[k].op[0]=='=' && strcmp(quad[i].result,quad[k].arg1)==0){ //comparer si T1 existe dans l'affectation 
                        quad[k].arg1==strdup("0");    // (=,T1,,X) ==> (=,0,,X)
                        quad[i].op==strdup("");    //supprime loperation inutile du moins
                        quad[i].arg1==strdup("");
                        quad[i].arg2==strdup("");
                        quad[i].result==strdup("");
                        
            }
                           
           
                
            }
        }
    }
}
}
//fonction des expressions redondantes 
void OptExpRedondantes(qdr * q)
{
    int i=0;
    for (i=0;i<qc;i++)
    {
        if(q[i].op[0]=='+' || q[i].op[0]=='-' || q[i].op[0]=='*' || q[i].op[0]=='/') //verifier tout les quads arithmetiques
        {
            int k=0;
            for(k=i+1;k<qc;k++)
            {
            if(strcmp(q[i].op,q[k].op)==0 && strcmp(q[i].arg1,q[k].arg1)==0 && strcmp(q[i].arg2,q[k].arg2)==0)// vérifier si les champs opr,op1,op2 sont identiques dans les 2 quads
                {   
                        int jz;
                         for(jz=k+1;jz<qc;jz++){
                         if(q[jz].op[0] == '=' && strcmp(q[k].result,q[jz].arg1)==0){
                                q[jz].arg1==strdup(q[i].result); //suprrimer le quad inutile
                                q[k].op==strdup("");
                                q[k].arg1==strdup("");
                                q[k].arg2==strdup("");
                                q[k].result==strdup("");
                                }
                         }
                }
            }
        }
    }
}
