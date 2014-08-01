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

int main()
{
		  int selection;
		  LinkedList<TYPE> cList;
		  ListNode<TYPE> *result = NULL; // Result of last search
		  int error;
		  TYPE c, a;
		  char * str = NULL;

		  do
		  {
					 selection = menu();
					 printf("\n");
					 switch(selection)
					 {
								case 0:
										  printf("Good-bye!\n");
										  break;

								case 1:
										  if(cList.empty())
										  {
													 printf("The list is empty. Add an item before searching.\n");
													 break;
										  }
										  c = cList.getValue();
										  result = cList.search(c);
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
										  c = cList.getValue();
										  if (!cList.empty())
										  {
													 do
													 {
																error = 0;
																cout << cList << endl;
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
																		  result = cList.search(a);
																}
																if (result || a == SVAL)
																{
																		  cList.insert(c, result); // Insert after last search (or head if no search)
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
													 cList.insert(c, result); // Insert after last search (or head if no search)
										  }
										  result = NULL;  // Reset result
										  printf("Element inserted into list.\n");
										  break;

								case 3:
										  if(cList.empty())
										  {
													 printf("The list is empty. Add an item before searching.\n");
													 break;
										  }
										  c = cList.getValue();
										  cList.remove(c);
										  break;

								case 4:
										  if(cList.empty())
										  {
													 printf("The list is empty. Add an item before searching.\n");
										  }
										  else
										  {
													 cout << "The list contents are:\n" << cList << endl;
										  }
										  break;

								case 5:
										  str = cList.toString();
										  if (str)
										  {
													 printf("%s\n", str);
										  }
										  else
										  {
													 printf("The list is empty\n");
										  }
										  break;

								default:
										  printf("Error: Invalid menu selection.\n");
					 }
					 printf("\n");
		  }
		  while(selection != 0);

		  return 0;
}

int menu()
{
		  int sel;

		  printf("      Welcome to the Linked List Menu\n");
		  printf("  =======================================\n");
		  printf("  1.  Search for an element in the list\n");
		  printf("  2.  Add an element to the list\n");
		  printf("  3.  Delete an element from the list\n");
		  printf("  4.  Print the list\n");
		  printf("  5.  Print the list with toString\n");
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
