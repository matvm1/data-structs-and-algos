#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    int val;
    struct node *next;
} node;

typedef struct list {
    node *head;
    node *tail;
} list;

node * create_node(int val);
list * create_list(int vals[], int len);
void printn(node *head);
void print(list *l);
void append(list *l, int val);
node * search(list *l, int val);
void unlink(list *l, int val);
/*void sort(node *head);
void create_circular_link(node *head);
void remove_ciruclar_link(node *head);
void reverse(node *head);
void free();*/

int main (int argc, char *argv[])
{
    // Create a linked list with one node
    node *l0 = create_node(4);
    printn(l0);

    int nums[] = {1, 3, 5, 7, 11, -1, -10, -100, 11};
    list *l1 = create_list(nums, sizeof(nums)/sizeof(nums[0]));
    print(l1);

    append(l1, 15);
    print(l1);

    printn(search(l1, 52));

    unlink(l1, 11);
    print(l1);
}

// Creates a linked list with a single node whose value is val
// Returns a pointre to the node
node * create_node(int val)
{
    node *head = (node *)malloc(sizeof(node *));
    head->val = val;

    return head;
}

// Creates a linked list with multiples node whose values are those stored in int val[]
// Returns a pointer to the head of the list
list * create_list(int vals[], int len)
{
    node *head = create_node(vals[0]);
    node *prev = head;
    for(int i = 1; i < len; i++)
    {
        node *n = create_node(vals[i]);
        prev->next = n;
        prev = n;
    }

    list *l = (list *)malloc(sizeof(list));
    l->head = head;
    l->tail = prev;

    return l;
}

// Creates a node with val=val and appends it to the list
// Theta(1) since list tail is tracked
void append(list *l, int val)
{
    node *n = create_node(val);

    l->tail->next = n;
}

// Returns the address of the first node in the list whose val equals the val arg
// O(n) at worst
node * search(list *l, int val)
{
    node *tmp = l->head;

    while(tmp != NULL && tmp->val != val)
        tmp = tmp->next;

    return tmp;
}

// Remove the first node in the list whose val matches argument val
void unlink(list *l, int val)
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
    {
        l->head = tmp->next;
    }
    else
    {
        prev->next = tmp->next;
    }

    free(tmp);
}

// Prints the linked list originating at node *head
// Theta(n)
void printn(node *head)
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
void print(list *l)
{
    printn(l->head);
}