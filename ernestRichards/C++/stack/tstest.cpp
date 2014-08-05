#include <stdio.h>
#include "tstack.h"

using namespace std;

/*

#ifndef TYPE
#define TYPE char
#endif

#ifndef SVAL
#define SVAL '~'
#endif

*/

#ifndef TYPE
#define TYPE int
#endif

#ifndef SVAL
#define SVAL 0
#endif

int menu();
void loop(Stack<TYPE> & cList1);

int main()
{
		  Stack<TYPE> cList1;

		  loop(cList1);

		  return 0;
}

void loop(Stack<TYPE> & cList1)
{
		  int selection;
		  LinkedList<ListNode<TYPE> *> * result_list = NULL;
		  ListNode<TYPE> *result = NULL; // Result of last search
		  TYPE c;
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
										  cList1.push(c); // Insert after last search (or head if no search)
										  printf("Element inserted into list.\n");
										  break;

								case 3:
										  if(cList1.empty())
										  {
													 printf("The list is empty. Add an item before dequeuing one.\n");
													 break;
										  }
										  cout << "Popd " << *(cList1.pop()) << " from the queue\n";
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

		  printf("                 Welcome to the Stack Menu\n");
		  printf("  ========================================================\n");
		  printf("  1.  Search for first occurance of an element in the list\n");
		  printf("  2.  Push an element\n");
		  printf("  3.  Pop an element\n");
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
