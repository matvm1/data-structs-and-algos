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
        tree *tprev = NULL, *tnext = NULL;

        if((*r)->prev)
            tprev = (*r)->prev;

        if((*r)->next)
            tnext = (*r)->next;
    
        if(!tprev)
        {
            if(!tnext)
                (*r)->parent->subtree = NULL;
            else
            {
                (*r)->parent->subtree = tnext;
                tnext->parent = (*r)->parent;
                tnext->prev = NULL;
                (*r)->parent = NULL;
                (*r)->next = NULL;
            }
        }
        else
        {
            tprev->next = tnext;
            if(tnext)
            {
                tnext->prev = tprev;
                (*r)->next = NULL;
            }
                
        }
        
        tfree(r);
    }

    if(mode == 'p')
    {
        tree *pprev = NULL, *pnext = NULL, *promoted = NULL;

        if((*r)->prev)
            pprev = (*r)->prev;

        if((*r)->next)
            pnext = (*r)->next;

        if((*r)->subtree)
            promoted = (*r)->subtree;
 
        if(promoted)
        {
            if(!pprev)
            {
                (*r)->parent->subtree = promoted;
                promoted->parent = (*r)->parent;

                if(pnext)
                {
                    promoted->next = pnext;
                    pnext->prev = promoted;
                }

                promoted->prev = NULL;
            }
            else
            {
                (*r)->prev->next = promoted;
                if(pnext)
                {
                    tree *tmp = promoted;
                    while(tmp->next != NULL)
                        tmp = tmp->next;

                    tmp->next = pnext;
                    pnext->prev = tmp;
                }

                promoted->parent = NULL;
                promoted->prev = pprev;
            }
        }
        else
        {
            if(!pprev)
            {
                (*r)->parent->subtree = pnext;
                if(pnext)
                {
                    pnext->parent = (*r)->parent;
                    pnext->prev = NULL;
                }
            }
            else
            {
                pprev->next = pnext;

                if(pnext)
                    pnext->prev = pprev;
            }
        }

        free(*r);
        *r = NULL;
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

// theight() helper
int theight_h(tree *t, int height, int maxheight)
{
    if(t == NULL)
        return height;

    if(height > maxheight)
        maxheight = height;

    int res1 = height;
    int res2 = height;

    if(t->subtree != NULL)
        res1 = theight_h(t->subtree, height + 1, maxheight);

    if(t->next != NULL)
        res2 = theight_h(t->next, height, maxheight);

    if(res1 > res2)
        return res1;
    else
        return res2;   
}

// Returns the height of tree t
int theight(tree *t)
{
    if(t == NULL)
        return 0;

    return theight_h(t, 1, 1);
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
