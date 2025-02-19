#include "structs.h"

// Creates an empty tree
tree * tcreaten()
{
    tree *t = (tree *)malloc(sizeof(tree));
    if(t == NULL)
        return NULL;

    t->prev = NULL;
    t->next = NULL;
    t->parent = NULL;
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
    t->prev = NULL;
    t->next = NULL;
    t->parent = NULL;
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

    if(t->subtree == NULL)
    {
        t->subtree = tcreatenv(val);
        t->subtree->parent = t;
        return t->subtree;
    }
    
    tree *tmp = t->subtree;
    while(tmp->next != NULL)
        tmp = tmp->next;

    tmp->next = tcreatenv(val);
    tmp->next->prev = tmp;

    return tmp->next;
}

// Searches for a subtree in t where t->val==val and deletes it if found
// mode: 't' - trims the entire branch, 'p' - promotes subtree
// Use tfree() to delete root nodes
void tdelete(tree *t, int val, char mode)
{
    if(t == NULL || (mode != 't' && mode != 'p'))
        return;

    tree **r = tsearch(t, val); 
    if(r == NULL)
        return;   

    if(t == *r)
        return;

    if(mode == 't')
    {
        if((*r)->prev == NULL)
        {
            if((*r)->next == NULL)
                (*r)->parent->subtree = NULL;
            else
            {
                (*r)->parent->subtree = (*r)->next;
                (*r)->next->parent = (*r)->parent;
                (*r)->parent = NULL;
                (*r)->next = NULL;
            }
        }
        else
        {
            if((*r)->next == NULL)
                (*r)->prev->next = NULL;
            else
            {
                (*r)->prev->next = (*r)->next;
                (*r)->next = NULL;
                tfree(&(*r));
                return;
            }
                
        }
        
        tfree(r);
    }

    if(mode == 'p')
    {
   /*     if((*r)->prev == NULL)
        {
            if((*r)->next == NULL)
               (*r)->parent->subtree = (*r)->subtree;
        }

        free(*r);
        *r = NULL;*/
    }
}

// Searches for the tree node in t whose val==val
// Returns the head of that tree node if found, NULL otherwise
tree ** tsearch(tree *t, int val)
{
    if(t == NULL)
        return NULL;

    tree **res = NULL;
    if(t->val == val)
        res = &t;

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
// Will free t->next if it exists
void tfree(tree **t)
{
    if(t == NULL || *t == NULL)
        return;
    
    tree *current = *t;
    tree *next = (*t)->next;
    tree *subtree = (*t)->subtree;

    if(next != NULL)
        tfree(&(next));
    if(subtree != NULL)
        tfree(&(subtree));

    free(current);
    *t = NULL;
}
