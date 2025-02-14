#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    int val;
    struct node *next;
} node;

typedef struct list {
    node *head;
    node *tail;
    long len;
    int iscircular; // 1 - yes, 0 - no
} list;

node * lnode(int val);
list * lcreate(int vals[], long len);
void lappend(list *l, int val);
node * lsearch(list *l, int val);
void ldelete(list *l, node *prev, node *node);
void ldeletep(list *l, long p);
void ldeletev(list *l, int val);
void ldeletea(list *l, int val);
void lsettail(list *l, node *n);
void lreverse(list *l);
void lfree(list *l);
void lprint(list *l);
void lprintn(node *node);
void lmakecirc(list *l);
void clprint(list *l, int m);
void clprintn(list *l, node *n, int m);

// Creates a linked list with a single node whose value is val
// Returns a pointre to the node
node * lnode(int val)
{
    node *head = (node *)malloc(sizeof(node *));
    head->val = val;

    return head;
}

// Creates a non-circular linked list with multiples node whose values are those stored in int val[]
// Returns a pointer to the head of the list
list * lcreate(int vals[], long len)
{
    if(len < 1)
        return NULL;

    node *head = lnode(vals[0]);
    node *prev = head;
    for(int i = 1; i < len; i++)
    {
        node *n = lnode(vals[i]);
        prev->next = n;
        prev = n;
    }

    list *l = (list *)malloc(sizeof(list));
    l->head = head;
    lsettail(l, prev);
    l->len = len;
    l->iscircular = 0;

    return l;
}

// Creates a node with val=val and appends it to the list
// Theta(1) since list tail is tracked
void lappend(list *l, int val)
{
    node *n = lnode(val);

    l->tail->next = n;
    lsettail(l, n);
    l->len++;
}

// Returns the address of the first node in the list whose val equals the val arg
// O(n) at worst
node * lsearch(list *l, int val)
{
    node *tmp = l->head;

    while(tmp != NULL && tmp->val != val)
        tmp = tmp->next;

    return tmp;
}

// Unlinks *node from the list
void ldelete(list *l, node *prev, node *node)
{
    if(node == l->head)
        l->head = node->next;
    else if(node == l->tail)
        lsettail(l, prev);
    else
        prev->next = node->next;

    free(node);
    l->len--;
}

// Unlinks the pth node in the list (where 0 <= p < l->len)
void ldeletep(list *l, long p)
{
    // Invalid positions
    if(p < 0 || p > l->len - 1)
        return;
    
    node *prev = NULL;
    node *curr = l->head;
    for(int i = 0; i < p; i++)
    {
        prev = curr;
        curr = curr->next;
    }

    ldelete(l, prev, curr);
}

// Remove the first node in the list whose val matches argument val
// O(n) at worst
void ldeletev(list *l, int val)
{
    node *prev = NULL;
    node *curr = l->head;

    while(curr != NULL && curr->val != val)
    {
        prev = curr;
        curr = curr->next;
    }

    // Not found
    if(curr == NULL)
        return;
    
    ldelete(l, prev, curr);
}

// Frees all nodes with val=val from list l
// O(n)
void ldeletea(list *l, int val)
{
    node *prev = NULL;
    node *curr = l->head;

    while(curr != NULL)
    {
        // If match found, update curr according to its position in the list
        // Prev stays as is since we need to check for a match against curr in the next iter
        // Could use ldelete() here but then would need additional condition to repoint curr
        if(curr->val == val)
        {
            node *tmp = curr;
            if(curr == l->head)
                curr = l->head = curr->next;
            else
                curr = prev->next = curr->next;

            if(tmp == l->tail)
                lsettail(l, prev);

            free(tmp);
            l->len--;
        }
        // No, match, keep chucking along
        else
        {
            prev = curr;
            curr = curr->next;
        }
    }
}

// Reverses the list
void lreverse(list *l)
{
    node *prev = NULL;
    node *curr = l->head;
    l->tail = curr;

    // Point the curr node to the prev, whilst maintining reference to the rest of the list, and move forward
    while(curr != NULL)
    {
        node *tmp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = tmp;
    }

    l->head = prev;
}

// Sets the tail of the list to node n
void lsettail(list *l, node *n)
{
    if(l->iscircular)
    {
        l->tail->next = n;
        n->next = l->head;
    }
    else
        // Ensure tail->next doesn't point to garbage data
        n->next = NULL;
    l->tail = n;    
}

// Frees all nodes in the list and the list itself
void lfree(list *l)
{
    node *tmp = l->head;

    while(l->head != NULL)
    {
        l->head = l->head->next;
        free(tmp);
        tmp = l->head;
    }
    l->len = 0;
    free(l);
}

// Prints a list
void lprint(list *l)
{
    if(l == NULL)
    {
        printf("NULL list\n");
        return;
    }

    printf("{len: %li} ", l->len);

    if(!l->iscircular)
        lprintn(l->head);
    else
        clprint(l, l->len);
}

// Prints the linked list originating at node *head
// Theta(n)
void lprintn(node *n)
{
    if(n == NULL)
    {
        printf("NULL list\n");
        return;
    }

    node *tmp = n;
    printf("[");
    while(tmp->next != NULL)
    {
        printf("%i, ", tmp->val);
        tmp = tmp->next;
    }
    printf("%i]\n", tmp->val);
}

// Makes the list a circular linked list
void lmakecirc(list *l)
{
    l->iscircular = 1;
    l->tail->next = l->head;
}

// Prints m nodes from a circular linked list
// If m is greater than l->len, then the iterator wraps around and continues printing
void clprint(list *l, int m)
{
    if(l == NULL)
    {
        printf("NULL list\n");
        return;
    }

    if(!l->iscircular)
    {
        printf("Not a circular list\n");
        return;
    }

    printf("{len: %li} ", l->len);
    clprintn(l, l->head, m);
}

// Prints m nodesthat trail n.
// If l is a non-NULL list, pretty prints the end of the list.
 void clprintn(list *l, node *n, int m)
 {
    node *prev = NULL;
    node *curr = n;

    printf("[");
    for(int i = 0; i < m - 1; i++)
    {   
        if(l != NULL && curr == l->tail)
            printf("%i | ", curr->val);
        else
            printf("%i, ", curr->val);
        prev = curr;
        curr = curr->next;
    }
    printf("%i]\n", curr->val);
 }