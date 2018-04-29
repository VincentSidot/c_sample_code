
#ifndef DEF_VARIABLE

#define DEF_VARIABLE

#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_MAX_NOM 512
#define  TAILLE_MAX_VALEUR 512
#define NOMBRE_MAX_VARIABLES 512

typedef struct 
{
	char nom[TAILLE_MAX_NOM] = { 0 };
	char valeur[TAILLE_MAX_VALEUR] = { 0 };

} variable;

typedef struct 
{
	variable T[NOMBRE_MAX_VARIABLES];
	size_t nb;
} variables;

void afficher_ensemble_variable(variables *ens);
void init_variable(variables *ens);
int ajouter_variable(variables *ens, const char *nom,const char *valeur);
int trouver_et_appliquer_affectation_variable(variables *ens, const char *ligne);
char* nom_variable(variables *ens, size_t indice);
char* valeur_variable(variables *ens, size_t indice);
int trouver_variable(variables *ens, const char *nom);
void apppliquer_expansion_variables(variables * ens, char *ligne_originale, char *ligne_expansee);



#endif // !DEF_VARIABLE
