# Visualisateur OSM

## Description
- Ce projet permet de lire et d’afficher des données géospatiales au format OSM.
- Il parse les fichiers XML OpenStreetMap pour extraire les nœuds et les voies.
- Il convertit les coordonnées géographiques (latitude, longitude) en coordonnées écran.
- Il gère l’affichage graphique des routes, des bâtiments et des plans d’eau avec SDL2.
- Il utilise un système de hachage pour accéder rapidement aux nœuds par identifiant.
- Il prend en charge les fichiers volumineux grâce à une lecture en mémoire optimisée.
- Il propose un mode test pour valider les calculs de conversion de coordonnées.
- Il utilise des listes chaînées pour stocker les éléments OSM en mémoire.
- Il fournit un journal d’exécution et un rapport d’analyse.
- Il est accompagné d’un Makefile pour automatiser la compilation et le rendu.

## Technologies utilisées
- **Langage :** C (C99)
- **Compilateur :** GNU Make 4.x, gcc 10.x
- **Librairies :**
  - SDL2 2.0.x
  - SDL2_gfx 1.0.x
  - libxml2 2.9.x

## Fonctionnalités
- Parsing des balises `<bounds>`, `<node>`, `<way>` et `<tag>` du fichier OSM
- Construction de listes chaînées pour les nœuds (ListNode) et les voies (ListWay)
- Stockage et recherche rapide des nœuds via une table de hachage (`hcreate`/`hsearch`)
- Conversion mathématique des coordonnées géographiques en coordonnées écran avec gestion des bornes
- Affichage graphique des routes (lignes), polygones pleins et contours via SDL2 et SDL2_gfx
- Gestion robuste de la mémoire et des cas d’erreurs (allocations, entrées invalides)
- Mode test intégré pour vérifier la précision des calculs de conversion dans `convert_coordonnees.c`
- Support des fichiers OSM volumineux (plusieurs dizaines de milliers de nœuds)
- Génération d’un journal (`journal.txt`) et d’un rapport d’exécution (`Rapport.txt`)
- Automatisation de la compilation et des tests via un Makefile global et des Makefile locaux dans chaque module
