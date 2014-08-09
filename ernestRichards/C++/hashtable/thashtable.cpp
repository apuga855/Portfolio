#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>

#include "init_arrays.h"

using namespace std;

#ifndef ELEMTYPE
#define ELEMTYPE int
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

#ifndef R
#define R 509
#endif

template <class T>
struct HashTable
{
		  T * table;
		  int count;
		  int CAPACITY;
};

void initTable(HashTable<ELEMTYPE> *);
bool full(HashTable<ELEMTYPE> *);
bool empty(HashTable<ELEMTYPE> *);
int hash1(HashTable<ELEMTYPE> *, ELEMTYPE);
int hash2(ELEMTYPE);
bool search (HashTable<ELEMTYPE> *, ELEMTYPE);
bool insert (HashTable<ELEMTYPE> *, ELEMTYPE);
bool remove (HashTable<ELEMTYPE> *, ELEMTYPE);
void printMenu();

int main ()
{
		  int choice, value;
		  HashTable<ELEMTYPE> table;
		  initTable (&table);
		  do
		  {
					 choice = -1;
					 printMenu();
					 cin >> choice;
					 if (cin.fail())
					 {
								cin.clear();
								cin.ignore(50, '\n');
								printf("\a\aInvaild Menu Option!\n");
								continue;
					 }
					 switch (choice)
					 {
								case 0:
										  cout << "Exiting...\n";
										  break;

								case 1:
										  // insert
										  if (full(&table))
										  {
													 cout << "Empty hash table\n";
													 break;
										  }
										  cout << "Enter the integer you want to insert into the table: ";
										  cin >> value;
										  if (cin.fail())
										  {
													 cin.clear();
													 cin.ignore(50, '\n');
													 printf("\a\aInvalid Input! You can't insert crappy input!\n");
													 break;
										  }
										  if (search(&table, value))
										  {
													 cout << "\a\aDuplicate value detected!\n";
													 break;
										  }
										  if (!insert(&table, value))
													 cout << "Unable to insert value!\n";
										  else
													 cout << "Success!\n";
										  break;

								case 2:
										  // delete
										  if (empty(&table))
										  {
													 cout << "Empty hash table\n";
													 break;
										  }
										  cout << "Enter the integer you want to delete: ";
										  cin >> value;
										  if (cin.fail())
										  {
													 cin.clear();
													 cin.ignore(50, '\n');
													 printf("\a\aInvalid Input! You can't search for crappy input!\n");
													 break;
										  }
										  if (!search(&table, value))
										  {
													 cout << value << " is not in the table\n";
													 break;
										  }
										  if (!remove(&table, value))
										  {
													 cout << "\a\aUnable to delete!\n";
										  }
										  else
													 cout << "It's a gonner\n";
										  break;

								case 3:
										  // search
										  if (empty(&table))
										  {
													 cout << "Empty hash table\n";
													 break;
										  }
										  cout << "Enter the integer you want to try to find: ";
										  cin >> value;
										  if (cin.fail())
										  {
													 cin.clear();
													 cin.ignore(50, '\n');
													 printf("\a\aInvalid Input! You can't search for crappy input!\n");
													 break;
										  }
										  if (!search(&table, value))
													 cout << value << " is not in the table\n";
										  else
													 cout << value << " is in there! Somewhere...\n";
										  break;

								case 4:
										  // print hashes for an integer
										  cout << "Enter the Integer you wish to hash: ";
										  cin >> value;
										  if (cin.fail())
										  {
													 cin.clear();
													 cin.ignore(50, '\n');
													 printf("\a\aInvalid Input! You can't hash crappy input!\n");
													 break;
										  }
										  cout << "Hash1 for " << value << " returns " << hash1(&table,value) << endl;
										  cout << "Hash2 for " << value << " returns " << hash2(value) << endl;
										  break;

								default:
										  cin.clear();
										  cin.ignore(50, '\n');
										  printf("Invalid Menu Option!\n");
										  break;
					 }
		  }
		  while (choice != 0);

		  return 0;
}

bool insert (HashTable<ELEMTYPE> * ht, ELEMTYPE value)
{
		  int hash1val = hash1(ht, value);
		  if (ht->table[hash1val] == EMPTY_VALUE || ht->table[hash1val] == DELETED_VALUE)
		  {
					 ht->table[hash1val] = value;
					 if (ht->table[hash1val] == value)
					 {
								ht->count++;
								return true;
					 }
					 return false;
		  }
		  int hash2val = hash2(hash1val);
		  while (ht->table[hash2val] != EMPTY_VALUE && ht->table[hash2val] != DELETED_VALUE)
					 hash2val = hash2(hash2val);
		  ht->table[hash2val] = value;
		  if (ht->table[hash2val] == value)
		  {
					 ht->count++;
					 return true;
		  }
		  return false;
}

bool remove (HashTable<ELEMTYPE> * ht, ELEMTYPE value)
{
		  int hash1val = hash1(ht, value);
		  if (ht->table[hash1val] == value)
		  {
					 ht->table[hash1val] = DELETED_VALUE;
					 if (ht->table[hash1val] == DELETED_VALUE)
					 {
								ht->count--;
								return true;
					 }
					 return false;
		  }
		  int hash2val = hash2(hash1val);
		  while (ht->table[hash2val] != value)
					 hash2val = hash2(hash2val);
		  ht->table[hash2val] = DELETED_VALUE;
		  if (ht->table[hash2val] == DELETED_VALUE)
		  {
					 ht->count--;
					 return true;
		  }
		  return false;
}

bool search (HashTable<ELEMTYPE> * ht, ELEMTYPE value)
{
		  int hash1val = hash1(ht, value);
		  if (ht->table[hash1val] == EMPTY_VALUE)
					 return false;
		  if (ht->table[hash1val] == value)
					 return true;
		  int hash2val = hash2(hash1val);
		  int i = 1;
		  while (ht->table[hash2val] != EMPTY_VALUE && ht->table[hash2val] != value && i < ht->count)
		  {
					 hash2val = hash2(hash2val);
					 i++;
		  }
		  if (ht->table[hash2val] == value)
					 return true;
		  return false;
}

int hash1 (HashTable<ELEMTYPE> * ht, ELEMTYPE value)
{
		  return (value % (ht->CAPACITY));
}

int hash2 (ELEMTYPE value)
{
		  return (R - (value % R));
}

void initTable (HashTable<ELEMTYPE> * ht)
{
		  ht->count = 0;
		  ht->CAPACITY = DEFAULT_CAP;
		  try
		  {
					 ht->table = new ELEMTYPE [ht->CAPACITY];
		  }
		  catch (bad_alloc)
		  {
					 printf("\a\aUnable to allocate Memory!\n");
					 delete ht;
					 ht = NULL;
					 exit(1);
		  }
		  initArraySentinel(ht->table, ht->CAPACITY, EMPTY_VALUE);
		  if (ht && ht->table && ht->CAPACITY == DEFAULT_CAP && ht->table[0] == EMPTY_VALUE && ht->count == 0)
					 return;
		  exit(1);
}

bool empty (HashTable<ELEMTYPE> * ht)
{
		  return (ht->count == 0);
}

bool full (HashTable<ELEMTYPE> * ht)
{
		  return (ht->count == ht->CAPACITY);
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
