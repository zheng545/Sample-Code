// ***
// *** You MUST modify this file
// ***

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tree.h"

// DO NOT MODIFY FROM HERE --->>>
Tree * newTree(void)
{
  Tree * t = malloc(sizeof(Tree));
  t -> root = NULL;
  return t;
}

void deleteTreeNode(TreeNode * tr)
{
  if (tr == NULL)
    {
      return;
    }
  deleteTreeNode (tr -> left);
  deleteTreeNode (tr -> right);
  free (tr);
}

void freeTree(Tree * tr)
{
  if (tr == NULL)
    {
      // nothing to delete
      return;
    }
  deleteTreeNode (tr -> root);
  free (tr);
}


// <<<--- UNTIL HERE

// ***
// *** You MUST modify the follow function
// ***
#ifdef TEST_BUILDTREE
TreeNode * helper(int * inArray, int * postArray, int inStart, int inEnd, int *postIndex)
{
  if (inStart > inEnd){return NULL;}

  // find the root based on postArray
  int root = postArray[*postIndex];
  (*postIndex)--; 

  TreeNode * tn = malloc(sizeof(TreeNode));
  tn -> left = NULL;
  tn -> right = NULL;
  tn -> value = root;

  /* If this node has no children then return */
  if (inStart == inEnd){return tn;}

  // find the index of root in inArray
  int inIndex;
  for (int x = inStart; x <= inEnd; x++)
  {
    if (inArray[x] == root)
    {
      inIndex = x;
    }
  }

  /* Using index in Inorder traversal, construct left and right subtress */
  tn -> right = helper(inArray, postArray, inIndex + 1, inEnd, postIndex); 
  tn -> left = helper(inArray, postArray, inStart, inIndex - 1, postIndex); 
  
  return tn; 
}

Tree * buildTree(int * inArray, int * postArray, int size)
{
  int Index = size - 1; 
  Tree * tr = malloc(sizeof(Tree));
  tr -> root = helper(inArray, postArray, 0, size - 1, &Index); 
  return tr;
}
#endif

#ifdef TEST_PRINTPATH
bool findPath(TreeNode * root, int ln)  
{  
  if (root == NULL){return false;} 
  if (root -> value == ln)
  {
    //arr[Index] = root -> value;
    printf("%d\n",root -> value);
    return true;
  }        
  // check whether the required node lies in the left subtree or right subtree of the current node  
  if (findPath(root -> left, ln) || findPath(root -> right, ln)) 
  {
    printf("%d\n",root -> value);
    return true;
  }
  return false;           
}  
void printPath(Tree * tr, int val)
{
  findPath(tr -> root, val);
}

#endif
