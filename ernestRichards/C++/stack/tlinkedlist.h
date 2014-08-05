/* Alfonso Puga & Ernest Richards */

/* TO DO
 */

#pragma once
#include <iostream>
#include <cstring>
#include "listnode.h"

using namespace std;

template <class T>
class LinkedList
{
		  private:
					 ListNode<T> *head;
					 bool doubly_linked;
					 bool dummy_head;

					 ListNode<T> *findPrevious(const ListNode<T> *);

		  public:
					 /* con/destructors */

					 LinkedList(const bool & dl = false, const bool & dh = false);
					 LinkedList(const LinkedList &);
					 ~LinkedList();

					 /* gets */

					 bool empty (void) const;
					 bool isDoublyLinked (void) const {return (doubly_linked);}
					 bool hasDummyHead(void) const {return (dummy_head);}
					 bool hasInputFunction(void) const {return (head->hasInputFunction());}
					 T getValue (const char * prompt = NULL) const;
					 ListNode<T> *findFirst (const T &) const;
					 LinkedList<ListNode<T> *> * findAll (const T & elem) const;
					 /* returns a character pointer, but uses oss.str.c_str */
					 char * toString (void);
					 ListNode<T> * getHead (void) const {return (head);}
					 ListNode<T> * getLast (void) const
					 {
								if (doubly_linked)
								{
										  return (head->getPrevious());
								}
								ListNode<T> * node = head, * prev = NULL;
								if (dummy_head)
								{
										  node = node->getNext();
										  while (node)
										  {
													 prev = node;
													 node = node->getNext();
										  }
										  return (prev);
								}
								while (node)
								{
										  prev = node;
										  node = node->getNext();
								}
								return (prev);
					 }

					 /* sets */

					 void insert(const T &, ListNode<T> * prev = NULL);
					 void remove(ListNode<T> *);
					 void remove(T);
					 void erase(void);
					 void setDoublyLinked (const bool & b = false) {doubly_linked = b;}
					 void setDummyHead (const bool & b = false) {dummy_head = b;}
					 void setDummyHead (const T & d) {setHead(d);}
					 void setHead (const T & d) {*head = d;}
					 void setHead (ListNode<T> *d) {head = d;}

					 /* operators */

					 void operator = (const LinkedList &);
					 bool operator ! () const {return (this == NULL);}
					 /* Will use the stream operator in ListNode */
					 friend ostream & operator << (ostream &o, const LinkedList<T> &right)
					 {
								ListNode<T> *node = right.head;

								if (right.hasDummyHead())
								{
										  while(node != right.getHead() && node->getNext() != right.getHead())
										  {
													 o << *node << " ";
													 node = node->getNext();
										  }
								}
								else
								{
										  while(node != NULL && node->getNext() != NULL)
										  {
													 o << *node << " ";
													 node = node->getNext();
										  }
								}
								o << *node << '\0';
								return (o);
					 }
};

template <class T>
char * LinkedList<T>::toString (void)
{
		  if (empty())
		  {
					 return (NULL);
		  }
		  ListNode<T> *node = head;
		  int len = 0;
		  char * str;

		  while(node != NULL)
		  {
					 len += strlen((const char *)((*node).toString()));
					 len += 1;
					 node = node->getNext();
		  }

		  node = head;
		  try
		  {
					 str = new char [(sizeof(char) * len)];
		  }
		  catch (bad_alloc)
		  {
					 cout << "Memory Allocation Error\n" << flush;
					 return (NULL);
		  }
		  catch (...)
		  {
					 cout << "An Unknown Error Occured\n" << flush;
					 return (NULL);
		  }
		  strncpy(str, (const char *)(((*node).toString())), strlen(((*node).toString())));
		  strncat(str, (const char *)("\n"), 1);
		  node = node->getNext();

		  while(node != NULL)
		  {
					 strncat(str, (const char *)(((*node).toString())), strlen(((*node).toString())));
					 strncat(str, (const char *)("\n"), 1);
					 node = node->getNext();
		  }

		  return (str);
}

