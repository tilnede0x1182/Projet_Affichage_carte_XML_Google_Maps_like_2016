#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <search.h>

#include "Coordonnees/convert_coordonnees.h"
#include "../XML/Parser/struct.h"
#include "../main.h"

void remplit_tab_dessin_t (tab_dessin_t *tab_dessin, int *tx, int *ty, int taille_tx_ty, color_rgb_t *color_rgb) {
	tab_dessin->tx = tx;
	tab_dessin->ty = ty;
	tab_dessin->taille_tx_ty = taille_tx_ty;
	tab_dessin->color_rgb = color_rgb;
}

void remplit_color_rgb_t (color_rgb_t *color_rgb, int red, int green, int blue, char *forme) {
	color_rgb->red = red;
	color_rgb->green = green;
	color_rgb->blue = blue;
	color_rgb->forme = forme;
}


