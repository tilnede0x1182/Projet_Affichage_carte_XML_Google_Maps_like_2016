#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "liste.h"

/**
	Renvoie la longueur de la liste.
**/
int len (liste_t *liste) {
	if (!liste) return 0;
	int cmp = 0;
	liste_t *tmp = liste;
	while (tmp) {
		tmp = tmp->next;
		if (&tmp->elt) cmp++;
	}
	return cmp;
}

int est_vide (liste_t *liste) {
	if (!liste) return 1;
	if (len(liste)<=0) return 1;
	return 0;
}

liste_t *init_liste_t (liste_t *liste, double elt) {
	liste = malloc(sizeof(liste_t));
	if (!liste) {
		puts("Problème des mémoire : impossible d'allouer une liste de type liste_t.");
		return NULL;
	}
	liste->elt = elt;
	return liste;
}

liste_t *create_liste_t (liste_t *liste) {
	liste = malloc(sizeof(liste_t));
	if (!liste) {
		puts("Problème des mémoire : impossible d'allouer une liste de type liste_t.");
		return NULL;
	}
	return liste;
}

int ajoute_element (liste_t *liste, double elt) {
	puts("ajoute_element");
	if (!liste) {
		puts("fonction ajoute_element : la liste n'est pas définie.");
		return 0;
	}
	liste_t *tmp = liste;
	int i = 0;
	//printf("taille de la liste : ", len(liste));
	while (tmp->next) {
		puts("ok");
		tmp = tmp->next;
		printf("parcours de la liste : %d\n", i);
		i++;
	}
	tmp->next = create_liste_t(tmp->next);
	if (!tmp->next)
		return 0;
	tmp = tmp->next;
	tmp->elt = elt;
	return 1;
}

/**
	Ajoute un élémet à la fin de la liste.
	(prend la taille en argument pour être sûr de ne pas déborder)
**/
int ajoute_element_taille_liste (liste_t *liste, double elt, int taille_liste) {
	puts("ajoute_element");
	if (!liste) {
		puts("fonction ajoute_element : la liste n'est pas définie.");
		return 0;
	}
	liste_t *tmp = liste;
	int cmp = 0;
	//printf("taille de la liste : ", len(liste));
	while (cmp<taille_liste && tmp->next) {
		//puts("ok");
		tmp = tmp->next;
		//printf("parcours de la liste : %d\n", i);
		cmp++;
	}
	tmp->next = create_liste_t(tmp->next);
	if (!tmp->next)
		return 0;
	tmp = tmp->next;
	tmp->elt = elt;
	return 1;
}

/**
	Affiche tous les éléments de la liste.
**/
void affiche_liste (liste_t *liste) {
	if (!liste) {
		puts("fonction affiche_liste : la liste n'est pas définie.");
		return;
	}
	int cmp = 0;
	liste_t *tmp = liste;
	while (tmp) {
		if (&tmp->elt&&cmp>0) {
			printf("liste[%d] = %lf\n", cmp, tmp->elt);
		}
		tmp = tmp->next;
		cmp++;
	}
}

/**
	Affiche tous les éléments de la liste.
**/
void affiche_liste_avec_nom (liste_t *liste, char *nom_liste) {
	if (!liste) {
		puts("fonction affiche_liste : la liste n'est pas définie.");
		return;
	}
	int cmp = 0;
	liste_t *tmp = liste;
	while (tmp) {
		if (&tmp->elt&&cmp>0) {
			printf("%s[%d] = %lf\n", nom_liste, cmp, tmp->elt);
		}
		tmp = tmp->next;
		cmp++;
	}
}

void tests () {
	liste_t *liste = NULL;
	liste = create_liste_t (liste);
	printf("ajoute_element : %d\n", ajoute_element(liste, 2));
	printf("ajoute_element : %d\n", ajoute_element(liste, 2));
	printf("len_liste = %d\n", len(liste));
	affiche_liste(liste);
}

void tests_parcours_prefixe () {
	// Initialisation des listes lat et lon.
	liste_t *lat = NULL;
	liste_t *lon = NULL;
	lat = create_liste_t (lat);
	lon = create_liste_t (lon);

	if (!lat || !lon) EXIT_FAILURE; //le message d'erreur est dans la fonction create_liste_t
	int i;
	for (i=0; i<100; i++) {
		printf("ajoute_element : %d\n", ajoute_element(lat, 2));
	}

	printf("len_liste = %d\n", len(lat));
	affiche_liste(lat);
}

int main1 () {
	//tests();
	tests_parcours_prefixe();
	return 0;
}
