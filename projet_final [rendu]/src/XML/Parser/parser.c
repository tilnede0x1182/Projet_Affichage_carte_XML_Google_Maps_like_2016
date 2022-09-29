#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/parserInternals.h>
#include <search.h>

#include "struct.h"

int way = 0;
ListNode * ln = NULL;
int ListNode_len=0;
ListWay * lw = NULL;
List *refs ;
char *tag[2];
Bounds *bd = NULL;

char *cherche_attribut(const xmlChar **attrs, char *nom_attribut) {
	int cmp = 0;
	while (attrs[cmp]) {
		cmp++;
	}
	int i = 0;
	while (i<cmp-1) {
		if (strcmp((const char*)(attrs[i]), nom_attribut)==0)
			return (char*)(attrs[i+1]);
		i++;
	}
	return NULL;	
}


void init_min_max(const xmlChar **attrs){
      if (attrs != NULL) {
        bd = malloc(sizeof(Bounds));
	if (!bd) {
		puts("Problèmes de mémoire : \nFonction : init_min_max\nvariable : bounds");
		return;
	}

        bd->minlat=atof(cherche_attribut(attrs, "minlat"));
        bd->minlon=atof(cherche_attribut(attrs, "minlon"));
        bd->maxlat=atof(cherche_attribut(attrs, "maxlat"));
        bd->maxlon=atof(cherche_attribut(attrs, "maxlon"));
      }
}

void debut_document(void *user_data) {
    //printf("Début du document\n");
}


void fin_document(void *user_data) {
    //printf("Fin du document\n");
}

void debut_element(void *user_data, const xmlChar *name, const xmlChar **attrs) {
    //printf("Début de l'élément : %s\n", name);

    if(xmlStrEqual(name, BAD_CAST "bounds")){
      init_min_max(attrs);
    }
    else if(xmlStrEqual(name, BAD_CAST "node")){
        if(ln==NULL){
            //printf("create\n");
            Node nd;
            nd.id = malloc((strlen((char*)attrs[1]) + 1) * sizeof(char));
	    if (!nd.id) {
		puts("Problèmes de mémoire : \nFonction : debut_element\nvariable : nd.id");
		return;
	    }
            strcpy(nd.id,(char*)attrs[1]);
            nd.lat = atof(cherche_attribut(attrs, "lat"));
            nd.lon = atof(cherche_attribut(attrs, "lon"));
            ln = list_node_create(nd);
            ListNode_len++;
        }
        else{
           //printf("ajoute\n");
           Node nd;
           nd.id = malloc((strlen((char*)attrs[1]) + 1) * sizeof(char));
	   if (!nd.id) {
		puts("Problèmes de mémoire : \nFonction : debut_element\nvariable : nd.id");
		return;
	   }
           strcpy(nd.id,(char *)attrs[1]);
           nd.lat = atof(cherche_attribut(attrs, "lat"));
           nd.lon = atof(cherche_attribut(attrs, "lon"));
           node_append(ln,nd);
           ListNode_len++;
        }
	}
    	else if(xmlStrEqual(name,BAD_CAST "way")){
        way++;

	}
	else if(xmlStrEqual(name,BAD_CAST "nd") && way){
        if(refs==NULL){
            //printf("creeWay\n");
            char* str = malloc((strlen((char*)attrs[1]) + 1) * sizeof(char));
	   if (!str) {
		puts("Problèmes de mémoire : \nFonction : debut_element\nvariable : str");
		return;
	   }
            strcpy(str,(char *)attrs[1]);
            refs=list_create(str);
        }
        else{
           //printf("ajouteWay\n");
           char* str = malloc((strlen((char*)attrs[1]) + 1) * sizeof(char));
	   if (!str) {
		puts("Problèmes de mémoire : \nFonction : debut_element\nvariable : str");
		return;
	   }
           strcpy(str,(char *)attrs[1]);
           list_append(refs,str);
        }
	}

	else if(xmlStrEqual(name,BAD_CAST "tag") && way){
        //printf("tag\n");
        if (!tag[0]){
            //printf("debut_element:attrs: %s, %s \n",attrs[1],attrs[3]);
            tag[0] = malloc((strlen((char*)(cherche_attribut(attrs, "k"))) + 1) * sizeof(char));
            tag[1] = malloc((strlen((char*)(cherche_attribut(attrs, "v"))) + 1) * sizeof(char));
	    if (!tag[0] || !tag[1]) {
		puts("Problèmes de mémoire : \nFonction : debut_element\nvariables tag[0] ou tag[1]");
		return;
	    }
            strcpy(tag[0], cherche_attribut(attrs, "k"));
            strcpy(tag[1], cherche_attribut(attrs, "v"));
        }
        //printf("tag2\n");
	}
}


