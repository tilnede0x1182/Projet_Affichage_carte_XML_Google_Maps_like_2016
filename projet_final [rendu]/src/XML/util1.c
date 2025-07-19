#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <search.h>

#include "../Affichage/Coordonnees/convert_coordonnees.h"
#include "Parser/struct.h"
#include "../main.h"

void remlissage_hash_tab (ListNode *list_node) {
	ListNode *tmp = list_node;
	int cmp = 0;
	while (tmp) {
		tmp = tmp->suivant;
		cmp++;
	}
	hcreate(cmp);
	ENTRY entry = {};
	int i=0;
	tmp = list_node;
	while (i<cmp) {
		entry.key = tmp->element.id;
		entry.data = &(tmp->element);
		hsearch(entry, ENTER);
		tmp = tmp->suivant;
		i++;
	}
}

coordonnees_affichage_t *remplissage_des_coordoonnes_extremes (XML* xml) {
	coordonnees_affichage_t *coordonnees_affichage = malloc(sizeof(coordonnees_affichage_t));
	if (!coordonnees_affichage) {
		puts("Problèmes de mémoire : \nFonction : remplissage_des_coordoonnes_extremes\nvariable : coordonnees_affichage");
		return NULL;
	}
	coordonnees_affichage->xmin = (xml->bd)->minlon;
	coordonnees_affichage->xmax = (xml->bd)->maxlon;
	coordonnees_affichage->ymin = (xml->bd)->minlat;
	coordonnees_affichage->ymax = (xml->bd)->maxlat;
	return coordonnees_affichage;
}

Node *cherche_node_ref (char * ref) {
	ENTRY entry_find = {};
	ENTRY *entry_res;
	entry_find.key = ref;
	entry_res = hsearch(entry_find, FIND);
	if (!entry_res) {
		puts("Problème de mémoire : \nFonction : cherche_node_ref\nVariable : entry_res\n");
		return NULL;
	}
	return entry_res->data;
}
