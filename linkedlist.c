#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    int val;
    struct node *next;
} node;

typedef struct list {
    node *head;
    node *tail;
    int len;
} list;

node * lnode(int val);
list * lcreate(int vals[], int len);
void lprintn(node *head);
void lprint(list *l);
void lappend(list *l, int val);
node * lsearch(list *l, int val);
void lunlink(list *l, int val);
void lunlink_all(list *l, int val);
void lreverse(list *l);
void lfree(list *l);

int main(int argc, char *argv[])
{
    // Create a linked list with one node
    node *n = lnode(4);
    lprintn(n);
    free(n);

    int nums[] = {1, 3, 5, 7, 11, -1, -10, -100, 11, 3, 1, 1};
    list *l = lcreate(nums, sizeof(nums)/sizeof(nums[0]));
    lprint(l);

    lappend(l, 15);
    lprint(l);

    lprintn(lsearch(l, 52));

    lappend(l, 33);
    lunlink(l, 33);
    lprint(l);

    lappend(l, 1);
    lunlink_all(l, 15);
    lunlink_all(l, 1);
    lprint(l);
    lprintn(l->tail);

    lreverse(l);
    lprint(l);
    lprintn(l->tail);

    lfree(l);
    lprint(l);
}

// Creates a linked list with a single node whose value is val
// Returns a pointre to the node
node * lnode(int val)
{
    node *head = (node *)malloc(sizeof(node *));
    head->val = val;

    return head;
}

// Creates a linked list with multiples node whose values are those stored in int val[]
// Returns a pointer to the head of the list
list * lcreate(int vals[], int len)
{
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
    l->tail = prev;
    l->len = len;

    return l;
}

// Creates a node with val=val and appends it to the list
// Theta(1) since list tail is tracked
void lappend(list *l, int val)
{
    node *n = lnode(val);

    l->tail->next = n;
    l->tail = n;
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

// Remove the first node in the list whose val matches argument val
// O(n) at worst
void lunlink(list *l, int val)
{
    node *prev = NULL;
    node *tmp = l->head;

    while(tmp != NULL && tmp->val != val)
    {
        prev = tmp;
        tmp = tmp->next;
    }

    // Not found
    if(tmp == NULL)
        return;

    if(tmp == l->head)
        l->head = tmp->next;
    else
        prev->next = tmp->next;

    if(tmp == l->tail)
        l->tail = prev;
    
    free(tmp);
    l->len--;
}

// Frees all nodes with val=val from list l
// O(n)
void lunlink_all(list *l, int val)
{
    node *prev = NULL;
    node *curr = l->head;

    while(curr != NULL)
    {
        // If match found, update curr according to its position in the list
        // Prev stays as is since we need to check for a match against curr in the next iter
        if(curr->val == val)
        {
            node *tmp = curr;
            if(curr == l->head)
                curr = l->head = curr->next;
            else
                curr = prev->next = curr->next;

            if(tmp == l->tail)
                l->tail = prev;

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
    free(l);
}

// Prints the linked list originating at node *head
// Theta(n)
void lprintn(node *head)
{
    if(head == NULL)
    {
        printf("Empty list\n");
        return;
    }

    node *tmp = head;
    printf("[");
    while(tmp->next != NULL)
    {
        printf("%i, ", tmp->val);
        tmp = tmp->next;
    }
    printf("%i]\n", tmp->val);
}

// Prints a list
void lprint(list *l)
{
    if(l == NULL)
    {
        printf("NULL list\n");
        return;
    }
    printf("{len: %i} ", l->len);
    lprintn(l->head);
}