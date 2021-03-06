#include <iostream>
#include <stdio.h>
#include <sstream>
#include "listnode.h"
#include "tlinkedlist.h"

using namespace std;

#ifndef TYPE
#define TYPE char
#endif

#ifndef SVAL
#define SVAL '~'
#endif

int menu();
void loop(LinkedList<TYPE> & cList1);

int main()
{
		  LinkedList<TYPE> cList1;
		  cList1.setDoublyLinked(false);
		  cList1.setDummyHead(false);

		  loop(cList1);

		  /* it works below
		  LinkedList<TYPE> cList2;
		  cList2.setDoublyLinked(true);
		  cList2.setDummyHead(false);

		  loop(cList2);
		  */

		  return 0;
}

void loop(LinkedList<TYPE> & cList1)
{
		  int selection;
		  LinkedList<ListNode<TYPE> *> * result_list;
		  ListNode<TYPE> *result = NULL; // Result of last search
		  int error;
		  TYPE c, a;
		  char * str = NULL;

		  do
		  {
//					 result_list.erase();
					 selection = menu();
					 printf("\n");
					 switch(selection)
					 {
								case 0:
										  printf("Good-bye!\n");
										  break;

								case 1:
										  if(cList1.empty())
										  {
													 printf("The list is empty. Add an item before searching.\n");
													 break;
										  }
										  c = cList1.getValue();
										  result = cList1.findFirst(c);
										  if(result == NULL)
										  {
													 printf("Value not found in list.\n");
										  }
										  else
										  {
													 printf("Value found in list at address %p.\n", result);
										  }
										  break;

								case 2:
										  c = cList1.getValue();
										  if (!cList1.empty())
										  {
													 do
													 {
																error = 0;
																cout << cList1 << endl;
																printf("After which element in the list (shown above) would you like to insert the new element? (~ for head insertion): ");
																cin >> a;
																while(cin.fail())
																{
																		  cin.clear();
																		  cin.ignore(20, '\n');
																		  printf("Error: Must enter a valid value.\n");
																		  printf("Enter a value: ");
																		  cin >> a;
																}
																if (a == SVAL)
																{
																		  result = NULL;
																}
																else
																{
																		  result = cList1.findFirst(a);
																}
																if (result || a == SVAL)
																{
																		  cList1.insert(c, result); // Insert after last search (or head if no search)
																}
																else if (result == NULL && a != SVAL)
																{
																		  printf("The element wasn't found in the list.\n");
																		  error++;
																}
													 }
													 while (error != 0);
										  }
										  else
										  {
													 cList1.insert(c, result); // Insert after last search (or head if no search)
										  }
										  result = NULL;  // Reset result
										  printf("Element inserted into list.\n");
										  break;

								case 3:
										  if(cList1.empty())
										  {
													 printf("The list is empty. Add an item before searching.\n");
													 break;
										  }
										  c = cList1.getValue();
										  cList1.remove(c);
										  break;

								case 4:
										  if(cList1.empty())
										  {
													 printf("The list is empty. Add an item before searching.\n");
										  }
										  else
										  {
													 cout << "The list contents are:\n" << cList1 << endl;
										  }
										  break;

								case 5:
										  str = cList1.toString();
										  if (str)
										  {
													 printf("%s\n", str);
										  }
										  else
										  {
													 printf("The list is empty\n");
										  }
										  break;

								case 6:
										  if(cList1.empty())
										  {
													 printf("The list is empty. Add an item before searching.\n");
													 break;
										  }
										  c = cList1.getValue();
										  result_list = cList1.findAll(c);
										  if(!result_list || result_list->empty())
										  {
													 printf("Value not found in list.\n");
										  }
										  else
										  {
													 cout << *result_list << endl;
										  }
										  break;

								default:
										  printf("Error: Invalid menu selection.\n");
					 }
					 printf("\n");
		  }
		  while(selection != 0);
}

int menu()
{
		  int sel;

		  printf("      Welcome to the Linked List Menu\n");
		  printf("  =======================================\n");
		  printf("  1.  Search for first occurance of an element in the list\n");
		  printf("  2.  Add an element to the list\n");
		  printf("  3.  Delete an element from the list\n");
		  printf("  4.  Print the list\n");
		  printf("  5.  Print the list with toString\n");
		  printf("  6.  Search for all occurances of an element in the list\n");
		  printf("\n");
		  printf("  0.  Exit\n");
		  printf("  =======================================\n");
		  printf("  Enter selection: ");

		  cin >> sel;
		  while(cin.fail())
		  {
					 cin.clear();
					 cin.ignore(20, '\n');
					 printf("  Error: Selection must be an integer.\n");
					 printf("  Enter Selection: ");
					 cin >> sel;
		  }

		  return sel;
}
