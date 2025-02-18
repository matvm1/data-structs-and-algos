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
// Supports n-trees
// Returns the child tree
// O(n) where n is the number of children in t
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

void tdelete(tree *t, int val, char mode)
{
    if(t == NULL)
        return;

    if(mode == 't')
    {
        printf("TODO\n");
    }

    if(mode == 'p')
    {
        printf("TODO\n");
    }
}

// Searches for the tree node in t whose val==val
// Returns the head of that tree node if found, NULL otherwise
tree * tsearch(tree *t, int val)
{
    if(t == NULL)
        return NULL;

    tree *res = NULL;
    if(t->val == val)
        res = t;

    if(res == NULL && t->subtree != NULL)
        res = tsearch(t->subtree, val);

    if(res == NULL && t->next != NULL)
        res = tsearch(t->next, val);

    return res;
}

// tprint() helper
void tprint_h(tree *t, int depth)
{
    if(t == NULL)
    {
        printf("NULL tree\n");
        return;
    }

    for(int i = 0; i < depth; i++)
        printf(" ");

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

// Frees tree and its subtrees
void tfree(tree **t)
{
    if(t == NULL || *t == NULL)
        return;
    
    tree *next = (*t)->next;
    tree *subtree = (*t)->subtree;

    if(next != NULL)
        tfree(&(next));
    if(subtree != NULL)
        tfree(&(subtree));

    free(*t);
    *t = NULL;
}
