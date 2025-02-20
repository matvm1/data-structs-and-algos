#include "structs.h"

// Creates a new binary tree with val=0 and NULL children
bst * bcreaten()
{
    bst *b = (bst *)malloc(sizeof(bst));
    b->val = 0;
    b->left = NULL;
    b->right = NULL;

    return b;
}

// Creates a new binary tree with b->val=val and NULL children
bst * bcreatenv(int val)
{
    bst *b = (bst *)malloc(sizeof(bst));
    b->val = val;
    b->left = NULL;
    b->right = NULL;

    return b;
}

// Creates a new binary tree with nodes populated from int vals[]
// O(n^2)
// Average(n log n)
// Omega(n log n) 
// TODO: Optimize such that a references to the most recently inserted node is kept, and inserting from there
bst * bcreatea(int vals[], long len)
{
    if(len < 1)
        return NULL;

    if(!vals)
        return NULL;

    bst *b = bcreatenv(vals[0]);
    for(int i = 1; i < len; i++)
        binsert(b, vals[i]);
    
    return b;
}

// Creates a node with val=val and inserts it into the tree, but only if no other nodes with that val exist
// O(n)
// Average(log n)
// Omega(1)
void binsert(bst *b, int val)
{
    if(!b)
		return;

    if(b->val == val)
        return;

	if(!b->left && val < b->val)
    {
		b->left = bcreatenv(val);
		return;
    }

	if(!b->right && val > b->val)
    {
		b->right = bcreatenv(val);
		return;
    }

	if(val < b->val)
		binsert(b->left, val);

	if(val > b->val)
		binsert(b->right, val);
}

// Prints a binary tree
// TODO: Print such that the left node is printed prior to the parent, and right node after the parent
void bprint_h(bst *b, int depth)
{
    for(int i = 0; i < depth; i++)
        printf(" ");

    printf("%i\n", b->val);

    if(b->left)
        bprint_h(b->left, depth + 1);

    if(b->right)
        bprint_h(b->right, depth + 1);
}

void bprint(bst *b)
{
    if(b == NULL)
    {
        printf("NULL bst\n");
        return;
    }

    bprint_h(b, 0);
}

void bfree(bst **b)
{
    if(!b || !*b)
        return;
    
    bst *curr = *b;
    bst *left = curr->left;
    bst *right = curr->right;

    if(left)
        bfree(&left);
    
    if(right)
        bfree(&right);

    free(*b);
    *b = NULL;
}