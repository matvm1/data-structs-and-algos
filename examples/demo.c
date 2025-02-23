#include "../structs/structs.h"
#include "../structs/arrays.c"
#include "../structs/linkedlist.c"
#include "../structs/stack.c"
#include "../structs/queue.c"
#include "../structs/tree.c"
#include "../structs/bst.c"
#include "../structs/hashtable.c"
#include "hashtables/speller.c"
#include <math.h>

void arrays();
void singlylinkedlists();
void stacks();
void queues();
void trees();
void bsts();
void hashtables(int argc, char *argv[]);

int main(int argc, char *argv[])
{
    arrays();
    //singlylinkedlists();
    //stacks();
    //queues();
    //trees();
    //bsts();
    //hashtables(argc, argv);
}

void arrays()
{
    printf("Creating array nums:\n    nums: ");
    int nums[] = {1, 3, 3, 5, 7, 11, 4, -1, -10, -100, 11, 3, 1, 1, 2, 4, 3};
    int numslen = sizeof(nums)/sizeof(nums[0]);
    int nums2[] = {3, 4, 9, 10};
    int numslen2 = sizeof(nums2)/sizeof(nums2[0]);
    arrprint(nums, numslen);

    printf("Sort nums:\n    nums: \n");
    arrsort(nums, numslen, merge);
    arrprint(nums, numslen);
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

void trees()
{
    printf("Creating tree t0 and manually adding children:\n");
    tree *t0 = tcreatenv(1);
    tree *t0_1 = tinsert(t0, 10);
    tree *t0_2 = tinsert(t0, 20);
    tree *t0_2_20 = tinsert(t0_2, 200);
    tree *t0_3 = tinsert(t0, 30);
    tree *t0_1_10 = tinsert(t0_1, 100);
    tree *t0_3_30 = tinsert(t0_3, 300);
    tprint(t0);
    printf("Height of t0: %i\n", theight(t0));
    printf("-----\n");
    tprint(t0_1);
    printf("-----\n");
    tprint(t0_1_10);
    printf("-----\n");

    printf("Iteratively adding children to t0:\n");
    tree *tmp = t0_1_10;
    for(long i = 3; i <= 9; i++)
    {
        tree *tmp2 = tinsert(tmp, pow(10, i));

        for(int j = 1; j < i; j++)
            tinsert(tmp2, tmp2->val + j);
        tmp = tmp->subtree;
    }
    tprint(t0);
    printf("Height of t0: %i\n", theight(t0));
    printf("-----\n");

    printf("Searching for 1002 in t0:\n");
    tree **r = tsearch(t0, 1002);
    if(r != NULL)
        tprint(*r);
    printf("-----\n");

    printf("Searching for -1002 in t0:\n");
    r = tsearch(t0, -1002);
    if(r != NULL)
        tprint(*r);
    printf("-----\n");

    // Trimming test cases
    printf("Trimming subtree 1000000000 from t0:\n");
    tdelete(t0, 1000000000, 't');
    tprint(t0);
    printf("-----\n");

    printf("Trimming subtree 10000002 from t0:\n");
    tdelete(t0, 10000002, 't');
    tprint(t0);
    printf("-----\n");

    printf("Trimming subtree 100000000 from t0:\n");
    tdelete(t0, 100000000, 't');
    tprint(t0);
    printf("-----\n");

    printf("Trimming subtree 100001 from t0:\n");
    tdelete(t0, 100001, 't');
    tprint(t0);
    printf("-----\n");

    printf("Trimming subtree 1001 from t0:\n");
    tdelete(t0, 1001, 't');
    tprint(t0);
    printf("Height of t0: %i\n", theight(t0));
    printf("-----\n");

    printf("Adding children to t0:\n");
    tree *tmp3 = t0_2;
    for(long i = 1; i <= 4; i++)
        tinsert(tmp3, 2 * (tmp3->val + i));

    tree *tmp4 = t0_3;
    for(long i = 3; i <= 6; i++)
    {
        tree *tmp5 = tinsert(tmp4, 2 * tmp4->val);

        for(int j = 1; j < i; j++)
            tinsert(tmp5, tmp5->val + j);
        tmp4 = tmp4->subtree;
    }

    tree *t0_2_20_200 = tinsert(t0_2_20, 2000);
    tree *t0_2_20_2000 = tinsert(t0_2_20_200, 20000);
    tprint(t0);
    printf("Height of t0: %i\n", theight(t0));
    printf("-----\n");

    // Promotion test cases
    printf("Promoting children of 1000 in t0:\n");
    tdelete(t0, 1000, 'p');
    tprint(t0);
    printf("-----\n");

    printf("Promoting children of 601 in t0:\n");
    tdelete(t0, 601, 'p');
    tprint(t0);
    printf("-----\n");
    
    printf("Promoting children of 60 in t0:\n");
    tdelete(t0, 60, 'p');
    tprint(t0);
    printf("-----\n");

    printf("Promoting children of 20 in t0:\n");
    tdelete(t0, 20, 'p');
    tprint(t0);
    printf("-----\n");

    printf("Promoting children of 20000 in t0:\n");
    tdelete(t0, 20000, 'p');
    tprint(t0);
    printf("-----\n");

    printf("Promoting children of 1002 in t0:\n");
    tdelete(t0, 1002, 'p');
    tprint(t0);
    printf("-----\n");

    printf("Promoting children of 1205 in t0:\n");
    tdelete(t0, 1205, 'p');
    tprint(t0);
    printf("-----\n");

    printf("Promoting children of 1207 in t0:\n");
    tdelete(t0, 1207, 'p');
    tprint(t0);
    printf("Height of t0: %i\n", theight(t0));
    printf("-----\n");

    printf("Deleting from t0 after promotions to check tree structure:\n");
    tdelete(t0, 10002, 't');
    tdelete(t0, 10003, 't');
    tdelete(t0, 42, 't');
    tdelete(t0, 44, 't');
    tdelete(t0, 46, 't');
    tdelete(t0, 30, 't');
    tprint(t0);
    printf("Height of t0: %i\n", theight(t0));

    printf("Freeing t0:\n");
    tfree(&t0);
    tprint(t0);

    tfree(r);
}

void bsts()
{
    printf("Creating b0 manually:\n");
    bst *b0 = bcreaten();
    bst *b0l = bcreatenv(-1);
    bst *b0r = bcreatenv(1);
    b0->left = b0l;
    b0->right = b0r;
    bprint(b0);

    printf("Freeing b0:\n");
    bfree(&b0);
    bprint(b0);

    printf("Creating b1 from array:\n");
    int nums[] = {10, 4, 5, 2, 7, 3, 9, 12, 0, 1, 100, 8, 30, 35, 20, 25, 60, 45, 18, 3};
    bst *b1 = bcreatea(nums, sizeof(nums)/sizeof(nums[0]));
    bprint(b1);

    printf("Searching for 4 in b1:\n");
    bprint(*bstsearch(b1, 4));

    printf("Searching for 8 in b1:\n");
    bprint(*bstsearch(b1, 8)); 

    printf("Searching for 100 in b1:\n");
    bprint(*bstsearch(b1, 100)); 

    printf("Searching for 30 in b1:\n");
    bst **r = bstsearch(b1, 30);
    if(r)
        bprint(*r);

    printf("Height of b1: %i\n", bheight(b1));
    
    printf("Trimming 9 from b1:\n");
    bdelete(b1, 9, 't');
    bprint(b1);

    printf("Trimming 2 from b1:\n");
    bdelete(b1, 2, 't');
    bprint(b1);

    bfree(&b1);
}

void hashtables(int argc, char *argv[])
{
    run_speller(argc, argv);
}