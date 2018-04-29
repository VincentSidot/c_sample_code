#include "variable.h"

void afficher_ensemble_variable(variables * ens)
{
	printf("Affichage des %d variables\n",ens->nb);
	for (size_t i = 0; i < ens->nb; i++)
	{
		printf("\"%s\" = \"%s\"\n", ens->T[i].nom, ens->T[i].valeur);
	}
}

void init_variable(variables * ens)
{
	ens->nb = 0;
}

int ajouter_variable(variables * ens, const char * nom, const char * valeur)
{
	size_t i = 0;

	for (; i < ens->nb; i++)
	{
		if (!strcmp(ens->T[i].nom, nom))
		{
			strcpy(ens->T[i].valeur, valeur);
			return i;
		}
	}
	if (i == NOMBRE_MAX_VARIABLES)
		return -1;
	strcpy(ens->T[i].nom,nom);
	strcpy(ens->T[i].valeur, valeur);
	ens->nb++;
	return i;
}

int trouver_et_appliquer_affectation_variable(variables * ens,const char * ligne)
{
	char cpy[TAILLE_MAX_NOM + TAILLE_MAX_VALEUR + 1];
	strcpy(cpy, ligne);
	size_t position_egale = 0;
	for (size_t i = 0; i < strlen(cpy); i++)
	{
		if (cpy[i] == '=' && position_egale != 0)
			return 0;
		if (cpy[i] == '=')
		{
			position_egale = i;
			continue;
		}
	}
	if (position_egale == 0)
		return 0;
	cpy[position_egale] = '\0';
	ajouter_variable(ens, cpy, &cpy[position_egale + 1]);

	return 1;
}

char * nom_variable(variables * ens, size_t indice)
{
	if(indice > ens->nb)
		return NULL;
	return ens->T[indice].nom;
}

char * valeur_variable(variables * ens, size_t indice)
{
	if (indice > ens->nb)
		return NULL;
	return ens->T[indice].valeur;
}

int trouver_variable(variables * ens, const char * nom)
{
	size_t i = 0;
	for (; i < ens->nb; i++)
	{
		if (!strcmp(ens->T[i].nom, nom))
		{
			return i;
		}
	}
	return -1;
}

void apppliquer_expansion_variables(variables * ens, char * ligne_originale, char * ligne_expansee)
{
	char mot[TAILLE_MAX_NOM];
	size_t i = 0;
	int correction_expanse = 0;
	for (; i < strlen(ligne_originale); i++)
	{
		if (ligne_originale[i] == '$')
		{
			i++; // on icremente i car on se moque du '$'
			size_t j = i; //on crée un indice pour parcourir le mot à expanser
			while (ligne_originale[j] != ' ' && j < strlen(ligne_originale))
			{
				mot[j - i] = ligne_originale[j]; // on sauvegarde le mot
				j++;
			}
			mot[j-i] = '\0'; // pour fermer la string.
			int indice = trouver_variable(ens, mot);
			if (indice == -1) // le mot n'existe pas donc on copie tel quel
			{
				ligne_expansee[i + correction_expanse - 1] = ligne_originale[i - 1]; // on copie le '$'
				ligne_expansee[i + correction_expanse] = ligne_originale[i];// on copie le caractere après le '$' car il ne sera pas pris dans la boucle
					continue; // on iter la boucle for
			}
			char* mot_expansee = valeur_variable(ens, indice);
			i--; // on reprend le i de base pour ne pas avoir de probleme d'indice
			for (size_t k = 0; k < strlen(mot_expansee); k++)
			{
				ligne_expansee[i + correction_expanse + k] = mot_expansee[k];
			}			
			i += strlen(mot); // on avance de la taille de mot car on se moque des caracteres du mot
			correction_expanse += strlen(mot_expansee) - strlen(mot) - 1;
		}
		else
		{
			ligne_expansee[i + correction_expanse] = ligne_originale[i];
		}
	}
}