template <class T>
ListNode<T> * LinkedList<T>::findPrevious(const ListNode<T> *ptr)
{
		  ListNode<T> *node = NULL;

		  if (isDoublyLinked())
		  {
					 node = ptr->getPrevious();
					 if (node == head)
					 {
								return (NULL);
								/* should this return heads previous? */
					 }
					 return (node);
		  }

		  node = head;
		  /* current node we're findFirsting, start at head */

		  /* singly linked list with dummy head */
		  if (hasDummyHead())
		  {
					 node = node->getNext();
					 while(node != head)
					 {
								if(node->getNext() == ptr)
								{
										  return (node);
								}
								node = node->getNext();
					 }
		  }
		  /* singly linked list with no dummy head */
		  else
		  {
					 while(node != NULL)
					 {
								if(node->getNext() == ptr)
								{
										  return (node);
								}
								node = node->getNext();
					 }
		  }

		  return (NULL);
		  /* not found */
}

template <class T>
LinkedList<T>::LinkedList(const bool & dl, const bool & dh)
{
		  head = NULL;
		  setDoublyLinked(dl);
		  setDummyHead(dh);
}

template <class T>
LinkedList<T>::~LinkedList()
{

		  /* tmp is one to delete, node is current node */
		  ListNode<T> *tmp = NULL, *node = head;

		  while(node != NULL)
		  {
					 tmp = node;
					 /* Delete the current node */
					 node = node->getNext();
					 /* Increment node pointer */
					 delete (tmp);
		  }
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T> &right)
{
		  LinkedList<T> *new_ll = NULL;

		  try
		  {
					 new_ll = new LinkedList<T>;
		  }
		  catch(bad_alloc)
		  {
					 cout << "Memory error\n" << flush;
					 new_ll = NULL;
		  }
		  catch(...)
		  {
					 cout << "Unknown error\n" << flush;
					 new_ll = NULL;
		  }
		  if(new_ll == NULL)
		  {
					 cout << "Allocation failed.\n" << flush;
					 head = NULL;
					 return;
		  }
		  *new_ll = right;
}

template <class T>
void LinkedList<T>::erase ()
{
		  if (empty())
		  {
					 return;
		  }
		  ListNode<T> * ptr, * tmp;
		  if (hasDummyHead())
		  {
					 ptr = head->getNext();
		  }
		  else
		  {
					 ptr = head;
		  }
		  while (ptr)
		  {
					 tmp = ptr;
					 ptr = ptr->getNext();
					 delete (tmp);
		  }
}

