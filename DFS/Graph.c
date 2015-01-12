/*andrew lien 
 * pa5
 * Patrick Tantalo
 * CS101
 * Graph.c
 */

#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include "Graph.h"

typedef struct Graph{
   ListA * adjac;
   char * color;
   int * d;
   int * finish;
   int * p;
   int order;
   int time;
   int size;
}Graph;

/*On August 14th, something went terribly wrong, couldn't figure it out, 
  fixed it by transferring from Graph to GraphA*/
  
GraphA newGraph(int n){
    int i;
    GraphA G = malloc(sizeof(Graph));
    G->adjac = calloc(n+1, sizeof(ListA));
    G->color = calloc(n+1, sizeof(char));
    G->d = calloc(n+1, sizeof(int));
    G->finish = calloc(n+1, sizeof(int));
    G->p = calloc(n+1, sizeof(int));    
    for ( i = 1; i<= n ; i++){
        G->adjac[i] = newList();
        G->color[i] = 'w';
        G->d[i] = INF;
        G->finish[i] = INF;
        G->p[i] = NIL;
    }
    G->order = n;
    G->time = INF;
    G->size = 0;
    return G;
}

void freeGraph(GraphA* pG){
    if (pG==NULL || *pG==NULL) return;
    int i, n = getOrder(*pG);
    for (i = 1;i <= n; i++){
       freeList(&(*pG)->adjac[i]);
    }
    free((*pG)->adjac);
    free((*pG)->color);
    free((*pG)->d);
    free((*pG)->finish);
    free((*pG)->p);
    free(*pG);
    *pG = NULL;
}


int getOrder(GraphA G){
    return G->order;
}
int getSize(GraphA G){
    return G->size;
} 

int getParent(GraphA G, int u){
    if (u < 1 || u > getOrder(G)){
        printf("Called getParent on out of bound u\n");
        exit(1);
    }
    else return G->p[u];
}

int getDiscover(GraphA G, int u){
     if (u < 1 || u > getOrder(G)){
         printf("Called getDiscoveristance on out of bound u\n");
         exit(1);
     }
     else return G->d[u];
}

int getFinish(GraphA G, int u){
     if (u < 1 || u > getOrder(G)){
         printf("Called getFinish on out of bound u\n");
         exit(1);
     }
     else return G->finish[u];
}


void addArc(GraphA G, int u, int v){
    ListA row = G->adjac[u];

    /* Inserts vetex v into row u in the adjac array */
    if (isEmpty(row)){
        prepend(row, v);
        G->size++;
        return;
    }
    else{
        moveTo(row, 0);
        while (!offEnd(row)){
            if (v == getElement(row)) return;
            if (v > getElement(row)){
                moveNext(row);
            }else{
                insertBefore(row, v);
                G->size++;
                return;
            }
        }
        append(row, v);
        G->size++;
    }

}

void visit(GraphA G, ListA S, int u){
    int v;
    G->color[u] = 'g';
    G->time++;
    G->d[u] = G->time;
    moveTo(G->adjac[u], 0);
    while (!offEnd(G->adjac[u]) ){
        v = getElement(G->adjac[u]);
        if(G->color[v] == 'w'){
            G->p[v] = u;
            visit(G, S, v);
        }
        moveNext(G->adjac[u]);
    }
    G->color[u] = 'b';
    G->time++;
    G->finish[u] = G->time;
    prepend(S, u);
}

void DFS(GraphA G, ListA S){
    if (length(S) != getOrder(G)){
        printf("Called DFS on a Graph whose order != the Stack size\n");
        exit(1);
    }
    ListA Stack = copyList(S);
    makeEmpty(S);
    int u;
    for(u = 1; u <= getOrder(G); u++){
        G->color[u] = 'w';
        G->p[u] = NIL;
    }
    G->time = 0;
    moveTo(Stack, 0);
    while(!offEnd(Stack)){ 
        u = getElement(Stack);
        if (G->color[u] == 'w') visit(G, S, u);
        moveNext(Stack);
    }
    freeList(&Stack);
}


/***************************** Other operations *******************************/ 

GraphA transpose(GraphA G){
    int source, dest;
    GraphA trans = newGraph(getOrder(G));
    for (source = 1; source <= getOrder(G); source++){
        moveTo(G->adjac[source], 0);
        while(!offEnd(G->adjac[source])){
            dest = getElement(G->adjac[source]);
            addArc(trans, dest, source);
            moveNext(G->adjac[source]);
        }
    }
    return trans;
}

GraphA copyGraph(GraphA G){
    int i;
    GraphA tmp = newGraph(getOrder(G));
    for (i = 1; i <= getOrder(G); i++){
        tmp->adjac[i] = copyList(G->adjac[i]);
    }
    return tmp;
}

void printGraph(FILE* out, GraphA G){
    int i;
    for(i = 1; i <= getOrder(G); i++){
        fprintf(out, "%d:", i);
        printList(out, G->adjac[i]); 
    }
}
