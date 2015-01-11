#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <wchar.h>
#include "List.h"

#define MAXSIZE 160
#define MINSIZE 40

void readInputFile(char buffer[],size_t size, 
                   char** lexlines, int max_size, char *filen,
                    List L){
                   
    // open files for reading and writing
   FILE *in = fopen(filen, "r");
   if( in==NULL ){
     printf("Unable to open file %s for reading\n", filen);
     exit(1);
   }
   
 char* hasline = fgets(buffer, MAXSIZE, in);
   char* numLines;
   for(; hasline != NULL; hasline = fgets(buffer, MAXSIZE, in)){
     if(size == max_size - 1){
       max_size *= 2;
       lexlines = realloc(lexlines, max_size * sizeof(char*));
       assert(lexlines != NULL);
     }
     numLines = strchr(buffer, '\n');
     if(numLines != NULL) *numLines = '\0';
     lexlines[size++] = strdup(buffer);
   }
   fclose(in);
    /*insert in order*/
   prepend(L, 0);
   moveTo(L, 0);
   int cmp;
   for(int i = 1; i < size; ++i){
     for(int j = i; j >= 0; --j){
       cmp = strcmp(lexlines[i], lexlines[getElement(L)]);
       if(cmp >= 0){
         insertAfter(L, i);
         moveTo(L, length(L) - 1);
         break;
       }else if(j == 0){
         prepend(L, i);
         moveTo(L, length(L) - 1);
         break;
       }
       if(length(L) > 1 && getIndex(L) != 0) movePrev(L);
     }
   }
}

int main(int argc, char *argv[]){
  /* variables declared */
  List L = newList();
  size_t size = 0, max_size = MINSIZE;
  char buffer[MAXSIZE];
  char** lexlines = malloc(max_size * sizeof(char*));

  if(argc != 3){
    printf("Usage: %s <input file> <output file>\n",argv[0]);
    exit(1);
  }


readInputFile(buffer,size,lexlines, max_size,argv[1], L);
   
   //write to the file after inserting array 
      moveTo(L,0);
      FILE *out = fopen(argv[2],"w");
      if(out == NULL){
        printf("Cannot open file %s for writting. Cannot proceed", argv[2]);
        exit(1);
      }
      for(; getIndex(L) != -1; moveNext(L)){
        char* tmporary = lexlines[getElement(L)];
        fprintf(out, "%s\n", tmporary);
        free(tmporary);
      }
      fclose(out);
      freeList(&L);
      free(lexlines);
       
  return(0);   
}
