#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <search.h>

#include "../Affichage/Coordonnees/convert_coordonnees.h"
#include "../XML/Parser/struct.h"
#include "../main.h"

#ifndef XWindows
 #define XWindows 800.0
#endif
#ifndef YWindows
 #define YWindows 600.0
#endif

tab_dessin_t *utilise_refs_fin (int *tx, int *ty, int taille_tx_ty, Way way) {
	tab_dessin_t *tab_dessin = malloc(sizeof(tab_dessin_t));
	if (!tab_dessin) {
		puts("Problèmes de mémoire :\nFonction : utilise_refs\nVariable : tab_dessin\n");
		free(tx);
		free(ty);
		return NULL;
	}
	color_rgb_t *color_rgb = utilise_tag(way);
	if (!color_rgb) {
		puts("Problèmes de mémoire :\nFonction : utilise_way\nVariable : color_rgb\n");
		free(tx);
		free(ty);
		free(tab_dessin);
		return NULL;
	}
	remplit_tab_dessin_t(tab_dessin, tx, ty, taille_tx_ty, color_rgb);
	return tab_dessin;
}

void utilise_refs (Way way, ListNode *list_node, coordonnees_affichage_t *coordonnees_affichage, int nbr_node) {
	int i=0, cmp = 0, taille_tx_ty = 0;
	int *tx = malloc(nbr_node*sizeof(int));
	int *ty = malloc(nbr_node*sizeof(int));
	coordonnes_t *res;
	Node *node = NULL;
	List* refs = (&way)->refs;
	if (!tx || !ty) {
		puts("Problèmes de mémoire :\nFonction : utilise_refs\nVariables tx et/ou ty\n");
		return;
	}
	while (refs) {
		refs = refs->next; cmp++;
	}
	refs = (&way)->refs;
	while (i<cmp-1) {
		refs = refs->next;
		node = cherche_node_ref(refs->data);
		if (node) {
			res = calc_coordonnees(coordonnees_affichage->xmin, 
			coordonnees_affichage->xmax, coordonnees_affichage->ymin, 
			coordonnees_affichage->ymax, node->lon, node->lat, XWindows, YWindows);
			if (!res) {
				puts("Problèmes de mémoire :\nFonction : utilise_refs\nVariables res (calc_cordonnées)\n");
				return;
			}
			tx[i] = (int)(res->x); ty[i] = (int)(res->y);
			free(res);
			taille_tx_ty++;
		}
		i++;
	}
	tab_affichage[compteur_tab_affichage] = utilise_refs_fin (tx, ty, taille_tx_ty, way);
	compteur_tab_affichage++;
}

int affiche_ways_debut (XML* xml, coordonnees_affichage_t *coordonnees_affichage) {
	int i=0, cmp=0;
	ListWay *list_way = xml->lw;
	while (list_way) {
		list_way = list_way->suivant;
		cmp++;
	}
	Way way;
	list_way = xml->lw;
	tab_affichage = malloc(cmp*sizeof(tab_dessin_t*));
	if (!tab_affichage) {
		puts("Problèmes de mémoire :\nFonction : \nVariable : tab_affichage\n");
		return 0;
	}
	compteur_tab_affichage = 0;
	printf("Nombre de ways : %d\n", cmp);
	while (i<cmp) {
		way = list_way->element;
		utilise_refs(way, xml->ln, coordonnees_affichage, xml->ListNode_len);
		//printf("i = %d\n", i);
		list_way = list_way->suivant;
		i++;
	}
	return cmp;
}

void affiche_ways_fin (SDL_Renderer* renderer, int taille_tab_dessin) {
	if (!tab_affichage) {
		puts("Problèmes de mémoire :\nFonction : affiche_ways_fin\nVariable : tab_affichage\n");
		return;
	}
	int i=0;
	tab_dessin_t *tab_dessin_tmp;
	while (i<taille_tab_dessin-1) {
		tab_dessin_tmp = tab_affichage[i];
		if (strcmp(tab_dessin_tmp->color_rgb->forme, "filledpolygone")==0)
			affiche_filled_polygone(renderer, tab_dessin_tmp->tx, tab_dessin_tmp->ty, tab_dessin_tmp->taille_tx_ty, tab_dessin_tmp->color_rgb);
		else if (strcmp(tab_dessin_tmp->color_rgb->forme, "polygone")==0)
			affiche_polygone(renderer, tab_dessin_tmp->tx, tab_dessin_tmp->ty, tab_dessin_tmp->taille_tx_ty, tab_dessin_tmp->color_rgb);
		else
			affiche_ligne(renderer, tab_dessin_tmp->tx, tab_dessin_tmp->ty, tab_dessin_tmp->taille_tx_ty, tab_dessin_tmp->color_rgb);
		i++;
	}
	free(tab_affichage);
}

int lecture_du_XML (char *fichier_osm) {
	XML* xml = Parser(fichier_osm);
	if (!xml) {
		puts("Problèmes de mémoire : \nFonction : affichage\nvariable : xml");
		return -1;
	}
	//remlissage du hashtab avec les nodes
	remlissage_hash_tab(xml->ln);
	// acquisition des coordoonées
	coordonnees_affichage_t *coordonnees_affichage = remplissage_des_coordoonnes_extremes(xml);
	if (!coordonnees_affichage) {
		puts("Problèmes de mémoire :\nFonction : lecture_du_XML\nVariable : coordonnees_affichage\n");
		return -1;
	}
	int taille_tab_dessin = affiche_ways_debut(xml, coordonnees_affichage);
	free(coordonnees_affichage);
	return taille_tab_dessin;
}
