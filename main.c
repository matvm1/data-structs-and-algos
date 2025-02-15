#include "structs/structs.h"
#include "structs/linkedlist.c"
#include "structs/stack.c"
#include "structs/queue.c"

void singlylinkedlists();
void stacks();
void queues();

int main(int argc, char *argv[])
{
    queues();
}

void singlylinkedlists()
{
    int nums[] = {1, 3, 3, 5, 7, 11, 4, -1, -10, -100, 11, 3, 1, 1, 2, 4, 3};
    printf("Creating list0 from array:\n    l0: ");
    list *l0 = lcreatea(nums, sizeof(nums)/sizeof(nums[0]), 'a');
    lprint(l0);

    printf("Creating list1 from array:\n    l1: ");
    list *l1 = lcreatea(nums, sizeof(nums)/sizeof(nums[0]), 'a');
    lprint(l1);

    printf("Making list1 circular:\n    l1: ");
    lmakecirc(l1);
    clprint(l1, l1->len * 2 + 1);

    printf("Printing list1 without reference in first arg:\n    l1: ");
    clprintn(NULL, l1->head, l1->len * 2 + 1);

    printf("Appending 15 to both:\n     l0: ");
    lappend(l0, 15);
    lprint(l0);
    lappend(l1, 15);
    printf("    l1: ");
    clprint(l1, l1->len + 1);

    printf("Searching for -100\n    l0: ");
    lprintn(lsearch(l0, -100));
    printf("    l1: ");
    clprintn(NULL, lsearch(l1, -100), 1);

    printf("Searching for 52:\n    l0: ");
    lprintn(lsearch(l0, 52));
    printf("    l1: ");
    clprintn(NULL, lsearch(l1, 52), 1);

    printf("Reversing:\n    l0: ");
    lreverse(l0);
    lprint(l0);
    printf("    l1: ");
    lreverse(l1);
    lprint(l1);
    printf("    l1: ");
    clprint(l1, l1->len * 2 + 1);

    printf("Delete 15:\n    l0: ");
    ldeletev(l0, 15);
    lprint(l0);
    printf("    l1: ");
    ldeletev(l1, 15);
    clprint(l1, l1->len + 1);

    printf("Delete -100:\n    l0: ");
    ldeletev(l0, -100);
    lprint(l0);
    printf("    l1: ");
    ldeletev(l1, -100);
    clprint(l1, l1->len + 1);

    printf("Append and then delete 33:\n    l0: ");
    lappend(l0, 33);
    ldeletev(l0, 33);
    lprint(l0);
    printf("    l1: ");
    lappend(l1, 33);
    ldeletev(l1, 33);
    clprint(l1, l1->len + 1);

    printf("Deleting pos 0:\n    l0:");
    ldeletep(l0, 0);
    lprint(l0);
    printf("    l1: ");
    ldeletep(l1, 0);
    clprint(l1, l1->len + 1);

    printf("Deleting pos mid:\n    l0:");
    ldeletep(l0, l0->len/2);
    lprint(l0);
    printf("    l1: ");
    ldeletep(l1, l1->len/2);
    clprint(l1, l1->len + 1);

    printf("Deleting pos len:\n    l0:");
    ldeletep(l0, l0->len - 1);
    lprint(l0);
    printf("    l1: ");
    ldeletep(l1, l1->len - 1);
    clprint(l1, l1->len + 1);

    printf("Delete all 3s:\n    l0: ");
    ldeletea(l0, 3);
    lprint(l0);
    printf("    l1: ");
    ldeletea(l1, 3);
    clprint(l1, l1->len + 1);

    printf("Delete all 1s:\n    l0: ");
    ldeletea(l0, 1);
    lprint(l0);
    printf("    l1: ");
    ldeletea(l1, 1);
    clprint(l1, l1->len + 1);

    printf("Delete all 4s:\n    l0: ");
    ldeletea(l0, 4);
    lprint(l0);
    printf("    l1: ");
    ldeletea(l1, 4);
    clprint(l1, l1->len + 1);

    printf("Removing circular link from l1:\n    l1: ");
    lremovecirc(l1);
    clprint(l1, l1->len + 1);
    printf("Printing l1 using lprint:\n    l1: ");
    lprint(l1);

    printf("Creating empty list l2:\n    l2: ");
    list *l2 = lcreaten();
    lprint(l2);
    printf("Appending 16 vals to l2:\n    l2: ");
    for(int i = 0; i < 16; i++)
        lappend(l2, i);
    lprint(l2);

    printf("Creating empty list l3, prepending 16 vals, appending 47, and reversing:\n    l3: ");
    list *l3 = lcreaten();
    for(int i = 0; i < 16; i++)
        lprepend(l3, i);
    lappend(l3, 47);
    lreverse(l3);
    lmakecirc(l3);
    clprint(l3, l3->len * 2 + 1);

    printf("Creating empty list and appending 1 val:\n    l4: ");
    list *l4 = lcreaten();
    lappend(l4, 500);
    lreverse(l4);
    lprint(l4);

    printf("Deleting from list with 1 val:\n    l4: ");
    ldeletep(l4, 0);
    lprint(l4);

    printf("Freeing lists:\n    l0: ");
    lfree(&l0);
    lprint(l0);
    printf("    l1: ");
    lfree(&l1);
    lprint(l1);
    printf("    l2: ");
    lfree(&l2);
    lprint(l2);
    printf("    l3: ");
    lfree(&l3);
    lprint(l3);
    printf("    l4: ");
    lfree(&l4);
    lprint(l4);
}