template <class T>
void LinkedList<T>::operator = (const LinkedList<T> &right)
{
		  ListNode<T> *node = NULL, *new_node = NULL, *prev = NULL;


		  /* Check for a = a syntax and exit function */
		  if(this == &right)
		  {
					 return;
		  }

		  doubly_linked = right.doubly_linked;
		  dummy_head = right.dummy_head;

		  this->erase();

		  node = right.head;
		  if(node == NULL)  
					 /* empty source list */
		  {
					 return;
		  }


		  /* Copy the head node */
		  try
		  {
					 new_node = new ListNode<T>;
		  }
		  catch (bad_alloc)
		  {
					 cout << "Memory Error\n" << flush;
					 new_node = NULL;
		  }
		  catch (...)
		  {
					 cout << "An Unknown Error Occured\n" << flush;
					 new_node = NULL;
		  }
		  if(new_node == NULL)
		  {
					 cout << "Allocation failed.\n" << flush;
					 head = NULL;
					 return;
		  }

		  /*
			* no need to account for dummy head node, singlly/doubly linked lists, just copy everything, including dummy head (if one exists)
			*/

		  new_node->setData(node->getData());
		  /* copy data */
		  new_node->setPrevious(NULL);
		  new_node->setNext(NULL);
		  new_node->setHead(true);
		  head = new_node;
		  prev = new_node;
		  node = node->getNext();


		  /* Copy the rest of the list */
		  while(node != NULL && node != head)
		  {
					 try
					 {
								new_node = new ListNode<T>;
					 }
					 catch (bad_alloc)
					 {
								cout << "Memory Error\n" << flush;
								new_node = NULL;
					 }
					 catch (...)
					 {
								cout << "An Unknown Error Occured\n" << flush;
								new_node = NULL;
					 }
					 if (new_node == NULL)
					 {
								cout << "Allocation failed.\n" << flush;
								prev->setNext(NULL);
								return;
					 }
					 new_node->setData(node->getData());
					 /* copy data */
					 prev->setNext(new_node);
					 if (doubly_linked)
					 {
								new_node->setPrevious(prev);
								if (node->getNext() == head)
								{
										  head->setPrevious(new_node);
								}
					 }
					 else
					 {
								new_node->setPrevious(NULL);
					 }
					 new_node->setHead(false);
					 prev = new_node;
					 node = node->getNext();
		  }
		  /* mark end of list */
		  if (dummy_head)
		  {
					 prev->setNext(head);
		  }
		  else
		  {
					 prev->setNext(NULL);
		  }
}

template <class T>
bool LinkedList<T>::empty(void) const
{
		  if (!dummy_head)
		  {
					 return (head == NULL);
		  }
		  return ((head->getNext()) == NULL);
}

template <class T>
T LinkedList<T>::getValue(const char * prompt) const
{
		  T c;
		  /* HERE */
		  /*
			  if (haed->hasInputFunction())
			  {
			  c = (head->getData()).getValue();
			  }
			  else
			  */
		  {
					 if (prompt)
					 {
								cout << prompt << endl << flush;
					 }
					 else
					 {
								cout << "Enter a value: " << flush;
					 }
					 cin >> c;
					 while(cin.fail())
					 {
								cin.clear();
								cin.ignore(20, '\n');
								cout << "Error: Must enter a valid value.\n" << flush;
								cout << "Enter a value: " << flush;
								cin >> c;
					 }
		  }
		  return (c);
}

template <class T>
ListNode<T> * LinkedList<T>::findFirst(const T & elem) const
{
		  if (*head == elem)
		  {
					 return (head);
		  }
		  ListNode<T> * forward_node = head->getNext();
		  ListNode<T> * reverse_node = head->getPrevious();

		  if (forward_node && reverse_node)
		  {
					 while(forward_node != NULL && reverse_node != NULL &&
										  forward_node != reverse_node &&
										  forward_node->getNext() != reverse_node && reverse_node->getPrevious() != forward_node)
					 {
								if (forward_node != head)
								{
										  if( *forward_node == elem ) 
													 /* This will use the == operator in ListNode */
										  {
													 return (forward_node);
										  }
								}
								if (reverse_node != head)
								{
										  if( *reverse_node == elem ) 
										  {
													 return (reverse_node);
										  }
								}
								forward_node = forward_node->getNext();
								reverse_node = reverse_node->getPrevious();
					 }
					 if (forward_node == reverse_node)
					 {
								if (*forward_node == elem)
								{
										  return (forward_node);
								}
					 }
		  }
		  else if (forward_node)
		  {
					 while(forward_node != NULL)
					 {
								if (forward_node != head)
								{
										  if( *forward_node == elem ) 
										  {
													 return (forward_node);
										  }
								}
								forward_node = forward_node->getNext();
					 }
		  }
		  /* not found */
		  return (NULL);
}

