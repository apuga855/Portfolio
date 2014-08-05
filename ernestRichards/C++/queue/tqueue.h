/* Alfonso Puga & Ernest Richards */

/* TO DO
*/

#pragma once
#include "tlinkedlist.h"

using namespace std;

template <class T>
class Queue : public LinkedList<T>
{
		  private:

		  public:
					 Queue ();
					 Queue (const Queue &);
					 ~Queue();

					 void enqueue(const T &);
					 void enqueue(void);
					 T * dequeue(void);
};

template <class T>
void Queue<T>::enqueue(void)
{
		  this->insert(this->getValue());
}

template <class T>
void Queue<T>::enqueue(const T & val)
{
		  this->insert(val, NULL);
}

template <class T>
T * Queue<T>::dequeue(void)
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
		  *tmp = this->getHead()->getData();
		  this->remove(this->getHead());
		  return (tmp);
}

template <class T>
Queue<T>::Queue()
{
}

template <class T>
Queue<T>::Queue(const Queue & rhs) : LinkedList<T> (rhs)
{
}

template <class T>
Queue<T>::~Queue()
{
}
