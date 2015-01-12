//Andrew Lien
//Pa4
//List.c
//CMPS 101 Patrick Tantalo
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "List.h"

//typedef struct ListObj* List;

//typedef struct node node;

typedef struct node{
  int data;
  struct node* prev;
  struct node* next;
} node;

struct ListObj{
  node* front;
  node* back;
  size_t length;
  int currentPosition;
  node* curr;
};


// Constructors-Destructors ---------------------------------------------------
List newList(void){
  List this = malloc(sizeof(struct ListObj));
  assert(this != NULL);
  this->front = NULL;
  this->back = NULL;
  this->length = 0;
  this->currentPosition = -1;
  this->curr = NULL;
  return this;
}

void freeList(List* L){
  clear(*L);
  free(*L);
}

// Access functions -----------------------------------------------------------

bool isEmpty(List L){
  return L->length == 0;
}

int length(List L){
  return L->length;
}

int getIndex(List L){
  if(L->length == 0){
    fprintf(stderr, "List is empty, function cannot proceed\n");
    exit(1);
  }
  return L->currentPosition;
}
int offEnd(List L) {
	if ( L == NULL ) {
		printf("List Error: calling offEnd() on NULL ListRef\n");
		exit(1);
	}
	return (L->curr == NULL);
}

int front(List L){
  if(L->length == 0){
    fprintf(stderr, "List is empty, function cannot proceed\n");
    exit(1);
  }
  return L->front->data;
}

int back(List L){
  if(L->length == 0){
    fprintf(stderr, "List is empty, function cannot proceed\n");
    exit(1);
  }
  return L->back->data;
}
int getFront(List L) {
	if ( L == NULL ) {
		printf("List Error: calling getFront() on NULL ListRef\n");
		exit(1);
	}
	if ( isEmpty(L) ) {
		//printf("List Error: calling getFront() on an empty List\n");
	    return 0;
	}
	return (L->front->data);
}

int getElement(List L){
  if(L->length == 0){
    fprintf(stderr, "List is empty, function cannot proceed\n");
    exit(1);
  }
  if(L->currentPosition == -1){
    fprintf(stderr, "Invalid pointer index\n");
    exit(1);
  }
  return L->curr->data;
} 

int equals(List A, List B){
  if(A->length != B->length) return 0;
  node* temp1 = A->front;
  node* temp2 = B->front;
  while(temp1 != NULL){
    if(temp1->data != temp2->data) return 0;
    temp1 = temp1->next;
    temp2 = temp2->next;
  }
  return 1;
}

// Manipulation procedures ----------------------------------------------------
void makeEmpty(List L) {
	if ( L == NULL ) {
		printf("List Error: calling makeEmpty() on NULL ListRef\n");
		exit(1);
	}
	if ( L->front == NULL) {
		return;
	}
	while( !isEmpty(L) ) {
		deleteFront(L);
	}
}
void clear(List L){
  node* tmporary;
  L->curr = L->front;
  L->front = NULL;
  L->back = NULL;
  while(L->curr != NULL){
    tmporary = L->curr;
    L->curr = L->curr->next;
    free(tmporary);
  }
  L->currentPosition = -1;
  L->length = 0;
}
void moveTo(List L, int i){
  if(L->currentPosition == -1){
    L->curr = L->front;
    L->currentPosition = 0;
  }
  //covers the spots where currentPosition is off the list
  if(i >= 0 && i < L->length);
  else{
    L->currentPosition = -1;
    return;
  }
  //if want to move at front of list
  if(i == 0){
    L->curr = L->front;
    L->currentPosition = i;
    return;
  }
  //if what to move at the back of the list
  if(i == L->length - 1){
    L->curr = L->back;
    L->currentPosition = i;
    return;
  }
  //the 'else' of all, in the middle of list
  while(L->currentPosition != i){
    if(L->currentPosition < i) moveNext(L);
    else movePrev(L);
  }
}

void movePrev(List L){
  if(L->currentPosition > 0 && L->currentPosition < L->length){
//  printf("If statement\n");
    --L->currentPosition;
    L->curr = L->curr->prev;
  }else{
//  printf("ELse statement\n");
    L->currentPosition = -1;
    L->curr = NULL;
  }
}

void moveFront(List L) {
	if ( L == NULL ) {
		printf("List Error: calling moveFront() on NULL ListRef\n");
		exit(1);
	}
	if ( isEmpty(L) ) {
		//printf("List Error: calling moveFront() on an empty List\n");
		//exit(1);
		L->currentPosition = 0;
		return;
	}
	L->curr = L->front;
	L->currentPosition = 0;
}
void moveNext(List L){
  if(L->currentPosition >= 0 && L->currentPosition < L->length - 1){
    ++L->currentPosition;
    L->curr = L->curr->next;
  }else{
    L->currentPosition = -1;
    L->curr = NULL;
  }
}


