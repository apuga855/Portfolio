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
					 ListNode<T> *find_previous(ListNode<T> *);

		  public:
					 LinkedList();                          // default constructor
					 LinkedList(const LinkedList &right);   // copy constructor
					 ~LinkedList();                         // destructor, deallocate list

					 void operator = (const LinkedList &right);

					 T getValue(const char * prompt = NULL);
					 bool empty();                          // is there a list?
					 ListNode<T> *search(T elem);            // find elem in list
					 void insert(T elem, ListNode<T> *prev); // insert element after prev
					 void remove(ListNode<T> *ptr);            // delete a specific node
					 void remove(T elem);                 // find elem and delete if found

					 /* returns a character pointer, but uses oss.str.c_str */
					 char * toString (void);

					 friend ostream & operator << (ostream &o, const LinkedList<T> &right)
					 {
								ListNode<T> *node = right.head;

								while(node != NULL)
								{
										  o << *node << " ";  // Will use the stream operator in ListNode
										  node = node->getNext();
								}
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
					 cout << "Memory Allocation Error\n";
					 return (NULL);
		  }
		  catch (...)
		  {
					 cout << "An Unknown Error Occured\n";
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
ListNode<T> * LinkedList<T>::find_previous(ListNode<T> *ptr)
{
		  ListNode<T> *node = head;  // current node we're searching, start at head

		  while(node != NULL)
		  {
					 // Check if the next node (one following "node") is ptr
					 if(node->getNext() == ptr)
					 {
								return (node);
					 }
					 // Increment the node pointer
					 node = node->getNext();
		  }
		  return (NULL);  // not found
}

template <class T>
LinkedList<T>::LinkedList()
{
		  head = NULL;
}

template <class T>
LinkedList<T>::~LinkedList()
{
		  // tmp is one to delete, node is current node
		  ListNode<T> *tmp = NULL, *node = head;

		  while(node != NULL)
		  {
					 tmp = node;  // Delete the current node
					 node = node->getNext();  // Increment node pointer
					 delete tmp;
		  }
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T> &right)
{
		  // node is the current node in the source list, new_node is the newly 
		  // allocated node for this list (copy of node), prev is the previously
		  // allocated node for this list
		  ListNode<T> *node = right.head, *new_node = NULL, *prev = NULL;

		  if(node == NULL)  // empty source list
		  {
					 head = NULL;
					 return;
		  }

		  // Copy the head node
		  try
		  {
					 new_node = new ListNode<T>;
		  }
		  catch(bad_alloc)
		  {
					 new_node = NULL;
		  }
		  if(new_node == NULL)
		  {
					 cout << "Allocation failed.\n";
					 head = NULL;
					 return;
		  }
		  new_node->setData(node->getData());  // copy data
		  head = new_node;
		  prev = new_node;
		  node = node->getNext();

		  // Copy the rest of the list
		  while(node != NULL)
		  {
					 try
					 {
								new_node = new ListNode<T>;
					 }
					 catch(bad_alloc)
					 {
								new_node = NULL;
					 }
					 if(new_node == NULL)
					 {
								cout << "Allocation failed.\n";
								prev->setNext(NULL);
								return;
					 }
					 new_node->setData(node->getData());  // copy data
					 prev->setNext(new_node); // Make previous node point to us
					 prev = new_node;
					 node = node->getNext();
		  }
		  prev->setNext(NULL);  // mark end of list
}

template <class T>
void LinkedList<T>::operator = (const LinkedList<T> &right)
{
		  ListNode<T> *tmp = NULL, *node = NULL, *new_node = NULL, *prev = NULL;

		  // Check for a = a syntax and exit function
		  if(this == &right)
		  {
					 return;
		  }

		  // Delete the previous list
		  node = head;
		  while(node != NULL)
		  {
					 tmp = node;  // Delete the current node
					 node = node->getNext();  // Increment node pointer
					 delete tmp;
		  }

		  // Copy the new list
		  node = right.head;
		  if(node == NULL)  // empty source list
		  {
					 head = NULL;
					 return;
		  }

		  // Copy the head node
		  try
		  {
					 new_node = new ListNode<T>;
		  }
		  catch (bad_alloc)
		  {
					 cout << "Memory Error\n";
					 new_node = NULL;
		  }
		  catch (...)
		  {
					 cout << "An Unknown Error Occured\n";
					 new_node = NULL;
		  }
		  if(new_node == NULL)
		  {
					 cout << "Allocation failed.\n";
					 head = NULL;
					 return;
		  }
		  new_node->setData(node->getData());  // copy data
		  head = new_node;
		  prev = new_node;
		  node = node->getNext();

		  // Copy the rest of the list
		  while(node != NULL)
		  {
					 try
					 {
								new_node = new ListNode<T>;
					 }
					 catch (bad_alloc)
					 {
								cout << "Memory Error\n";
								new_node = NULL;
					 }
					 catch (...)
					 {
								cout << "An Unknown Error Occured\n";
								new_node = NULL;
					 }
					 if (new_node == NULL)
					 {
								cout << "Allocation failed.\n";
								prev->setNext(NULL);
								return;
					 }
					 new_node->setData(node->getData());  // copy data
					 prev->setNext(new_node); // Make previous node point to us
					 prev = new_node;
					 node = node->getNext();
		  }
		  prev->setNext(NULL);  // mark end of list
}

template <class T>
bool LinkedList<T>::empty()
{
		  return (head == NULL);
}

template <class T>
T LinkedList<T>::getValue(const char * prompt)
{
		  T c;
		  if (prompt)
		  {
					 cout << "%s\n", prompt;
		  }
		  else
		  {
					 cout << "Enter a value: ";
		  }
		  cin >> c;
		  while(cin.fail())
		  {
					 cin.clear();
					 cin.ignore(20, '\n');
					 cout << "Error: Must enter a valid value.\n";
					 cout << "Enter a value: ";
					 cin >> c;
		  }
		  return (c);
}

template <class T>
ListNode<T> * LinkedList<T>::search(T elem)
{
		  ListNode<T> *node = head;

		  while(node != NULL)
		  {
					 if( *node == elem ) // This will use the == operator in ListNode
					 {
								return (node);
					 }
					 node = node->getNext();
		  }
		  return (NULL);  // not found
}

template <class T>
void LinkedList<T>::insert(T elem, ListNode<T> *prev)
{
		  if (prev)
		  {
					 if (!search(prev -> getData()))
					 {
								cout << "\a\aAn Error Occured!!\nPrevious wasn't found in the list\n";
								return;
					 }
					 ListNode<T> * new_node;
					 try
					 {
								new_node = new ListNode<T> (elem,(prev -> getNext()));
					 }
					 catch (bad_alloc)
					 {
								cout << "Memory Error\n";
								new_node = NULL;
					 }
					 catch (...)
					 {
								cout << "An Unknown Error Occured\n";
								new_node = NULL;
					 }
					 if (!new_node || new_node -> getData() != elem || new_node -> getNext() != prev -> getNext())
					 {
								cout << "\a\aNode creation failed\n";
								return;
					 }
					 prev -> setNext(new_node);
					 cout << "Insertion Complete!\n";
					 return;
		  }
		  ListNode<T> * new_node = new ListNode<T> (elem);
		  if (!new_node)
		  {
					 cout << "\a\aAn Error Occured!!\nNode creation failed\n";
					 return;
		  }
		  new_node -> setNext(head);
		  head = new_node;
		  cout << "Insertion Complete!\n";
		  return;
}

template <class T>
void LinkedList<T>::remove(ListNode<T> *ptr)
{
		  ListNode<T> *prev = NULL;

		  // head delete
		  if(ptr == head)
		  {
					 head = head->getNext();  // increment head to 2nd element
					 delete ptr;
		  }
		  else
		  {
					 prev = find_previous(ptr);
					 if(prev == NULL)
					 {
								cout << "Error: Cannot delete. Node not in list.\n";
								return;
					 }
					 prev->setNext( ptr->getNext() );
					 delete ptr;
		  }
}

template <class T>
void LinkedList<T>::remove(T elem)
{
		  ListNode<T> *ptr = NULL;

		  ptr = search(elem);
		  if(ptr == NULL)
		  {
					 cout << "Error: Cannot delete. Node not in list.\n";
					 return;
		  }
		  remove(ptr);
		  cout << "Element deleted from list.\n";
}

