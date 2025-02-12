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
void unlink_all(list *l, int val);
/*void sort(node *head);
void create_circular_link(node *head);
void remove_ciruclar_link(node *head);
void reverse(node *head);
void free();*/

int main (int argc, char *argv[])
{
    // Create a linked list with one node
    node *n = create_node(4);
    printn(n);

    int nums[] = {1, 3, 5, 7, 11, -1, -10, -100, 11, 3, 1, 1};
    list *l = create_list(nums, sizeof(nums)/sizeof(nums[0]));
    print(l);

    append(l, 15);
    print(l);

    printn(search(l, 52));

    append(l, 33);
    unlink(l, 33);
    print(l);

    append(l, 1);
    unlink_all(l, 15);
    unlink_all(l, 1);
    print(l);
    printn(l->tail);
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
    l->tail = n;
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
// O(n) at worst
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
        l->head = tmp->next;
    else
        prev->next = tmp->next;

    if(tmp == l->tail)
        l->tail = prev;
    
    free(tmp);
}

// Frees all nodes with val=val from list l
// O(n)
void unlink_all(list *l, int val)
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
        }
        // No, match, keep chucking along
        else
        {
            prev = curr;
            curr = curr->next;
        }
    }
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