void prepend(List L, int data){

  ++L->length;
  node* n = malloc(sizeof(struct node));
  n->data = data;
  n->next = L->front;
  n->prev = NULL;
  if(L->length == 1) L->back = n;
  else L->front->prev = n;
  if(L->currentPosition > -1) ++L->currentPosition;
  L->front = n;
  printf("The state of the current position is %d\n", L->currentPosition);
}

void append(List L, int data){
  ++L->length;
  node* n = malloc(sizeof(struct node));
  n->data = data;
  n->prev = L->back;
  n->next = NULL;
  if(L->length == 1) L->front = n;
  else L->back->next = n;
  L->back = n;
}

void insertBefore(List L, int data){
  if(L->length == 0){
    fprintf(stderr, "Cursor element is off the list, function cannot proceed\n");
    exit(1);
  }
  if(!(L->currentPosition >= 0)){
    fprintf(stderr, "Cursor is off the list, function cannot proceed\n");
    exit(1);
  }
  node* n = malloc(sizeof(struct node));
  
  assert(n!=NULL);
  n->data = data;
  n->next = L->curr;
  n->prev = L->curr->prev;
  L->curr->prev = n;
  if(L->currentPosition == 0){ L->front = n; }
  else{ 
  assert(n->prev != NULL);
    // n->prev->next = n; 
    n->prev->next = n;
    }
  
  ++L->length;
  ++L->currentPosition;
 // if(L->currentPosition > -1) ++L->currentPosition;
 /*
 	if ( L->curr->prev == NULL ) {
		N->next = L->front;
		L->front->prev = N;
		L->front = N;
	}else {
		N->prev = L->curr->prev;
		N->next = L->curr;
		L->curr->prev->next = N;
		L->curr->prev = N;
		printf("N->data : %d\n", N->data);
	}
	++(L->length);*/
}

void insertAfter(List L, int data){
  if(L->length == 0){
    fprintf(stderr, "Cursor element is off the list, function cannot proceed\n");
    exit(1);
  }
  if(!(L->currentPosition >= 0)){
    fprintf(stderr, "Cursor is off the list, function cannot proceed\n");
    exit(1);
  }
  node* n = malloc(sizeof(struct node));
  n->data = data;
  n->prev = L->curr;
  n->next = L->curr->next;
  L->curr->next = n;
  if(L->currentPosition == (L->length - 1)) L->back = n;
  else n->next->prev = n;
  ++L->length;
}

void deleteFront(List L){
  if(L->length == 0){
    fprintf(stderr, "List is empty, function cannot proceed\n");
    exit(1);
  }
  if(L->currentPosition > -1) --L->currentPosition;
  if(L->curr == L->front) L->curr = NULL;
//  printf("pass 1\n");
  node* tmporary = L->front;
 // L->front = L->front->next;
  //  printf("pass 2\n");
//  node* tmporary = L->front->prev;
  //  printf("pass 3\n");
  if(L->length > 1){
  L->front = L->front->next;
  L->front->prev = NULL;
  }
  //  printf("pass 4\n");
    --L->length;
  if(L->length == 0) L->back = NULL;
  free(tmporary);
  //  printf("pass 5\n");
}

void deleteBack(List L){
  if(L->length == 0){
    fprintf(stderr, "List is empty, function cannot proceed\n");
    exit(1);
  }
  if(L->curr == L->back){
    L->curr = NULL;
    L->currentPosition = -1;
  }
  node* tmporary = L->back;
  L->back = L->back->prev;
  L->back->next = NULL;
  --L->length;
  if(L->length == 0) L->back = NULL;
  free(tmporary);
}

void delete(List L){
  if(L->length == 0){
    fprintf(stderr, "Cursor element does not exist\n");
    exit(1);
  }
  if(!(L->currentPosition >= 0)){
    fprintf(stderr, "Cursor is turned off\n");
    exit(1);
  }
  if(L->currentPosition == 0) deleteFront(L);
  else if(L->currentPosition == L->length - 1)
    deleteBack(L);
  else{
    L->curr->prev->next = L->curr->next;
    L->curr->next->prev = L->curr->prev;
    node* tmporary = L->curr;
    L->curr = NULL;
    L->currentPosition = -1;
    --L->length;
    free(tmporary);
  }
}

// Other operations -----------------------------------------------------------
void printList(FILE* out, List L){
	if ( L == NULL ) {
		printf("List Error: calling printList() on NULL List\n");
		exit(1);
	}
//printf("L->front->data is %d", L->front->data);
  for(node* tmporary = L->front; tmporary != NULL; tmporary = tmporary->next){
    fprintf(out, "%d ", tmporary->data);
  //  printf("Current index: %d \n", L->currentPosition);

  }
}

List copyList(List L){
  List cpy = newList();
  //L->curr = front;
  node* tmporary = L->front;
  while(tmporary != NULL){
    append(cpy, tmporary->data);
    tmporary = tmporary->next;
  }
  return cpy;
}