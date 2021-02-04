#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#ifdef TEST_READLIST
bool readList(char * filename, List * arithlist)
{
  // arithlist should have memory to store head and tail
  // If arithlist is NULL, return false
  if (arithlist == NULL)
  {
    return false;
  }
  // If fopen fails, return false
  FILE * fptr = fopen(filename,"r");
  if (fptr == NULL)
  {
    return false;
  }
  // read line by line from the input file
  // each line shorter than WORDLENGTH (including '\n' and '\0')
  char word[WORDLENGTH];
  //strchr
  while (fgets(word,sizeof(word),fptr) != NULL)
  {
    //check if line is too line
    //if (word[WORDLENGTH-1] != '\n')
    if ((strchr(word,'\n') == NULL))
    {
      fclose(fptr);
      deleteList(arithlist);
      return false;
    }
    addNode(arithlist,word);
  }
  // of last one is newline 
  
  // If a line is too long,
  //    free memory of the list
  //    fclose
  //    return false  

  // If everything is fine
  //    fclose
  //    arithlist points to the head and tail of the list
  //    return true
  fclose(fptr);
  return true;
}
#endif

#ifdef TEST_DELETELIST
// If arithlist is NULL, do nothing
// release the memory of every node in the list
// release the memory of the list 
void deleteList(List * arithlist)
{
  if (arithlist == NULL){return;}
    ListNode * h = arithlist -> head;
    ListNode * p;
    while (h != NULL)
    {
      p = h -> next;
      free(h);
      h = p;
    }
  free(arithlist);
}
#endif

#ifdef TEST_ADDNODE
// Input: 
// arithlist stores the addresses of head and tail
// If arithlist is NULL, do nothing
// word is the word to be added
//
// Output:
// a ListNode is added to the end (become tail)
//
// allocate memory for a new ListNode
// copy word to the word attribute of the new ListNode
// insert the ListNode to the list
void addNode(List * arithlist, char * word)
{
  if (arithlist == NULL){return;}
  //ListNode * n = arithlist -> head;
  ListNode * added = malloc(sizeof(ListNode));
  strcpy(added -> word, word);
  added -> next = NULL;
  added -> prev = NULL;
  //if added node the first one in list
  if (arithlist -> head == NULL)
  {
    arithlist -> head = added;
    arithlist -> tail = added;
  }
  //added node not the first node inserted
  else
  {
    added -> prev = arithlist -> tail;
    arithlist -> tail -> next = added;
    arithlist -> tail = added;
  }
}
#endif

#ifdef TEST_DELETENODE
// Input:
// arithlist stores the addresses of head and tail
// If arithlist is NULL, return false
// If the list is empty (head and tail are NULL), return false
// ln is the node to be deleted
// If ln is not in the list, return false
// 
// Output:
// arithlist stores the addresses of head and tail
//   after ln is deleted
// return true.
//
// Be careful about delete the first or the last node
bool deleteNode(List * arithlist, ListNode * ln)
{
  if (arithlist == NULL){return false;}
  if (arithlist -> head == NULL){return false;}
  ListNode * finder = arithlist -> head;
  while ((finder != NULL) && (finder != ln)){finder = finder -> next;}
  if (finder == NULL){return false;}
  if (finder == arithlist -> head)
  {
    ListNode * tmp = arithlist -> head -> next;
    if (tmp != NULL)
    {
      tmp -> prev = NULL;
    }
    free(arithlist -> head);
    arithlist -> head = tmp;
    if (arithlist -> head == NULL){arithlist -> tail = NULL;}
    return true;
  }
  if (finder == arithlist -> tail)
  {
    ListNode * tmp = arithlist -> tail -> prev;
    if (tmp != NULL)
    {
      tmp -> next = NULL;
    }
    free(arithlist -> tail);
    arithlist -> tail = tmp;
    if (arithlist -> tail == NULL){arithlist -> head = NULL;}
    return true;
  }
  finder -> next -> prev = finder -> prev;
  finder -> prev -> next = finder -> next;
  free(finder);
  return true;
}
#endif
