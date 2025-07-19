#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <search.h>

#include "Coordonnees/convert_coordonnees.h"
#include "../XML/Parser/struct.h"
#include "../main.h"

#ifndef XWindows
 #define XWindows 800.0
#endif
#ifndef YWindows
 #define YWindows 600.0
#endif

void affiche_ligne (SDL_Renderer* renderer, int *tx, int *ty, int taille_tx_ty, color_rgb_t* color_rgb) {
	int i = 0;
	SDL_Point *points = malloc(taille_tx_ty*sizeof(SDL_Point));
	if (!points) {
		puts("Problèmes de mémoire :\nFonction : affiche_route\nVariable : point\n");
		return;
	}
	while (i<taille_tx_ty) {
		points[i].x = tx[i];
		points[i].y = YWindows-ty[i];
		i++;
	}
	SDL_SetRenderDrawColor(renderer, color_rgb->red, color_rgb->green, color_rgb->blue, 255);
	SDL_RenderDrawLines(renderer, points, taille_tx_ty);
	free(points);
}

void affiche_filled_polygone (SDL_Renderer* renderer, int *tx, int *ty, int taille_tx_ty, color_rgb_t* color_rgb) {
	int i = 0;
	short *stx = malloc(taille_tx_ty*sizeof(short));
	short *sty = malloc(taille_tx_ty*sizeof(short));
	if (!stx || !sty) {
		puts("Problèmes de mémoire :\nFonction : affiche_polygone\nVariables strx et/ou sty\n");
		return;
	}
	while (i<taille_tx_ty) {
		stx[i] = tx[i];
		sty[i] = YWindows-ty[i];
		i++;
	}
	filledPolygonRGBA(renderer, stx, sty, taille_tx_ty, color_rgb->red, color_rgb->green, color_rgb->blue, 255);
	free(stx);
	free(sty);
}

void affiche_polygone (SDL_Renderer* renderer, int *tx, int *ty, int taille_tx_ty, color_rgb_t* color_rgb) {
	int i = 0;
	short *stx = malloc(taille_tx_ty*sizeof(short));
	short *sty = malloc(taille_tx_ty*sizeof(short));
	if (!stx || !sty) {
		puts("Problèmes de mémoire :\nFonction : affiche_polygone\nVariables strx et/ou sty\n");
		return;
	}
	while (i<taille_tx_ty) {
		stx[i] = tx[i];
		sty[i] = YWindows-ty[i];
		i++;
	}
	polygonRGBA(renderer, stx, sty, taille_tx_ty, color_rgb->red, color_rgb->green, color_rgb->blue, 255);
	free(stx);
	free(sty);
}

color_rgb_t *utilise_tag (Way way) {
	color_rgb_t *color_rgb = malloc(sizeof(color_rgb_t));
	if (!color_rgb) {
		puts("Problèmes de mémoire :\nFonction : utilise_tag\nVariable : color_rgb\n");
		return NULL;
	}

	char **tag = way.tag;
	remplit_color_rgb_t(color_rgb, 0, 0, 0, "ligne");
	if (tag[0] && tag[1]) {
		if(strcmp(tag[0], "building") == 0 && strcmp(tag[1], "yes") == 0)
			remplit_color_rgb_t(color_rgb, 68, 41, 0, "filledpolygone");
		if(strcmp(tag[0], "highway") == 0)
			remplit_color_rgb_t(color_rgb, 95, 95, 95, "ligne");
		if(strcmp(tag[0], "waterway") == 0 && strcmp(tag[1], "river") == 0)
			remplit_color_rgb_t(color_rgb, 0, 0, 155, "filledpolygone");
		if(strcmp(tag[0], "waterway") == 0 && strcmp(tag[1], "canal") == 0)
			remplit_color_rgb_t(color_rgb, 102, 178, 255, "filledpolygone");
		if(strcmp(tag[0], "natural") == 0 && strcmp(tag[1], "water") == 0)
			remplit_color_rgb_t(color_rgb, 0, 102, 255, "filledpolygone");
		if(strcmp(tag[0], "natural") == 0 && strcmp(tag[1], "coastline") == 0)
			remplit_color_rgb_t(color_rgb, 58, 144, 230, "ligne");
		if(strcmp(tag[0], "landuse") == 0)
			remplit_color_rgb_t(color_rgb, 240, 166, 92, "filledpolygone");
	}
	else {
		if (!tag[0]) {
			//puts("tag[0] est null");
		}
		if (!tag[1]) {
			//puts("tag[1] est null");
		}
	}
	return color_rgb;
}

/**
	Rappel : 
		lon = x
		lat = y
**/
int affichage (int taille_tab_dessin) {
	if (taille_tab_dessin==-1) {
		puts("Erreur : fermeture de l'application");
		return 0;
	}
	SDL_Window* window;
	SDL_Renderer* renderer;
	// déclaration d'une surface.
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
		return 1;

	window = SDL_CreateWindow("Tracer un Point", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, XWindows, YWindows, 0);
	// création de la fenêtre
	renderer = SDL_CreateRenderer(window, -1, 0);
	// création de l'outil de dessin
	//SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	// choix d'une couleur
	SDL_RenderClear(renderer);
	// nétoyage de la fenêtre

	// affichages des polygones
	affiche_ways_fin(renderer, taille_tab_dessin);

	// mécanisme de fonctinnement de la fenêtre
	SDL_RenderPresent(renderer);
	SDL_Event e;
	while (1) {
		if (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT) {
				break;
			}
		}
	}
	SDL_Quit();
	return 1;
}
