/* Alfonso Puga & Ernest Richards */

/* TO DO
*/

#pragma once
#include "tlinkedlist.h"

using namespace std;

template <class T>
class Stack : public LinkedList<T>
{
		  private:

		  public:
					 Stack ();
					 Stack (const Stack &);
					 ~Stack();

					 void push(const T &);
					 void push(void);
					 T * pop(void);
};

template <class T>
void Stack<T>::push(void)
{
		  this->insert(this->getValue(), this->getLast());
}

template <class T>
void Stack<T>::push(const T & val)
{
		  this->insert(val, this->getLast());
}

template <class T>
T * Stack<T>::pop(void)
{
		  if (this->empty())
		  {
					 return (NULL);
		  }
		  T * tmp = NULL;
		  try
		  {
					 tmp = new T;
		  }
		  catch (bad_alloc)
		  {
					 cout << "Insufficient Memory\n";
					 tmp = NULL;
		  }
		  catch (...)
		  {
					 cout << "Unknown Error\n";
					 tmp = NULL;
		  }
		  if (!tmp)
		  {
					 cout << "Allocation failed\n";
					 return (NULL);
		  }
		  *tmp = this->getLast()->getData();
		  this->remove(this->getLast());
		  return (tmp);
}

template <class T>
Stack<T>::Stack()
{
}

template <class T>
Stack<T>::Stack(const Stack & rhs) : LinkedList<T> (rhs)
{
}

template <class T>
Stack<T>::~Stack()
{
}
