/*andrew lien 
 * pa4
 * Patrick Tantalo
 * CS101
 * Graph.h
 */
#ifndef __GRAPH_H__
#define __GRAPH_H__
#define INF -1
#define NIL 0
#define WHITE 0
#define GRAY 1
#define BLACK 2

#include "List.h"

/************* Exported Types *************************************************/

typedef struct GraphObj* Graph;


/************** Constructors-Destructors **************************************/

Graph newGraph(int);
void freeGraph(Graph*);


/*************** Access Functions *********************************************/

int getOrder(Graph);
int getSize(Graph);
int getSource(Graph);
int getParent(Graph, int);
int getDist(Graph, int);
void getPath(List, Graph, int );


/************** Manipulation Procedures ***************************************/

void makeNull(Graph);
void addEdge(Graph, int, int);
void addArc(Graph, int, int);
void BFS(Graph, int);


/***************** Other Operations *******************************************/

void printGraph(FILE*, Graph);

#endif
