/*andrew lien 
 * pa4
 * Patrick Tantalo
 * CS101
 * Graph.c 
 */

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

/*START PRIVATE STRUCTS*/
typedef struct GraphObj{
  List* adj; //array of lists of ints corresponding to vertice
  int* color; //array of color values corresponding to vertice #
  int* d; //array of distance values
  int* p; //array of parent values w/ vertice #
  int order; //## of vertices
  int size; //## of sizes
  int source; //most recent used as source for BFS
}GraphObj;
/*END PRIVATE STRUCTS*/

/* START CONSTRUCTORS/DESTRUCTORS */
Graph newGraph(int n){
  Graph G = malloc(sizeof(GraphObj));
  G->adj = calloc(n+1, sizeof(List));
  G->color = calloc(n+1, sizeof(int));
  G->p = calloc(n+1, sizeof(int));
  G->d = calloc(n+1,sizeof(int));
  G->order = n;
  G->size = 0;
  G->source = NIL; //from graph.h 
 int i;
 for(i = 1; i<=n; ++i){
   G->adj[i] = newList(); //create new list across the adjacency list
   G->color[i] = WHITE; //turn all of the colors across the list as white
   G->d[i] = INF; //assume for infinite spaces
   G->p[i] = NIL; //none has parents yet
 }
 return (G);
}
void freeGraph(Graph* pG){
  if(pG == NULL || (*pG) == NULL){ return; }
  int i;
  for(i = 1; i <=getOrder(*pG); ++i){
    freeList(&((*pG)->adj[i]));
  }
	free((*pG)->adj);
	free((*pG)->color);
	free((*pG)->d);
	free((*pG)->p);
	free(*pG);
	*pG = NULL;

}

/* END CONSTRUCTORS/DESTRUCTORS */

/* BEGIN ACCESS FUNCTIONS */

int getOrder(Graph G){
  if(G == NULL) { //account for the null graph
    printf("GetOrder() --> NULL Graph\n");
    exit(1);
  }
  return G->order;
}
int getSize(Graph G){
  if(G == NULL){
    printf("getSize() -->NULL Graph\n");
    exit(1);
  }
  return G->size;
}
int getSource(Graph G){
  if(G == NULL){
    printf("getSource() -->NULL Graph\n");
    exit(1);
  }
  return G->source;
}
int getParent(Graph G, int u){
	if ( G == NULL ) {
		printf("Graph Error: calling getParent() on NULL GraphRef\n");
		exit(1);
	}
	if ( u < 1 || u > getOrder(G) ) {
		printf("Graph Error: calling getParent() on out of index array P\n");
		exit(1);
	}
	
	return G->p[u];  
}
int getDist(Graph G, int u) {
	if ( G == NULL ) {
		printf("Graph Error: calling getDist() on NULL GraphRef\n");
		exit(1);
	}
	if ( u < 1 || u > getOrder(G) ) {
		printf("Graph Error: calling getDist() on out of index array d\n");
		exit(1);
	}
	
	return G->d[u];
}
void getPath(List L, Graph G, int u){

 if (getSource(G) == NIL) {
      printf("Graph Error: calling getPath() before BFS is called");
      exit(1);
   }
   else {
      if (G->source == u) {
         append(L, u);
      }
      else if (G->p[u] == NIL) {
      }
      else {
         getPath(L, G, G->p[u]);
         append(L, u);
      }
   }


}

/*END ACCESS FUNCTIONS*/ 

// Private Helper Class: Insert Sorted inserts v into list u
// in it's appropriate position
void insertSorted(List U, int v) {
	moveTo(U, 0);
	if (length(U) == 0) {
      append(U,v);
      return;
	}
	for (int i=0; i<length(U);i++) {
      moveTo(U,i);
      int cmp = getElement(U);
		// Insert before if lex. less than
		if (v == cmp) {
			break;
		} if (v < cmp) {
			insertBefore(U, v);
			break;
		// If reached the end of the list, append
		} else if (i == length(U)-1) {
			append(U,v);
				//	printList(stdout,U);
		//printf("\n");
		//	printf("Studying\n");
			break;
		}
		moveNext(U);
	}
}