void fin_element(void *user_data, const xmlChar *name) {
    //printf("Fin de l'élément : %s\n", name);
    if(xmlStrEqual(name,BAD_CAST "way")){
        //printf("finduway\n");
        Way tmp_way;
        tmp_way.refs = list_create(refs->data);
        while (refs!=NULL){
            refs = refs->next;
            if(refs){
                list_append(tmp_way.refs,refs->data);
            }
        }
       // printf("fin_element:attrs: %s, %s\n",tag[0],tag[1]);

        tmp_way.tag[0] = tag[0];
        tmp_way.tag[1] = tag[1];

        if(lw==NULL){
            //printf("create2\n");
            lw=list_way_create(tmp_way);
        }
        else{
            //printf("append2\n");
            way_append(lw,tmp_way);
        }
        refs = NULL;
        tag[0] = NULL;
        tag[1] = NULL;
        way--;
    }
    //printf("fin2\n");
}

void caracteres(void *user_data, const xmlChar *ch, int len) {
    //printf("Elément texte : (longueur = %d) %.*s\n", len, len, ch);
}

XML* Parser(char* file){
    // Initialisation de tous les membres à zéro (soit NULL pour un pointeur par conversion)
    xmlSAXHandler sax = { 0 };
    // Utilisation par affectation de la fonction au membre startDocument
    sax.startDocument = debut_document;
    // Utilisation par affectation de la fonction au membre endDocument
    sax.endDocument = fin_document;
    // Affectation de la fonction au membre startElement
    sax.startElement = debut_element;
    // Affectation de la fonction au membre endElement
    sax.endElement = fin_element;
    // Affectation de la fonction au membre characters
    sax.characters = caracteres;

    xmlParserCtxtPtr ctxt;
    // Création du contexte
    if ((ctxt = xmlCreateFileParserCtxt(file)) == NULL) {
        fprintf(stderr, "Erreur lors de la création du contexte\n");
	return NULL;
    }
    // Fonctions de rappel à utiliser
    ctxt->sax = &sax;
    // Analyse
    xmlParseDocument(ctxt);
    // Le document est-il bien formé ?
    if (ctxt->wellFormed) {
        //printf("Document XML bien formé\n");
    }
    else {
        fprintf(stderr, "Document XML mal formé\n");
        xmlFreeParserCtxt(ctxt);
    }

    // Libération de la mémoire
    // rien pour le moment.

    XML* xml = malloc(sizeof(XML));
    if (!xml) {
	puts("Problèmes de mémoire : \nFonction : Parser\nvariable : xml");
	return NULL;
    }
    xml->ln = ln;
    xml->lw = lw;
    xml->bd = bd;
    xml->ListNode_len = ListNode_len;

    printf("Nombre de Nodes : %d\n", ListNode_len);
    //printf("Nombre de ways oubliés : %d\n", way);
    puts("fin parssage");

    return xml;
}

/*int main() {
    XML* xml = Parser("02_paris_place_des_vosges.osm");
    //code a mettre ds le sdl pour creer le hashmap
    hcreate((xml->ListNode_len + ((xml->ListNode_len*25)/100)));
    ListNode **plist = &(xml->ln);
    //int i;
    //for(i=0;i<(xml->ListNode_len);i++){
    while (*plist){
        char *key1 = ((*plist)->element).id;
      //strcpy(key1, "abc");
      coord *c1 = malloc(sizeof(coord));
      if (!c1) {
		puts("Problèmes de mémoire : \nFonction : main\nvariable : c1");
		return 1;
      }
      XML* xml = malloc(sizeof(XML));
      if (!xml) {
		puts("Problèmes de mémoire : \nFonction : main\nvariable : xml");
		return 1;
      }
      c1 -> lat = ((*plist)->element).lat;
      c1 -> lon = ((*plist)->element).lon;

      ENTRY e = {key1, c1};

      hsearch(e, ENTER);
      plist = &((*plist)->suivant);
    }
    //}
    //fin de la creation du hashmap

    //comment afficher un element du hashmap
    ENTRY e_find = {};
    ENTRY *e_res;
    e_find.key = "1381772707";
    e_res = hsearch(e_find, FIND);
    coord *c_res = (coord *) (e_res -> data);
    //printf(" %lf, %lf\n", c_res -> lat, c_res -> lon);

    //recuperer string des element de la list de ref
    ListWay **pliste = &(xml->lw);
    char * str = (((*pliste)->element).refs)->data;
    //printf("refs1 %s\n",str);
    // Libération de la mémoire
    //xmlFreeParserCtxt(ctxt);

    return EXIT_SUCCESS;
}*/

