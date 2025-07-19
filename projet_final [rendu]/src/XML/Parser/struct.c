#include "struct.h"

List *list_create (char* data){
   List *list = malloc(sizeof(List)); /* allocation et affectation à la variable list */
   if (list) {                         /* si l'allocation a réussi */
       list->data = data;              /* affectation du champ data  */
       list->next = NULL;              /* affectation du champ next à la liste vide */
   }
   else {
	puts("Problèmes de mémoire : \nFonction : list_create\nvariable : list");
   }
   return list;                        /* retour de la liste (correctement allouée et affectée ou NULL) */
 }

List *list_append(List *list, char* data){
    List **plist = &list;
    while (*plist){
       plist = &(*plist)->next;
    }
    *plist = list_create(data);
    if (*plist)
       return list;
    else {
        return NULL;
    }
}

/* struct de liste specifique inutile*/

ListNode *list_node_create (Node nd){
	ListNode *list = malloc(sizeof(ListNode)); /* allocation  et affectation à la variable list */
   	if (list) {                         /* si l'allocation a réussi */
         	list->element = nd;              /* affectation du champ data */
       	        list->suivant = NULL;              /* affectation du champ next à la liste vide */
   	}
   else {
	puts("Problèmes de mémoire : \nFonction : list_node_create\nvariable : list");
   }
   return list;                        /* retour de la liste (correctement allouée et affectée ou NULL) */
}

ListNode* node_append(ListNode *list, Node element){
    ListNode **plist = &list;
    while (*plist!=NULL){
        plist = &((*plist)->suivant);
        }
    *plist = list_node_create(element);
     if (*plist)
        return list;
    else
        return NULL;
}


ListWay *list_way_create (Way w){
    ListWay *list = malloc(sizeof(ListWay)); /* allocation (en vert sur le diagramme) et affectation à la variable list (en bleu) */
    if (list) {                           /* si l'allocation a réussi */
     list->element = w;              /* affectation du champ data */
     list->suivant = NULL;              /* affectation du champ next à la liste vide */
    }
   else {
	puts("Problèmes de mémoire : \nFonction : list_way_create\nvariable : list");
   }
    return list;                        /* retour de la liste (correctement allouée et affectée ou NULL) */
}

ListWay* way_append(ListWay *list, Way element){
    ListWay **plist = &list;
    while (*plist!=NULL)
        plist = &(*plist)->suivant;
    *plist = list_way_create(element);
     if (*plist)
        return list;
    else
        return NULL;
}

