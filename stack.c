#include "structs.h"

// Creates an empty stack
stack * stcreaten()
{
    stack *s = (stack *)malloc(sizeof(stack));
    if(s == NULL)
        return NULL;
    
    list *l = lcreaten();
    if(l == NULL)
    {
        free(s);
        return NULL;
    }

    s->list = l;
    s->height = 0;
    return s;
}

stack * stcreatea(int vals[], long len)
{
    stack *s = (stack *)malloc(sizeof(stack));
    if(s == NULL)
        return NULL;
    
    list *l = lcreatea(vals, len, 'p');
    if(l == NULL)
    {
        free(s);
        return NULL;
    }

    s->list = l;
    s->height = l->len;
    return s;
}

void push(stack *s, int val)
{
    if(s == NULL)
        return;

    lprepend(s->list, val);
    s->height++;
}

int pop(stack *s)
{
    if(s->list == NULL || s->list == NULL || s->list->head == NULL || s->height == 0)
    {
        printf("Error popping from stack\n");
        exit(EXIT_FAILURE);
    }

    int r = s->list->head->val;
    ldeletep(s->list, 0);
    s->height--;

    return r;
}

int peek(stack *s)
{
    if(s->list == NULL || s->list == NULL || s->list->head == NULL || s->height == 0)
    {
        printf("Error peeking at stack\n");
        exit(EXIT_FAILURE);
    }

    int r = s->list->head->val;

    return r;
}

void stprint(stack *s)
{
    if(s == NULL)
    {
        printf("NULL stack\n");
        return;
    }

    lprint(s->list); //segfaulting after freeing
}

void stfree(stack **s)
{
    if(s == NULL || *s == NULL)
        return;

    lfree(&((*s)->list));
    free(*s);
    *s = NULL;
}