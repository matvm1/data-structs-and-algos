#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    int val;
    struct node *next;
} node;

node * create_node(int val);
node * create_list(int vals[], int len);
void print(node *head);
void add(node *head, int val);
/*void add(node *bt, int val);
void remove(node *head, int val);
void sort(node *head);
void create_circular_link(node *head);
void remove_ciruclar_link(node *head);
void reverse(node *head);
void free();*/

int main (int argc, char *argv[])
{
    // Create a linked list with one node
    node *ll = create(4);
    print(ll);

    int nums[] = {1, 3, 5, 7, 11};
    node *ll1 = createm(nums, sizeof(nums)/sizeof(nums[0]));
    print(ll1);
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
node * create_list(int vals[], int len)
{
    node *head = create(vals[0]);
    node *prev = head;
    for(int i = 1; i < len; i++)
    {
        node *n = create(vals[i]);
        prev->next = n;
        prev = n;
    }

    return head;
}

// Prints the linked list originating at head
// Theta(n)
void print(node *head)
{
    node *tmp = head;
    printf("[");
    while(tmp->next != NULL)
    {
        printf("%i, ", tmp->val);
        tmp = tmp->next;
    }
    printf("%i]\n", tmp->val);
}