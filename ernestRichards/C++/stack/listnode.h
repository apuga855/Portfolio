#pragma once
#include <ostream>
#include <sstream>

/* TO DO
 */

using namespace std;

template <class T>
class ListNode
{
		  private:
					 T element;                           
					 ListNode * next;                        
					 ListNode * previous;
					 bool head;
					 bool input_function;

		  public:
					 ListNode()
					 {
								next = previous = NULL;
								head = false;
								input_function = false;
					 }
					 /* next has to come before previous because next will always be included and previous may not be */
					 ListNode(const T elem, ListNode<T> * n = NULL, ListNode<T> * p = NULL, const bool & h = false, const bool & i = false)
					 {
								element = elem;
								next = n;
								previous = p;
								head = h;
								input_function = i;
					 }
					 ListNode(const ListNode & rhs)
					 {
								/* requires that the raw data type has an assignment operator */
								element = rhs.element;
								next = rhs.next;
								previous = rhs.previous;
								input_function = rhs.input_function;
								head = rhs.head;
					 }
					 ~ListNode()
					 {
								next = previous = NULL;
								head = false;
								input_function = false;
					 }

					 void setInputFunction (const bool & b = false) {input_function = b;}
					 bool hasInputFunction(void) const {return (input_function);}
					 void setData(T elem) {element = elem;}  
					 const T getData() const {return (element);}           
					 T getData() {return (element);}           
					 void setNext(ListNode<T> *n) {next = n;}      
					 void setPrevious(ListNode<T> *n) {previous = n;}      
					 ListNode<T> *getNext() const {return (next);}        
					 ListNode<T> *getPrevious() const {return (previous);}        
					 bool isHead (void) const {return (head);}
					 void setHead (const bool & b) {head = b;}

					 
					 bool operator ==(const ListNode<T> &right) {return (element == right.element);}
					 bool operator <=(const ListNode<T> &right) {return (element <= right.element);}
					 bool operator >=(const ListNode<T> &right) {return (element >= right.element);}
					 bool operator >(const ListNode<T> &right) {return (element > right.element);}
					 bool operator <(const ListNode<T> &right) {return (element < right.element);}
					 void operator = (const ListNode<T> &right)
					 {
								if (this == &right)
								{
										  return;
								}
								element = right.element;
								next = right.next;
								previous = right.previous;
								head = previous.head;
					 }
					 bool operator ! () const {return (this == NULL);}

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
