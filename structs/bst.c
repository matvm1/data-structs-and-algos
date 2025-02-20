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