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

// List wrapper for stacks
typedef struct stack {
    list *list;
    long height;
} stack;

// List wrapper for queues
typedef struct queue {
    list *list;
    long len;
} queue;

typedef struct tree{
    int val;
    struct tree *prev;
    struct tree *next;
    struct tree *parent;
    struct tree *subtree;
} tree;

// linked lists
node * lnode(int val);
list * lcreaten();
list * lcreatea(int vals[], long len, char mode);
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

// stacks
stack * stcreaten();
stack * stcreatea(int vals[], long len);
void push(stack *s, int val);
int pop(stack *s);
int stpeek(stack *s);
void stprint(stack *s);
void stfree(stack **s);

// queues
queue * qcreaten();
queue * qcreatea(int vals[], long len);
void enqueue(queue *q, int val);
int dequeue(queue *q);
int qpeek(queue *q);
void qprint(queue *q);
void qfree(queue **q);

// trees
tree * tcreaten();
tree * tcreatenv(int val);
tree * tinsert(tree *t, int val);
void tdelete(tree *t, int val, char mode);
int * theight(tree *t);
tree ** tsearch(tree *t, int val);
void tprint(tree *t);
void tfree(tree **t);

#endif