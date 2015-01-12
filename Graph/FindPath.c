/*andrew lien 
 * pa4
 * Patrick Tantalo
 * CS101
 * FindPath.c
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"Graph.h"
#include"List.h"

#define MAXLEN 250
void printDandP(FILE* out, Graph G, List path, int dest) {
	fprintf(out,"\n");
	fprintf(out, "The distance from %d to %d is ", getSource(G), dest);
	if ( getFront(path) == NIL ) {
		fprintf(out, "infinity\n");
		fprintf(out, "No %d-%d path exists", getSource(G), dest);
	}else {
		fprintf(out, "%d\n", getDist(G, dest));
		fprintf(out, "A shortest %d-%d path is: ", getSource(G), dest);
		printList(out, path);
	}
	fprintf(out,"\n");
}

int main(int argc, char *argv[]){
  
  /*check command line arguments*/
  if(argc!= 3){
    printf("Usage: %s infile outfile\n", argv[0]);
    exit(1);
  }
  
  /*open files for reading and writing*/
  FILE *in, *out;
  in = fopen(argv[1],"r");
  out = fopen(argv[2], "w");
  if(in == NULL){
    printf("Unable to open %s for reading\n",argv[1]);
    exit(1);
  }
  if(out == NULL){
    printf("Unable to open %s for writing\b", argv[2]);
    exit(1);
  }
	
	/* declare and initialize variables */
	char line[MAXLEN];
	char* token;
	int linenum = 0;
	bool flag = false;
	int  n, x, y, source, dest;
	Graph G;
	List path = newList();
	
	/* read and store the graph and print out its adjacency list */
	char delims[] = " ";
	while( !flag && fgets(line, MAXLEN, in) != NULL ) {
		++linenum;
		token = strtok(line, delims);
		if( linenum == 1 ) {
			n = atoi(token);
			G = newGraph(n);
		}else {
			x = atoi(token);
			token = strtok(NULL, "delims");
			y = atoi(token);
			if( x != 0 ) {
			  addEdge(G, x, y);
			}
			else { flag = true; }
			
		}
	}
	//printf("The Final graph: \n");
	printGraph(out, G);	
	//print out the destination & path
		while( fgets(line, MAXLEN, in) != NULL ) {
		token = strtok(line, " \n");
		source = atoi(token);
		token = strtok(NULL, " \n");
		dest = atoi(token);
		if( source != NIL ){
			BFS(G, source);
			makeEmpty(path);
			getPath(path, G, dest);
			printDandP(out, G, path, dest);
		}
	}

/* free memory */
	freeList(&path);
	freeGraph(&G);
	
	/* close files */
	fclose(in);
	fclose(out);
	
  return(0);
}