void stacks()
{
    printf("Creating stack0 from array:\n    s0:");
    int nums[] = {1, 3, 3, 5, 7, 11, 4, -1, -10, -100, 11, 3, 1, 1, 2, 4, 3};
    stack *s0 = stcreatea(nums, sizeof(nums)/sizeof(nums[0]));
    stprint(s0);

    printf("Creating stack1 by pushing vals:\n    s1:");
    stack *s1 = stcreaten();
    for(int i = 0; i < 20; i++)
        push(s1, i);
    stprint(s1);

    printf("Freeing s1:\n    s1: ");
    stfree(&s1);
    stprint(s1);

    printf("Peeking from s0:\n    s0 top: %i\n", stpeek(s0));
    printf("Popping from s0:\n    s0 popped val: %i\n    s0: ", pop(s0));
    stprint(s0);

    printf("Pushing 30 to s0 and popping immediately:\n    s0 top: ");
    push(s0, 30);
    printf("%i\n    s0: ", pop(s0));
    stprint(s0);

    printf("Popping all from s0:\n    s0: ");
    int sth = s0->height;
    for(int i = 0; i < sth; i++)
        pop(s0);
    stprint(s0);

    printf("Freeing s0:\n    s1: ");
    stfree(&s0);
    stprint(s0);
}

void queues()
{
    printf("Creating queue0 from array:\n    q0:");
    int nums[] = {1, 3, 3, 5, 7, 11, 4, -1, -10, -100, 11, 3, 1, 1, 2, 4, 3};
    queue *q0 = qcreatea(nums, sizeof(nums)/sizeof(nums[0]));
    qprint(q0);

    printf("Creating queue1 by enqueueing vals:\n    q1:");
    queue *q1 = qcreaten();
    for(int i = 0; i < 20; i++)
        enqueue(q1, i);
    qprint(q1);

    printf("Freeing q1:\n    q1: ");
    qfree(&q1);
    qprint(q1);

    printf("Peeking from q0:\n    q0 top: %i\n", qpeek(q0));
    printf("Dequeueing from q0:\n    q0 dequeue val: %i\n    q0: ", dequeue(q0));
    qprint(q0);

    printf("Enqueueing 30 to q0 and popping:\n    q0 val: ");
    enqueue(q0, 30);
    printf("%i\n    q0: ", dequeue(q0));
    qprint(q0);

    printf("Dequeueing all from q0:\n    q0: ");
    int qlen = q0->len;
    for(int i = 0; i < qlen; i++)
        dequeue(q0);
    qprint(q0);

    printf("Freeing q0:\n    q1: ");
    qfree(&q0);
    qprint(q0);
}