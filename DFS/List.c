/*andrew lien 
 * pa5
 * Patrick Tantalo
 * CS101
 * List.c
 */

#include<stdio.h>
#include<stdlib.h>
#include "List.h"



typedef struct Node{
   int data;
   struct Node* next;
   struct Node* prev;
} Node;

typedef struct List{
   NodeA front;
   NodeA back;
   NodeA curr;
   int length;
} List;
ListA newList(void){
   ListA L = malloc(sizeof(List));
   L->front = L->back = L->curr = NULL;
   L->length = 0;
   return(L);
}

void freeList(ListA* pL){
   if(pL==NULL || *pL==NULL) { return; }
   while( !isEmpty(*pL) ) { deleteBack(*pL); }
   free(*pL);
   *pL = NULL;
}
NodeA newNode(int data){
   NodeA N = malloc(sizeof(Node));
   N->data = data;
   N->next = NULL;
   N->prev = NULL;
   return(N);
}

/*
*  freeNode
*  Frees heap memory pointed to by pN. Private.
*/
void freeNode(NodeA* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}


int length(ListA L){
   if( L==NULL ){
      printf("List Error: calling length() on NULL ListA\n");
      exit(1);
   }
   return(L->length);
}
   
/*
*  isEmpty 
*  Returns True if L is empty, otherwise returns 0
*/
int isEmpty(ListA L){
   if( L==NULL ){
      printf("List Error: calling isEmpty() on NULL ListA\n");
      exit(1);
   }
   return(L->length==0);
}

/*
* offEnd
* Returns True if curr is NULL, otherwise returns 0
*/
int offEnd(ListA L){
    if (L == NULL){
        printf("List Error calling offEnd() on NULL ListA\n");
        exit(1);
    }
    return(L->curr==NULL);
}

/*
* getIndex
* Returns position of curr index in respect to the List
*/
int getIndex(ListA L){
    if (L->curr == NULL){ return -1;}
    int index = 1;
    Node* N = NULL;
    for (N = L->front; N != L->curr ; N = N->next){
        index ++;
    } 
    return index;
}

/*
*  getFront
*  Returns the value at the front of L.
*  Pre: !isEmpty(L)
*/
int getFront(ListA L){
   if( L==NULL ){
      printf("List Error: calling getFront() on NULL ListA\n");
      exit(1);
   }
   return(L->front->data);
}

/*
*  getBack
*  Returns the value at the front of L.
*  Pre: !isEmpty(L)
*/
int getBack(ListA L){
   if( L==NULL ){
      printf("List Error: calling getBack() on NULL ListA\n");  
      exit(1);
   }
   return(L->back->data);
}

int getElement(ListA L){
   if( L==NULL ){
      printf("List Error: calling getElement() on NULL ListA\n");
      exit(1);
   }
   return(L->curr->data); 
}

int equals(ListA A, ListA B){
   int flag = 1;  
   Node* N = NULL;
   Node* M = NULL;  
   if( A==NULL || B==NULL ){
      printf("List Error: calling equals() on NULL ListA\n");
      exit(1);
   }
   N = A->front;
   M = B->front;
   if( A->length != B->length ) { return 0; }
   while( flag && N!=NULL){
      flag = (N->data==M->data);
      N = N->next;
      M = M->next;
   }
   return flag;
}

void makeEmpty(ListA L){
   if(!isEmpty(L)){
      while( !isEmpty(L)){ deleteBack(L); }
   }
} 
void moveTo(ListA L, int i){
   int j;
   L->curr = L->front;
   for (j = 0; j < i; j++){
      moveNext(L);
   }
} 

void movePrev(ListA L){
   if (isEmpty(L)){printf("List Error: calling movePrev() on NULL ListA\n");}
   else if (offEnd(L)){printf("List Error: calling movePrev() on offEnd ListA\n");}
   else{ L->curr = L->curr->prev;}
}

