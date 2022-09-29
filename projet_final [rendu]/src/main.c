#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <search.h>

#include "Affichage/Coordonnees/convert_coordonnees.h"
#include "XML/Parser/struct.h"
#include "main.h"

#ifndef XWindows
 #define XWindows 800.0
#endif
#ifndef YWindows
 #define YWindows 600.0
#endif

int main (int argc, char **argv) {
	if (argc<2) {
		puts("usage : prgm fichier.osm");
		return 3;
	}
	affichage(lecture_du_XML(argv[1]));
	return 0;
}
