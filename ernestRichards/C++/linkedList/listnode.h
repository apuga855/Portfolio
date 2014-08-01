#pragma once
#include <iostream>
#include <ostream>
#include <sstream>

using namespace std;

template <class T>
class ListNode
{
		  private:
					 T element;                           // data being stored
					 ListNode * next;                        // pointer to next element

		  public:
					 ListNode()
					 {
								next = NULL;
					 }
					 ListNode(T elem)
					 {				// creates node to store elem
								element = elem;
								next = NULL;
					 }
					 ListNode(T elem, ListNode<T> * n)
					 {			// specific data and next
								element = elem;
								next = n;
					 }
					 ~ListNode()
					 {
								next = NULL;
					 }

					 void setData(T elem) {element = elem;}  // set the element
					 T getData() const {return element;}           // retrieve the element
					 void setNext(ListNode<T> *n) {next = n;}      // set the next pointer
					 ListNode<T> *getNext() const {return next;}        // retrieve the next pointer

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
								return o;
					 }

					 char * toString(void)
					 {
								ostringstream oss;
								oss << (*this).element;
								return ((char *)(oss.str().c_str()));
					 }
};
