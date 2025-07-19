#ifndef CONVERT_COORDONNEES_H
# define CONVERT_COORDONNEES_H

typedef struct coordonnes_s {
	double x;
	double y;
} coordonnes_t;

double change_bornes (double borne_min, double borne_max, double valeur, 
double nouvelle_borne_min, double nouvelle_borne_max);

double applatit_coordonnee (double valeur);

double calc_coordonnee_positive (double xmin, double xmax, double x, double xmax_fenetre);

coordonnes_t *calc_coordonnees (double xmin, double xmax, double ymin, 
double ymax, double x, double y, double xmax_fenetre, double ymax_fenetre);



#endif /* !CONVERT_COORDONNEES_H */

