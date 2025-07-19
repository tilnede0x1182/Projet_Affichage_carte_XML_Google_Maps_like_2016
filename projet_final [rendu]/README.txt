convert coordoonées : 
	Le convert fichier coordoonées fini se situe dans SDL/Affichage_points/V1/.
	Le but est de convertir directement les coordonnées du fichier XML en coordonnées 
	qu'on peut passer à la foncion d'affichage en pixels.
	Pour cela, on utilise la fonction suivante :

	coordonnes_t *res = calc_coordonnees (xmin, xmax, ymin, ymax, x, y, xmax_fenetre, ymax_fenetre);


