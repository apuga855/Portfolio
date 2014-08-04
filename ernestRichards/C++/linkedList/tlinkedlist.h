/* Alfonso Puga & Ernest Richards */

/* TO DO
 * set up use of previous and head in ListNode
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
		bool input_function;
		ListNode<T> *findPrevious(const ListNode<T> *);

	public:
		LinkedList(const bool & dl = false, const bool & dh = false, const bool & i = false);                          // default constructor
		LinkedList(const LinkedList &);   // copy constructor
		~LinkedList();                         // destructor, deallocate list

		T getValue(const char * prompt = NULL);
		bool empty();                          // is there a list?
		ListNode<T> *search(const T &);            // find elem in list
		void insert(const T &, const ListNode<T> *); // insert element after prev
		void remove(ListNode<T> *);            // delete a specific node
		void remove(T);                 // find elem and delete if found

		bool isDoublyLinked(void) const {return (doubly_linked);}
		bool hasDummyHead(void) const {return (dummy_head);}
		bool hasInputFunction(void) const {return (input_function);}
		void setDoublyLinked (const bool & b = false) {doubly_linked = b;}
		void setDummyHead (const bool & b = false) {dummy_head = b;}
		void setDummyHead (const T & d) {head = d;}
		void setInputFunction (const bool & b = false) {input_function = b;}

		/* returns a character pointer, but uses oss.str.c_str */
		char * toString (void);

		void operator = (const LinkedList &);
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
ListNode<T> * LinkedList<T>::findPrevious(const ListNode<T> *ptr)
{
	ListNode<T> *node = NULL;

	if (isDoublyLinked())
	{
		node = ptr->getPrevious();
		if (node == head)
		{
			return (NULL); // should this return heads previous?
		}
		return (node);
	}

	node = head;  // current node we're searching, start at head

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

	return (NULL);  // not found
}

template <class T>
LinkedList<T>::LinkedList(const bool & dl, const bool & dh, const bool & i)
{
	head = NULL;
	setDoublyLinked(dl);
	setDummyHead(dh);
	setInputFunction(i);
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
		delete (tmp);
	}
}

/* good copy constructor
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
cout << "Memory error\n";
new_node = NULL;
}
catch(...)
{
cout << "Unknown error\n";
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
cout << "Memory error\n";
new_node = NULL;
}
catch(...)
{
cout << "Unknown error\n";
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
*/

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
		cout << "Memory error\n";
		new_node = NULL;
	}
	catch(...)
	{
		cout << "Unknown error\n";
		new_node = NULL;
	}
	if(new_node == NULL)
	{
		cout << "Allocation failed.\n";
		head = NULL;
		return;
	}
	*new_ll = right;
}

template <class T>
void LinkedList<T>::erase (LinkedList<T> & ll)
{
	if (isEmpty())
	{
		return;
	}
	if (isDoublyLinked())
	{
		ListNode<T> * forward, * reverse, * tmp_f, * tmp_r;
		if (hasDummyHead())
		{
			forward = head->getNext();
			reverse = head->getPrevious();
		}
		else
		{
			forward = head;
			reverse = head->getPrevious();
		}
		while (forward || reverse)
		{
			if (forward)
			{
				tmp_f = forward;
				forward = forward->getNext();
				delete (tmp_f);
			}
			if (reverse)
			{
				tmp_r = reverse;
				reverse = reverse->getPrevious();
				delete (tmp_r);
			}
		}
		return;
	}
	else
	{
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

	doubly_linked = right.doubly_linked;
	dummy_head = right.dummy_head;

	// Delete the previous list
	/*
	   node = head;
	   while(node != NULL)
	   {
	   tmp = node;  // Delete the current node
	   node = node->getNext();  // Increment node pointer
	   delete (tmp);
	   }
	   */
	erase(this);

	node = right.head;
	if(node == NULL)  // empty source list
	{
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

	/*
	 * no need to account for dummy head node, singlly/doubly linked lists, just copy everything, including dummy head (if one exists)
	 */

	doubly_linked = right.isDoublyLinked();
	dummy_head = right.hasDummyHead();

	new_node->setData(node->getData());  // copy data
	new_node->setPrevious(node->getPrevious());
	new_node->setNext(node->getNext());
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
		new_node->setPrevious(node->getPrevious());
		new_node->setNext(node->getNext());
		prev = new_node;
		node = node->getNext();
	}
	if (dummy_head)
	{
		prev->setNext(head);  // mark end of list
	}
	else
	{
		prev->setNext(NULL);  // mark end of list
	}
}

template <class T>
bool LinkedList<T>::empty()
{
	if (!dummy_head)
	{
		return (head == NULL);
	}
	return ((head->getNext()) == NULL);
}

template <class T>
T LinkedList<T>::getValue(const char * prompt)
{
	T c;
	if (hasInputFunction())
	{
		c = head->getValue();
	}
	else
	{
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
	}
	return (c);
}

/* good search function
   template <class T>
   ListNode<T> * LinkedList<T>::search(const T & elem)
   {
   ListNode<T> * node = head;

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
   */

template <class T>
ListNode<T> * LinkedList<T>::search(const T & elem)
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
				if( *forward_node == elem ) // This will use the == operator in ListNode
				{
					return (forward_node);
				}
			}
			if (reverse_node != head)
			{
				if( *reverse_node == elem ) // This will use the == operator in ListNode
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
				if( *forward_node == elem ) // This will use the == operator in ListNode
				{
					return (forward_node);
				}
			}
			forward_node = forward_node->getNext();
		}
	}
	return (NULL);  // not found
}

template <class T>
void LinkedList<T>::insert(const T & elem, const ListNode<T> *prev)
{
	ListNode<T> * new_node;
	if (prev)
	{
		if (!search(prev -> getData()))
		{
			cout << "\a\aAn Error Occured!!\nPrevious wasn't found in the list\n";
			return;
		}
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
	if (!new_node)
	{
		cout << "\a\aAn Error Occured\nNode creation failed\n";
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
		if (dummy_head)
		{
			cout << "\a\aUnable to remove dummy head node\n";
			return;
		}
		if (doubly_linked)
		{
			head->getNext()->setPrevious(head->getPrevious());
			head->getPrevious()->setNext(head->getNext());
		}
		head = head->getNext();  // increment head to 2nd element
		delete (ptr);
	}
	else
	{
		prev = findPrevious(ptr);
		if(prev == NULL)
		{
			cout << "Error: Cannot delete. Node not in list.\n";
			return;
		}
		prev->setNext( ptr->getNext() );
		if (doubly_linked)
		{
			ptr->getNext()->setPrevious(prev);
		}
		delete (ptr);
	}
	cout << "Removal Succeded\n";
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
}

