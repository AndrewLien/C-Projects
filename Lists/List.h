/*andrew lien 
 * pa4
 * Patrick Tantalo
 * CS101
 * List.h
 */
#ifndef __LIST_H__
#define __LIST_H__
#include <stdbool.h>
typedef struct ListObj* List;

List newList(void);

void clear(List);

void freeList(List*);

// Access functions

bool isEmpty(List);

int length(List);
int getFront(List);
int getIndex(List);
int offEnd(List);

int front(List);

int back(List);

int getElement(List);

int equals(List, List);

// Manipulation procedures
void makeEmpty(List);
void movePrev(List);

void moveNext(List);
void moveFront(List);

void moveTo(List, int);

void prepend(List, int);

void append(List, int);

void insertBefore(List, int);

void insertAfter(List, int);

void deleteFront(List);

void deleteBack(List);

void delete(List);

//Misc

void printList(FILE*, List);

List copyList(List);
#endif
