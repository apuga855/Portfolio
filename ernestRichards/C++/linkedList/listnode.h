#pragma once
#include <iostream>
#include <ostream>
#include <sstream>

/* TO DO
 * set up use of previous and head
 */

using namespace std;

template <class T>
class ListNode
{
		  private:
					 T element;                           // data being stored
					 ListNode * next;                        // pointer to next element

					 ListNode * previous;
					 bool head;

		  public:
					 ListNode()
					 {
								next = previous = NULL;
								head = false;
					 }
					 ListNode(const T elem, ListNode<T> * p = NULL, ListNode<T> * n = NULL, const bool & h = false)
					 {
								element = elem;
								next = n;
								previous = p;
								head = h;
					 }
					 ~ListNode()
					 {
								next = previous = NULL;
								head = false;
					 }

					 void setData(T elem) {element = elem;}  // set the element
					 T getData() const {return (element);}           // retrieve the element
					 void setNext(ListNode<T> *n) {next = n;}      // set the next pointer
					 void setPrevious(ListNode<T> *n) {previous = n;}      // set the previous pointer
					 ListNode<T> *getNext() const {return (next);}        // retrieve the next pointer
					 ListNode<T> *getPrevious() const {return (previous);}        // retrieve the next pointer
					 bool isHead const {return (head);}
					 void setHead (const bool & b) {head = b;}

					 // Test for equality. Return true if right's element equals this element
					 bool operator ==(const ListNode<T> &right) {return (element == right.element);}
					 bool operator <=(const ListNode<T> &right) {return (element <= right.element);}
					 bool operator >=(const ListNode<T> &right) {return (element >= right.element);}
					 bool operator >(const ListNode<T> &right) {return (element > right.element);}
					 bool operator <(const ListNode<T> &right) {return (element < right.element);}

					 // Output the element
					 friend ostream & operator << (ostream &o, const ListNode<T> &right)
					 {
								o << right.element;
								return (o);
					 }

					 char * toString(void)
					 {
								ostringstream oss;
								oss << (*this).element;
								return ((char *)(oss.str().c_str()));
					 }
};