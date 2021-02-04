// ***
// *** You MUST modify this file
// ***

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

// DO NOT MODIFY FROM HERE --->>>
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

static void preOrderNode(TreeNode * tn, FILE * fptr)
{
  if (tn == NULL)
    {
      return;
    }
  fprintf(fptr, "%d\n", tn -> value);
  preOrderNode(tn -> left, fptr);
  preOrderNode(tn -> right, fptr);
}

void preOrder(Tree * tr, char * filename)
{
  if (tr == NULL)
    {
      return;
    }
  FILE * fptr = fopen(filename, "w");
  preOrderNode(tr -> root, fptr);
  fclose (fptr);
}
// <<<--- UNTIL HERE

// ***
// *** You MUST modify the follow function
// ***

#ifdef TEST_BUILDTREE
// Consider the algorithm posted on
// https://www.geeksforgeeks.org/construct-a-binary-tree-from-postorder-and-inorder/
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
