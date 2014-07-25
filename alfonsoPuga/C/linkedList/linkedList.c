#include"linkedList.h"
void nodeInit(Node * node)
{
   
   node->used = 0;
   node->head = 0;
   node->next = NULL;
   node->previous = NULL;
   data = NULL;
}

Node * nodeAlloc()
{
   Node * nNode = NULL;
   nNode = malloc(sizeof(Node));
   nodeInit(nNode);
   return nNode;
}

int nodeDel(Node * node)
{
   if(nodeRdy(node))
   {
      if(node->head == 1)
      {
         
      }
   }
}

int nodeIns();
int nodeCpy();
int nodeRdy(Node * node)
{
   if(node == NULL || node->next == NULL || node->prev == NULL)
      return 0;
   else
      return 1;
}


void linkedListInit();
LinkedList * linkedListAlloc();
int linkedListDel();
int linkedListIns();
int linkedListCpy();

