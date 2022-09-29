#ifndef MAIN_H
#define MAIN_H

typedef struct coordonnees_affichage_s {
	double xmin;
	double xmax;
	double ymin;
	double ymax;
	double x1;
	double y1;
} coordonnees_affichage_t;

typedef struct color_rgb_s {
	int red;
	int green;
	int blue;
	char *forme;
} color_rgb_t;

typedef struct tab_dessin_s {
	int *tx;
	int *ty;
	int taille_tx_ty;
	color_rgb_t *color_rgb;
} tab_dessin_t;

tab_dessin_t **tab_affichage;
int compteur_tab_affichage;

// Affichage
void affiche_filled_polygone (SDL_Renderer* renderer, int *tx, int *ty, int taille_tx_ty, color_rgb_t* color_rgb);
void affiche_polygone (SDL_Renderer* renderer, int *tx, int *ty, int taille_tx_ty, color_rgb_t* color_rgb);
void affiche_ligne (SDL_Renderer* renderer, int *tx, int *ty, int taille_tx_ty, color_rgb_t* color_rgb);
void remplit_color_rgb_t (color_rgb_t *color_rgb, int red, int green, int blue, char *forme);
int affichage (int taille_tab_dessin);
color_rgb_t *utilise_tag (Way way);

// XML
void remplit_tab_dessin_t (tab_dessin_t *tab_dessin, int *tx, int *ty, int taille_tx_ty, color_rgb_t *color_rgb);
int affiche_ways_debut (XML* xml, coordonnees_affichage_t *coordonnees_affichage);
coordonnees_affichage_t *remplissage_des_coordoonnes_extremes (XML* xml);
void affiche_ways_fin (SDL_Renderer* renderer, int taille_tab_dessin);
void remlissage_hash_tab (ListNode *list_node);
int lecture_du_XML (char *fichier_osm);
Node *cherche_node_ref (char * ref);

#endif /* !MAIN_H */
