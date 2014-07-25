#include<stdlib.h>
/*
Author: Alfonso Puga

Linked List with Dummy Head Node

*/


typedef struct _Node
{
   int used;
   int head;
   Node * next;
   Node * previous;
   void * data;
} Node;

typedef struct _LinkedList
{
   Node * headNode;
   int length;
}LinkedList;


void nodeInit(Node *);
Node * nodeAlloc();
int nodeDel(Node *);
int nodeIns();
int nodeCpy();
int nodeRdy();
/*==============================*/
void linkedListInit();
LinkedList * linkedListAlloc();
int linkedListDel();
int linkedListIns();
int linkedListCpy();