void moveNext(ListA L){
   if (isEmpty(L)){printf("List Error: calling moveNext() on NULL ListA\n");}
   else if (offEnd(L)){printf("List Error: calling moveNext() on offEnd ListA\n");}
   else{ L->curr = L->curr->next;}
}

void prepend(ListA L, int data){
   NodeA N = newNode(data);
   if( L == NULL){
      printf("List Error: calling prepend() on NULL ListA\n");
      exit(1); 
   }
   if ( isEmpty(L) ) {L->front = L->back = N; }
   else { N->next = L->front; L->front->prev = N; L->front = N; }
   L->length++;
}

void append(ListA L, int data){
   NodeA N = newNode(data);
   if( L==NULL ){
       printf("List Error: calling append() on NULL ListA\n");
       exit(1);
   }
   if( isEmpty(L) ) { L->front = L->back = N; }
   else { L->back->next = N; N->prev = L->back; L->back = N; }
   L->length++;
}

void insertBefore(ListA L, int data){
   if ( !isEmpty(L) && !offEnd(L) ){
      if (getIndex(L) == 1){
         prepend(L, data);
         return;
      }
      else{
         NodeA N = newNode(data);
         L->curr->prev->next = N;
         N->prev = L->curr->prev;
         N->next = L->curr;
         L->curr->prev = N;
      }
      L->length++;
   }
} 


void insertAfter(ListA L, int data){
 if ( !isEmpty(L) && !offEnd(L) ){
      if (getIndex(L) == length(L)){
         append(L, data);
         return;
      }
      else{
         NodeA N = newNode(data);
         L->curr->next->prev = N;
         N->next = L->curr->next;
         L->curr->next = N;
         N->prev = L->curr;
      }
      L->length++;
   }
}


void deleteFront(ListA L){
   NodeA N = NULL;

   if( L==NULL ){
      printf("List Error: calling deleteFont() on NULL ListA\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling deleteFront on an empty List\n");
      exit(1);
   }
   N = L->front;
   if( length(L)>1 ) { L->front = L->front->next; L->front->prev = NULL; }
   else { L->front = L->back = NULL; }
   L->length--;
   freeNode(&N);
}
void deleteBack(ListA L){
   NodeA N = NULL;

   if( L==NULL ){
      printf("List Error: calling deleteBack() on NULL ListA\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling deleteBack on an empty List\n");
      exit(1);
   }
   N = L->back;
   if( length(L)>1 ) { L->back = L->back->prev; L->back->next = NULL; }
   else { L->front = L->back = NULL; }
   L->length--;
   freeNode(&N);
}

void delete(ListA L){
   NodeA N = NULL;
    
   if( L==NULL ){
      printf("List Error: calling delete() on NULL ListA\n");
      exit(1);
   }
   if( isEmpty(L) ){
      printf("List Error: calling delete on an empty List\n");
      exit(1);
   }
   N = L->curr;
   if( length(L)>1 ) { 
       L->curr->prev = L->curr->next;
       L->curr->next->prev = L->curr->prev;
       L->curr->next = L->curr->prev = NULL;
   }
   else { L->front = L->back = L->curr = NULL; }
   L->length--;
   freeNode(&N);   
} 

void printList(FILE* out, ListA L){
   Node* N = NULL;

   if( L==NULL ){
      printf("List Error: calling printList() on NULL ListA\n");
      exit(1);
   }
   if(isEmpty(L)) fprintf(out, "\n");
   for(N = L->front; N != NULL; N = N->next){
      if(N->next == NULL){fprintf(out, " %d\n", N->data);}
      else if (N->prev == NULL){fprintf(out, " %d", N->data);}
      else {fprintf(out, " %d", N->data);}
   }
}
ListA copyList(ListA L){
   ListA copy = newList();
   NodeA temp = L->front;

   while( temp!=NULL){
      append(copy , temp->data);
      temp = temp->next;
   }
   return copy;
}



