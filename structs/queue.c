#include "structs.h"

// Creates an empty queue
queue * qcreaten()
{
    queue *q = (queue *)malloc(sizeof(queue));
    if(q == NULL)
        return NULL;
    
    list *l = lcreaten();
    if(l == NULL)
    {
        free(q);
        return NULL;
    }

    q->list = l;
    q->len = 0;
    return q;
}

// Creates queue from array
queue * qcreatea(int vals[], long len)
{
    queue *q = (queue *)malloc(sizeof(queue));
    if(q == NULL)
        return NULL;
    
    list *l = lcreatea(vals, len, 'a');
    if(l == NULL)
    {
        free(q);
        return NULL;
    }

    q->list = l;
    q->len = l->len;
    return q;
}

// Enqueues val to q
// O(1)
void enqueue(queue *q, int val)
{
    if(q == NULL)
        return;

    lappend(q->list, val);
    q->len++;
}

// Dequeues from q
// Exits program if q or any downstream pointer is null or length is 0
// O(1)
int dequeue(queue *q)
{
    if(q->list == NULL || q->list == NULL || q->list->head == NULL || q->len == 0)
    {
        printf("Error popping from queue\n");
        exit(EXIT_FAILURE);
    }

    int r = q->list->head->val;
    ldeletep(q->list, 0);
    q->len--;

    return r;
}

// Peeks at q
// Exits program if q or any downstream pointer is null or length is 0
int qpeek(queue *q)
{
    if(q->list == NULL || q->list == NULL || q->list->head == NULL || q->len == 0)
    {
        printf("Error peeking at queue\n");
        exit(EXIT_FAILURE);
    }

    int r = q->list->head->val;

    return r;
}

// Prints queue
void qprint(queue *q)
{
    if(q == NULL)
    {
        printf("NULL queue\n");
        return;
    }

    lprint(q->list);
}

// Frees q, the underlying list, and the lists' nodes
void qfree(queue **q)
{
    if(q == NULL || *q == NULL)
        return;

    lfree(&((*q)->list));
    free(*q);
    *q = NULL;
}