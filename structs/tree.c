#include "structs.h"

// Creates an empty tree
tree * tcreaten()
{
    tree *t = (tree *)malloc(sizeof(tree));
    if(t == NULL)
        return NULL;

    t->next = NULL;
    t->subtree = NULL;

    return t;
}

// Creates a tree with val=val
tree * tcreatenv(int val)
{
    tree *t = (tree *)malloc(sizeof(tree));
    if(t == NULL)
        return NULL;

    t->val = val;
    t->next = NULL;
    t->subtree = NULL;

    return t;
}

// Inserts val as a child node to t
// Supports k-trees
// Returns the child tree
tree * tinsert(tree *t, int val)
{
    if(t == NULL)
        return NULL;

    tree *tmp = t->subtree;
    if(t->subtree == NULL)
    {
        t->subtree = tcreatenv(val);
        return t->subtree;
    }

    while(tmp->next != NULL)
        tmp = tmp->next;

    tmp->next = tcreatenv(val);

    return tmp;
}

// tprint() helper
void tprint_h(tree *t, int depth)
{
    if(t == NULL)
        return;

    for(int i = 0; i < depth; i++)
        printf(" ");

    int x = t->val;
    printf("%i\n", t->val);

    if(t->subtree == NULL)
        return;

    tree *tmp = t->subtree;
    while(tmp != NULL)
    {
        tprint_h(tmp, depth + 1);
        tmp = tmp->next;
    }
}

// Prints a tree
void tprint(tree *t)
{
    tprint_h(t, 0);
}
