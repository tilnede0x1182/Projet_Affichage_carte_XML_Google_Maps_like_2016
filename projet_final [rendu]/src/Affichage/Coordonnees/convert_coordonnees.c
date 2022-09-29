// Includes de base
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Includes des .h
#include "../../XML/Parser/liste.h"
#include "convert_coordonnees.h"

// Variables préprocesseur
#ifndef M_PI
 #define M_PI 3.14159265358979323846
#endif
#ifndef RAYON_TERRE
 #define RAYON_TERRE 6371.0 // km (approximatif)
#endif

double change_bornes (double borne_min, double borne_max, double valeur, 
double nouvelle_borne_min, double nouvelle_borne_max) {
	double val_res = ((valeur-borne_min)/(borne_max-borne_min))*nouvelle_borne_max;
	if (val_res>nouvelle_borne_max)
		val_res = nouvelle_borne_max;
	if (val_res<nouvelle_borne_min)
		val_res = nouvelle_borne_min;
	return val_res;
}

double applatit_coordonnee (double valeur) {
	double r = RAYON_TERRE;
	double x = valeur;
	double pi = M_PI;
	double min_val = (90*pi*r)/180;
	double res = (x*pi*r)/180;
	res = change_bornes (0, min_val, res, 0, r);
	return res;
}

double calc_coordonnee_positive (double xmin, double xmax, double x, double xmax_fenetre) {
	double tmp = applatit_coordonnee(x);
	double xmax_convert = applatit_coordonnee(xmax);
	double xmin_convert = applatit_coordonnee(xmin);
	return change_bornes (xmin_convert, xmax_convert, tmp, 0.0, xmax_fenetre);
}

coordonnes_t *calc_coordonnees (double xmin, double xmax, double ymin, 
double ymax, double x, double y, double xmax_fenetre, double ymax_fenetre) {
	coordonnes_t *res = malloc(sizeof(coordonnes_t));
	if (!res) {
		puts("Problème de mémoire : \nFonction : calc_coordonnees\nVariable : res\n");
		return NULL;
	}

	if (xmin>=0 && xmax>=0)
		res->x = calc_coordonnee_positive (xmin, xmax, x, xmax_fenetre);
	if (ymin>=0 && ymax>=0)
		res->y = calc_coordonnee_positive (ymin, ymax, y, ymax_fenetre);

	if (xmin<=0 || xmax<=0) {
		double xmax_res = xmax-xmin;
		double x_res = x-xmin;
		res->x = calc_coordonnee_positive (0, xmax_res, x_res, xmax_fenetre);
	}
	if (ymin<=0 || ymax<=0) {
		double ymax_res = ymax-ymin;
		double y_res = y-ymin;
		res->y = calc_coordonnee_positive (0, ymax_res, y_res, ymax_fenetre);
	}
	return res;
}

void affiche_donness_pour_le_test (double xmax, double xmin, double ymax, double ymin, double y, double x, double xmax_fenetre, double ymax_fenetre) {
	printf("\nxmin  = %lf\n", xmin);
	printf("ymin  = %lf\n", ymin);
	printf("xmax  = %lf\n", xmax);
	printf("ymax  = %lf\n", ymax);
	printf("x  = %lf\n", x);
	printf("y  = %lf\n", y);
	printf("xmax_fenetre  = %lf\n", xmax_fenetre);
	printf("ymax_fenetre  = %lf\n\n", ymax_fenetre);
}

void convertit_liste (liste_t *lat, liste_t *lon, int taille_liste, double xmin, double xmax, double ymin, double ymax, double xmax_fenetre, double ymax_fenetre) {
	liste_t *tmp_lat = lat;
	liste_t *tmp_lon = lon;
	int cmp = 0;
	while (cmp<taille_liste && tmp_lat && tmp_lon) {
		if (tmp_lat->elt && tmp_lon->elt) {
			coordonnes_t *res = calc_coordonnees (xmin, xmax, ymin, ymax, tmp_lon->elt, tmp_lat->elt, xmax_fenetre, ymax_fenetre);
			tmp_lon->elt = res->x;
			tmp_lat->elt = res->y;
		}
		tmp_lat = tmp_lat->next;
		tmp_lon = tmp_lon->next;
		cmp++;
	}
}

void test_avec_des_donnes () {
	double xmax, xmin, ymax, ymin, y, x, xmax_fenetre, ymax_fenetre;
	coordonnes_t *res;

	/**
		Rappel :
			lat = y
			lon = x
	**/

	xmax_fenetre = 800;
	ymax_fenetre = 600;

	// tests coordonnees positives
	xmax = 15;
	xmin = 12;
	x = 13;
	ymax = 15;
	ymin = 12;
	y = 15;

	affiche_donness_pour_le_test (xmin, xmax, ymin, ymax, x, y, xmax_fenetre, ymax_fenetre);
	res = calc_coordonnees (xmin, xmax, ymin, ymax, x, y, xmax_fenetre, ymax_fenetre);
	printf("x = %lf\n", res->x);
	printf("y = %lf\n", res->y);

	// tests coordonnees négatives
	xmax = -12;
	xmin = -15;
	x = -12;
	ymax = -12;
	ymin = -15;
	y = -15;

	free(res);
	affiche_donness_pour_le_test (xmin, xmax, ymin, ymax, x, y, xmax_fenetre, ymax_fenetre);
	res = calc_coordonnees (xmin, xmax, ymin, ymax, x, y, xmax_fenetre, ymax_fenetre);
	printf("x = %lf\n", res->x);
	printf("y = %lf\n", res->y);


	// tests coordonnees positives et négatives
	xmax = 5;
	xmin = -5;
	x = 5;
	ymax = 5;
	ymin = -5;
	y = 5;

	free(res);
	affiche_donness_pour_le_test (xmin, xmax, ymin, ymax, x, y, xmax_fenetre, ymax_fenetre);
	res = calc_coordonnees (xmin, xmax, ymin, ymax, x, y, xmax_fenetre, ymax_fenetre);
	printf("x = %lf\n", res->x);
	printf("y = %lf\n", res->y);

	// tests avec vrai coordonnées :
	xmax = -2.6436;
	xmin = -3.4676;
	x = -104.9739674;
	ymax = 59.5183;
	ymin = 58.9245;
	y = 39.7519707;
	
	free(res);
	affiche_donness_pour_le_test (xmin, xmax, ymin, ymax, x, y, xmax_fenetre, ymax_fenetre);
	res = calc_coordonnees (xmin, xmax, ymin, ymax, x, y, xmax_fenetre, ymax_fenetre);
	printf("x = %lf\n", res->x);
	printf("y = %lf\n", res->y);
}

/*int main () {
	test_avec_des_donnes();

	return 0;
}*/
