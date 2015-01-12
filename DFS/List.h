/*andrew lien 
 * pa5
 * Patrick Tantalo
 * CS101
 * List.h
 */

#if !defined(_LIST_H_INCLUDE_)
#define _LIST_H_INCLUDE_

typedef struct List * ListA; 
typedef struct Node * NodeA;
ListA newList(void);
void freeList(ListA* pL);
void freeNode(NodeA* pN); 
int length(ListA L);
int isEmpty(ListA L);
int offEnd(ListA L); 
int getIndex(ListA L); 
int getFront(ListA L);
int getBack(ListA L);
int getElement(ListA L);
int equals(ListA A, ListA B);  
void makeEmpty(ListA L); 
void moveTo(ListA L, int i); 
void movePrev(ListA L); 
void moveNext(ListA L); 
void prepend(ListA L, int data);
void append(ListA L, int data);
void insertBefore(ListA L, int data); 
void insertAfter(ListA L, int data); 
void deleteFront(ListA L);
void deleteBack(ListA L);
void delete(ListA L);
void printList(FILE* out, ListA L);

ListA copyList(ListA L);

#endif