/* BEGIN MANIPULATION FUNCTIONS */
void makeNull(Graph G){ //hint, think constructor
  if(G==NULL){
    printf("Graph Error: calling makeNull() on NULL GraphRef\n");
	exit(1);
  }
   int i;
   for(i = 1; i<=getOrder(G); ++i){
      makeEmpty(G->adj[i]); //empty the list
      G->color[i] = NIL;
      G->d[i] = NIL;
      G->p[i] = NIL;
   }
   G->size = 0;
   G->source = NIL; 
 }  
 void addEdge(Graph G, int u, int v){
//   printf("Pass 2\n");
	if ( G == NULL ) {
		printf("Graph Error: calling addEdge() on NULL GraphRef\n");
		exit(1);
	}
	if ( u < 1 || u > getOrder(G) ) {
		printf("Graph Error: calling addEdge() on u non-existent within bounds of order\n");
		exit(1);
	}
	if ( v < 1 || v > getOrder(G) ) {
		printf("Graph Error: calling addEdge() on v non-existent within bounds of order\n");
		exit(1);
	}

	// Sorted insert v into neighbors[u]
	List U = G->adj[u];
	insertSorted(U, v);
	++G->size;
	// Sorted insert u into neighbors[V]
	List V = G->adj[v];
	insertSorted(V, u);
	//printGraph(stdout, G);
/*	addArc(G, u, v);
    addArc(G, v, u);
    G->size--;
   // printf(" \n \n ");
             // printf("After performing AddEdge\n");
             // printf("%d: ",u);
			 // printList(stdout, G->adj[u]);
			 // printf("\n");
			  //printf("%d: ",v);
			 // printList(stdout,G->adj[v]);
			  //printf("\n");
			  
			  //printf("State of Graph as it stands: \n");
			  printGraph(stdout, G);
			 // printf("\n");*/
			 // printGraph(stdout, G);
}  
 //note: addEdge inserts a new EDGE joining u to v, adding to adjacency list

void addArc(Graph G, int u, int v){

  if(!(u > 0 && u <= getOrder(G)) || !(v > 0 && v <= getOrder(G))){
    fprintf(stderr, "Vertex out of bounds\n");
    exit(1);
  }
/*
  int curr;
  if(length(G->adj[u]) == 0) append(G->adj[u], v);
  else{
    moveTo(G->adj[u], 0);
    while(getIndex(G->adj[u]) != -1){
      curr = getElement(G->adj[u]);
      if(v <= curr){
        insertBefore(G->adj[u], v);
        break;
      } else if (v > curr){
        append(G->adj[u], v);
        break;
      } else moveNext(G->adj[u]);

    }
  }
  ++G->size;*/
  	List U = G->adj[u];
	insertSorted(U, v);

}
/*BEGIN: BREADTH FIRST SEARCH ALGORITHM*/
void BFS(Graph G, int s){

	if ( G == NULL ) {
		printf("Graph Error: calling BFS() on NULL\n");
		exit(1);
	}
	if ( s < 1 || s > getOrder(G) ) {
		printf("Graph Error: calling BFS() on s non-existent within bounds of order\n");
		exit(1);
	}
	
	G->source = s; //set the source to 2nd parameter
	int i,x;
	//reset the entire board to empty
	for(i = 1; i<=getOrder(G); ++i){
	  G->color[i] = WHITE;
	  G->d[i] = INF;
	  G->p[i] = NIL; 
	}
	//set the initial source color to discovered(grey);;
	//distance so far is 0, and no parent for source
	G->color[s] = GRAY;
	G->d[s] = 0;
	G->p[s] = NIL;
	
	//create a list to start putting items into it
	List L = newList();
	append(L,s);
	while(!isEmpty(L)){
	
	  x = getFront(L); //start @ front of the list
	  deleteFront(L); //now that x is collected, delete it
	  //as long as adj list is still 'active' stay at front
	  if(!isEmpty(G->adj[x])) moveFront(G->adj[x]);
	    moveFront(G->adj[x]);
	  while(!offEnd(G->adj[x])) {
	//  printf("Value of y before: %d\n,",y);
	  int y = getElement(G->adj[x]);
	    //	  printf("Value of y after: %d\n",y);
	    if(G->color[y] == WHITE) {
	      G->color[y] = GRAY;
	      G->d[y] = (getDist(G,x) +1); 
	      G->p[y] = x;
	      append(L,y);
	    }
	    moveNext(G->adj[x]);
	  }
	  G->color[x] = BLACK;
	}
	free(L);

}

/*END: BREADTH FIRST SEARCH ALGORITHM*/

void printGraph(FILE* out, Graph G){
		if (out == NULL) {
		exit(1);
	} else if (G == NULL) {
		exit(1);
	}
	for (int i = 1; i <= getOrder(G); i++) {
		fprintf(out,"%d: ",i);
		printList(out,G->adj[i]);
		fprintf(out,"\n");
	}
}













