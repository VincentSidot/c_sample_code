#include <cstdio>
#include <cstdlib>
#include "variable.h"


int main(int argc, char** argv)
{
	variables var;
	init_variable(&var);
	trouver_et_appliquer_affectation_variable(&var, "type_voiture=berline");
	trouver_et_appliquer_affectation_variable(&var, "couleur_voiture=noir");
	trouver_et_appliquer_affectation_variable(&var, "nombreporte_voiture=4");
	afficher_ensemble_variable(&var);

	char ligne_originale[512] = { 0 };
	char ligne_expansee[512] = { 0 };

	strcpy(ligne_originale, "J'ai vue une $type_voiture avec $nombreporte_voiture portes de couleur $couleur_voiture");

	apppliquer_expansion_variables(&var, ligne_originale, ligne_expansee);

	printf("ligne originale : %s\nligne expansee : %s\n",ligne_originale,ligne_expansee);

	getchar();
	return 0;
}