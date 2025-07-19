#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#ifndef STRUCT_H
#define STRUCT_H

typedef struct Node {
	char   *id;
	double lon;
	double lat;
} Node;

typedef struct coord {
	double lat;
	double lon;
} coord;

typedef struct List {
	char* data;
	struct List* next;
} List;

typedef struct Way {
	List* refs;
	char* tag[2];
} Way;

typedef struct Bounds {
	double minlat;
	double minlon;
	double maxlon;
	double maxlat;
} Bounds;

typedef struct ListNode {
	Node element;
	struct ListNode* suivant;
} ListNode;

typedef struct ListWay {
	Way element;
	struct ListWay* suivant;
} ListWay;

typedef struct XML {
	ListNode *ln;
	int ListNode_len;
	ListWay *lw;
	Bounds *bd;
} XML;

XML* Parser(char* file);
List *list_create (char* data);
List *list_append(List *list, char* data);
/* struct de liste specifique inutile*/
ListNode *list_node_create (Node nd);
ListNode* node_append(ListNode *list, Node element);
ListWay *list_way_create (Way w);
ListWay* way_append(ListWay *list, Way element);

#endif /* !STRUCT_H */