template <class T>
LinkedList<ListNode<T> *> * LinkedList<T>::findAll(const T & elem) const
{
		  if (empty())
		  {
					 return (NULL);
		  }
		  ListNode<T> * forward_node = head;
		  ListNode<T> * reverse_node = head->getPrevious();

		  LinkedList<ListNode<T> *> * addr_list = new LinkedList<ListNode<T> *>;

		  if (forward_node && reverse_node)
		  {
					 while(forward_node != NULL && reverse_node != NULL &&
										  forward_node != reverse_node)
					 {
								if(*forward_node == elem ) 
										  /* This will use the == operator in ListNode */
								{
										  addr_list->insert((ListNode<T> *)forward_node);
								}
								if(*reverse_node == elem) 
								{
										  addr_list->insert(reverse_node);
								}
								forward_node = forward_node->getNext();
								reverse_node = reverse_node->getPrevious();
					 }
					 if (forward_node == reverse_node)
					 {
								if (*forward_node == elem)
								{
										  addr_list->insert(forward_node);
								}
					 }
		  }
		  else if (forward_node)
		  {
					 while(forward_node != NULL)
					 {
								if( *forward_node == elem ) 
								{
										  addr_list->insert(forward_node);
								}
								forward_node = forward_node->getNext();
					 }
		  }
		  return (addr_list);
}

template <class T>
void LinkedList<T>::insert(const T & elem, ListNode<T> *prev)
{
		  ListNode<T> * new_node;
		  if (prev)
		  {
					 if (!findFirst(prev -> getData()))
					 {
								cout << "\a\aAn Error Occured!!\nPrevious wasn't found in the list\n" << flush;
								return;
					 }
					 try
					 {
								new_node = new ListNode<T> (elem,(prev -> getNext()));
					 }
					 catch (bad_alloc)
					 {
								cout << "Memory Error\n" << flush;
								new_node = NULL;
					 }
					 catch (...)
					 {
								cout << "An Unknown Error Occured\n" << flush;
								new_node = NULL;
					 }
					 if (!new_node || new_node -> getData() != elem || new_node -> getNext() != prev -> getNext())
					 {
								cout << "\a\aNode creation failed\n" << flush;
								return;
					 }
					 prev -> setNext(new_node);
					 return;
		  }
		  try
		  {
					 new_node = new ListNode<T> (elem);
		  }
		  catch (bad_alloc)
		  {
					 cout << "Memory Error\n" << flush;
					 new_node = NULL;
		  }
		  catch (...)
		  {
					 cout << "An Unknown Error Occured\n" << flush;
					 new_node = NULL;
		  }
		  if (!new_node)
		  {
					 cout << "\a\aAn Error Occured\nNode creation failed\n" << flush;
					 return;
		  }
		  new_node -> setNext(head);
		  head = new_node;
		  return;
}

template <class T>
void LinkedList<T>::remove(ListNode<T> *ptr)
{
		  ListNode<T> *prev = NULL;

		  /* head delete */
		  if(ptr == head)
		  {
					 if (dummy_head)
					 {
								cout << "\a\aUnable to remove dummy head node\n" << flush;
								return;
					 }
					 if (doubly_linked)
					 {
								head->getNext()->setPrevious(head->getPrevious());
								head->getPrevious()->setNext(head->getNext());
					 }
					 /* increment head to 2nd element */
					 head = head->getNext();
					 delete (ptr);
		  }
		  else
		  {
					 prev = findPrevious(ptr);
					 if(prev == NULL)
					 {
								cout << "Error: Cannot delete. Node not in list.\n" << flush;
								return;
					 }
					 prev->setNext( ptr->getNext() );
					 if (doubly_linked)
					 {
								ptr->getNext()->setPrevious(prev);
					 }
					 delete (ptr);
		  }
		  cout << "Removal Succeded\n" << flush;
}

template <class T>
void LinkedList<T>::remove(T elem)
{
		  ListNode<T> *ptr = NULL;

		  ptr = findFirst(elem);
		  if(ptr == NULL)
		  {
					 cout << "Error: Cannot delete. Node not in list.\n" << flush;
					 return;
		  }
		  remove(ptr);
}

