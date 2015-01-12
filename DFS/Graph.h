/*andrew lien 
 * pa5
 * Patrick Tantalo
 * CS101
 * Graph.h
 */

#include "List.h"
#if !defined(_GRAPH_H_INCLUDE)
#define _GRAPH_H_INCLUDE_
#define INF -1
#define NIL 0



typedef struct Graph * GraphA;

/* Constructors-Destructors */ 
GraphA newGraph(int n); 
void freeGraph(GraphA* pG);
 
/* Access functions */ 
int getOrder(GraphA G); 
int getSize(GraphA G); 
int getParent(GraphA G, int u); 
int getDiscover(GraphA G, int u);
int getFinish(GraphA G, int u);

/* Manipulation procedures */ 
void addArc(GraphA G, int u, int v);
void DFS(GraphA G, ListA S);
 
/* Other Functions */ 
GraphA transpose(GraphA G); 
GraphA copyGraph(GraphA G); 
void printGraph(FILE* out , GraphA G); 
#endif
