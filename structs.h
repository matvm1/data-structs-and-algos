#ifndef CONFIG_H
#define CONFIG_H

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

// List wrapper
typedef struct stack {
    list *list;
} stack;

node * lnode(int val);
list * lcreaten();
list * lcreate(int vals[], long len, char mode);
void lprepend(list *l, int val);
void lappend(list *l, int val);
node * lsearch(list *l, int val);
void ldelete(list *l, node *prev, node *node);
void ldeletep(list *l, long p);
void ldeletev(list *l, int val);
void ldeletea(list *l, int val);
void lsethead(list *l, node *n);
void lsettail(list *l, node *n);
void lreverse(list *l);
void lfree(list **l);
void lprint(list *l);
void lprintn(node *node);
void lmakecirc(list *l);
void lremovecirc(list *l);
void clprint(list *l, int m);
void clprintn(list *l, node *n, int m);

stack * stcreate();
stack * stcreaten(int vals[], long len);
void push(stack *s, int val);
int pop(stack *s);
int peek(stack *s);
void stprint(stack *s);

#endif