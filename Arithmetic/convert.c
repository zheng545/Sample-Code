#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "list.h"
#include "convert.h"


const int Operations[] = {'+', '-', '*', '(', ')'};

// return -1 if the word is not an operator
// return 0 if the word contains '+'
//        1                      '-'
//        2                      '*'
//        3                      '('
//        4                      ')'
int isOperator(char * word)
{
  int ind;
  int numop = sizeof(Operations) / sizeof(int);
  for (ind = 0; ind < numop; ind ++)
    {
    char *loc = strchr(word, Operations[ind]);
    if (loc != NULL && !isdigit(loc[1]))
	{
	  return ind;
	}
    }
  return -1;
}


#ifdef TEST_CONVERT
bool convert(List * arithlist)
{
  if (arithlist == NULL)
  {
    return true;
  }
  if ((arithlist -> head) == NULL)
  {
    return true;
  }
  ListNode * tmp = arithlist -> head;
  List * Output = malloc(sizeof(List));
  List * Stack =  malloc(sizeof(List));
  Output -> head = NULL;
  Output -> tail = NULL;
  Stack -> head = NULL;
  Stack -> tail = NULL;
  //ListNode * StackTail = Stack -> tail;
  int operator;
  while (tmp!= NULL)
  //&& (arithlist -> head != arithlist -> tail))
  {
    operator = isOperator(tmp -> word);
    //detect operands
    switch(operator) 
      {
        case -1 : //operands
          addNode(Output, tmp -> word);
          tmp = tmp -> next;
          break;
	
        case 0 : //"+/-" [A * B + C] - 
          if ((Stack -> tail -> word) != NULL && isOperator(Stack -> tail -> word) == 2)
          {
            addNode(Output, Stack -> tail -> word); //put "*" into output
            deleteNode(Stack, Stack -> tail);
            if ((Stack -> tail -> word) != NULL && isOperator(Stack -> tail -> word) < 2)
            {
              addNode(Output, Stack -> tail -> word);
              strcpy(Stack -> tail -> word,tmp -> word);
            }
            else
            {
              addNode(Stack,tmp -> word);
            }
          }
          else{addNode(Stack, tmp -> word);}
          tmp = tmp -> next;
          break;

        case 1 :
          if ((Stack -> tail -> word) != NULL && isOperator(Stack -> tail -> word) == 2)
          {
            addNode(Output, Stack -> tail -> word); //put "*" into output
            deleteNode(Stack, Stack -> tail);
            if ((Stack -> tail -> word) != NULL && isOperator(Stack -> tail -> word) < 2)
            {
              addNode(Output, Stack -> tail -> word);
              strcpy(Stack -> tail -> word,tmp -> word);
            }
            else
            {
              addNode(Stack,tmp -> word);
            }
          }
          else{addNode(Stack, tmp -> word);}
          tmp = tmp -> next;
          break;

        case 2 : //"*"
          addNode(Stack, tmp -> word);
          tmp = tmp -> next;
          break;

        case 3 : //"("
          addNode(Stack, tmp -> word);
          tmp = tmp -> next;
          break;

        case 4 :
          //tmp = )
          while (isOperator(Stack -> tail -> word) != 3)
          {
            addNode(Output, Stack -> tail -> word); //move sign inside bracket to Output
            //Stack -> tail = Stack -> tail -> prev;
            deleteNode(Stack, Stack -> tail); //delete sign
          }
          //if (Stack -> tail -> prev == NULL)
          //{
          //  Stack -> tail -> prev = NULL;
          //  Stack -> head -> next = NULL;
          //}
          //else{//
          deleteNode(Stack, Stack -> tail); //delete open bracket
          tmp = tmp -> next;
          break;
      }
  }
  //put all Stack stuff into Output
  while (Stack -> tail != NULL)
  {
    addNode(Output, Stack -> tail -> word);
    //Stack -> tail = Stack -> tail -> prev;
    deleteNode(Stack, Stack -> tail);
  }
  while (arithlist -> tail != NULL)
  {
    deleteNode(arithlist, arithlist -> tail);
  }
  arithlist -> head = Output -> head;
  arithlist -> tail = Output -> tail;
  deleteList(Stack);
  free(Output);
  free(tmp);
  return true;
  //while (curln != NULL)
  //{      
  //deleteNode(arithlist, curln);      
 //// curln = arithlist -> head;    
  //}
  //ListNode * curln = arithlist -> head;
}
#endif
