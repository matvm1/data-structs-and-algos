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

// Creates a node with val=val and inserts it into the tree, but only if no other nodes with that val exist
// Returns a pointer to the new node (or a pointer to the existing node if val is already present in the tree)
// O(n)
// Average(log n)
// Omega(1)
// More memory usage as local pointers require stack mem
// Subsuequent inserts with this function into a tree not rooted at b may break the BST structure of the tree
bst * binsert_r(bst *b, int val)
{
    if(!b)
		return NULL;

    bst *res = NULL;

    if(b->val == val)
        res = b;

	if(!b->left && val < b->val)
    {
		b->left = bcreatenv(val);
		res = b->left;
    }

	if(!b->right && val > b->val)
    {
		b->right = bcreatenv(val);
		res = b->right;
    }

	if(!res && val < b->val)
		res = binsert_r(b->left, val);

	if(!res && val > b->val)
		res = binsert_r(b->right, val);

    return res;
}

// Searches for the node in b with val=val
// Returns the nodes address if found, NULL otherwise
// O(log n)
// Omega(1)
bst * bstsearch(bst *b, int val)
{
    if(!b)
        return NULL;

    bst *res = NULL;
    if(b->val == val)
        res = b;

    if(!res && val < b->val && b->left)
        res = bstsearch(b->left, val);

    if(!res && val > b->val && b->right)
        res = bstsearch(b->right, val); 

    return res;
}

// bprint() helper
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

// Prints a binary tree
void bprint(bst *b)
{
    if(b == NULL)
    {
        printf("NULL bst\n");
        return;
    }

    bprint_h(b, 0);
}

// Frees BST b and its children
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