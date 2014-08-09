/* er and ap
 *
 * TO DO:
 * resize function, next prime number
 * useage of DEFAULT_R and r_val, change with resize, find next prime
 *
 * maybe add init function with params for cap and r_val
 * copy constructor
 *
 * toString function?
 * useage of -> operator?
 *
 * first hash function depends on int, make some basics for basic data types? special for adts relying on a toString function?
 *
 * rewrite initArraySentinal for void *?
 */

#pragma once
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>

#include "init_arrays.h"

using namespace std;

#ifndef TYPE
#define TYPE int
#endif

#ifndef EMPTY_VALUE
#define EMPTY_VALUE -99
#endif

#ifndef DELETED_VALUE
#define DELETED_VALUE -88
#endif

#ifndef DEFAULT_CAP
#define DEFAULT_CAP 1013
#endif

#ifndef DEFAULT_R
#define DEFAULT_R 1123
#endif

void printMenu(void);

template <class T>
class Hashtable
{
		  private:
					 T * table;
					 int count;
					 int capacity;
					 int r_val;

		  public:
					 /* con/destructors */

					 Hashtable();
					 Hashtable(const Hashtable<T> &);
					 ~Hashtable();

					 /* accessors */

					 T getValue(const int &) const;
					 int getCount (void) const {return (count);}
					 int getCapacity (void) const {return (capacity);}
					 bool full(void) const;
					 bool empty(void) const;
					 bool search (const T &) const;

					 /* mutators */

					 void initTable(void);
					 bool insert (const T &);
					 bool remove (const T &);

					 /* hash functions */

					 int hash1(const T &) const;
					 int hash2(const int &) const;
};

/* HERE */
template <>
int Hashtable<int>::hash1 (const int & value) const
{
		  return ((int)value % (getCapacity()));
}

template <>
int Hashtable<double>::hash1 (const double & value) const
{
		  return ((int)value % (getCapacity()));
}

template <>
int Hashtable<char>::hash1 (const char & value) const
{
		  return ((int)value % (getCapacity()));
}

/* this function assumes T has a getHash() function to return some integer, representative of the data it holds, to be put into the hashtable */
template <class T>
int Hashtable<T>::hash1 (const T & value) const
{
		  return ((value.getHash()) % (getCapacity()));
}

template <class T>
Hashtable<T>::Hashtable()
{
		  initTable();
}

template <class T>
Hashtable<T>::Hashtable(const Hashtable<T> & r)
{
		  initTable();
		  int j = getCapacity();
		  for (int i = 0; i < j; i++)
		  {
					 table[i] = r.getValue(i);
		  }
}

template <class T>
Hashtable<T>::~Hashtable()
{
		  for (int i = 0; i < capacity; i++)
		  {
					 table[i] = EMPTY_VALUE;
		  }
		  count = capacity = 0;
		  delete (table);
		  table = NULL;
}

template <class T>
bool Hashtable<T>::insert (const T & value)
{
		  int hash1val = hash1(value);
		  if (getValue(hash1val) == EMPTY_VALUE || getValue(hash1val) == DELETED_VALUE)
		  {
					 this->table[hash1val] = value;
					 if (getValue(hash1val) == value)
					 {
								this->count++;
								return (true);
					 }
					 return (false);
		  }
		  int hash2val = hash2(hash1val);
		  while (getValue(hash2val) != EMPTY_VALUE && getValue(hash2val) != DELETED_VALUE)
		  {
					 hash2val = hash2(hash2val);
		  }
		  this->table[hash2val] = value;
		  if (getValue(hash2val) == value)
		  {
					 this->count++;
					 return (true);
		  }
		  return (false);
}

template <class T>
bool Hashtable<T>::remove (const T & value)
{
		  int hash1val = hash1(value);
		  if (getValue(hash1val) == value)
		  {
					 this->table[hash1val] = DELETED_VALUE;
					 if (getValue(hash1val) == DELETED_VALUE)
					 {
								this->count--;
								return (true);
					 }
					 return (false);
		  }
		  int hash2val = hash2(hash1val);
		  while (getValue(hash2val) != value)
		  {
					 hash2val = hash2(hash2val);
		  }
		  if (getValue(hash2val) == value)
		  {
					 this->table[hash2val] = DELETED_VALUE;
					 if (getValue(hash2val) == DELETED_VALUE)
					 {
								this->count--;
								return (true);
					 }
		  }
		  return (false);
}

template <class T>
bool Hashtable<T>::search (const T & value) const
{
		  int hash1val = hash1(value);
		  if (getValue(hash1val) == EMPTY_VALUE)
		  {
					 return (false);
		  }
		  if (getValue(hash1val) == value)
		  {
					 return (true);
		  }
		  int hash2val = hash2(hash1val);
		  int i = 1;
		  while (getValue(hash2val) != EMPTY_VALUE && getValue(hash2val) != value && i < getCount())
		  {
					 hash2val = hash2(hash2val);
					 i++;
		  }
		  if (getValue(hash2val) == value)
		  {
					 return (true);
		  }
		  return (false);
}

template <class T>
int Hashtable<T>::hash2 (const int & v) const
{
		  return (r_val - (v % r_val));
}

template <class T>
void Hashtable<T>::initTable (void)
{
		  this->setCount(0);
		  this->setCapacity(DEFAULT_CAP);
		  try
		  {
					 table = new T [this->getCapacity()];
		  }
		  catch (bad_alloc)
		  {
					 cout << "Memory error\n";
					 table = NULL;
					 exit(1);
		  }
		  catch (...)
		  {
					 cout << "Unknown error\n";
					 table = NULL;
					 exit(2);
		  }
		  initArraySentinel(table, getCapacity(), EMPTY_VALUE);
		  if (this->table && this->getCapacity() == DEFAULT_CAP && this->getValue(0) == EMPTY_VALUE && this->empty())
		  {
					 return;
		  }
		  cout << "Initialization error\n";
		  exit(1);
}

template <class T>
T Hashtable<T>::getValue(const int & loc) const
{
		  if (!table || empty())
		  {
					 return (EMPTY_VALUE);
		  }
		  return (table[loc]);
}

template <class T>
bool Hashtable<T>::empty (void) const
{
		  return (this->getCount() == 0);
}

template <class T>
bool Hashtable<T>::full (void) const
{
		  return (this->getCount() == this->getCapacity());
}

void printMenu()
{
		  cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n"
					 << "<<<<<<<<<<   Hash Table Menu   >>>>>>>>>>\n"
					 << "-----------------------------------------\n\n"
					 << "1. Insert an integer into a hash table\n"
					 << "2. Delete an integer from a hash table\n"
					 << "3. Search for an integer in a hash table\n"
					 << "4. Display hash values for an integer\n\n"
					 << "0. Gtfo\n\n"
					 << "=========================================\n\n"
					 << "> ";
}
