/*andrew lien 
 * pa5
 * Patrick Tantalo
 * CS101
 * ListTest.c
 */

#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main(int argc, char* argv[]){
      int i;
      ListA A = newList();
      ListA B = newList();
      ListA C = NULL;

      for(i = 1; i <= 10; i++){
         append(A, i);
         append(B, 11-i);
      }
      printf("A = ");
      printList(stdout, A);
      printf("\n"); 
      printf("B = ");
      printList(stdout, B );
      printf("\n");

      for(i = 1; i <= 6; i++){
         prepend(A, getBack(B));
         deleteBack(B);
      }

      printf("A.prepend() of last 6 elements of B  = ");
      printList(stdout, A);
      printf("\n");

      printf("deleteBack(B) * 6 = ");
      printList(stdout, B);
      printf("\n");

      C = copyList(A);
      printf("C = A.copy() = ");
      printList(stdout, C);
      printf("\n");

      printf("Does A = B? ");
      printf("%s\n", equals(A,B)?"true":"false");

      printf("Does A = C? "); 
      printf("%s\n", equals(A,C)?"true":"false");

      printf("getFront(A) = %d\n", getFront(A));
      printf("getBack(A) = %d\n", getBack(A));

      moveTo(A, 5);
      printf("moveTo(A, 5)+ getElement(A) = %d\n", getElement(A));
      
      insertBefore(A, 9);
      printf("insertBefore(A, 9) = ");
      printList(stdout, A);
      printf("\n");
      
      insertAfter(A, 7);
      printf("insertAfter(A, 7) = ");
      printList(stdout, A);
      printf("\n");

      printf("getIndex(A) = %d\n", getIndex(A));

      movePrev(A);
      printf("movePrev(A) + getIndex(A) = %d\n", getIndex(A));

      delete(A);
      printf("delete(A) = ");
      printList(stdout, A);
      printf("\n");

      deleteFront(A);
      printf("deleteFront(A)  = ");
      printList(stdout, A);
      printf("\n");
 
      return(0);

}

