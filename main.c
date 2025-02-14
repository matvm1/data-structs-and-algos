#include "linkedlist.c"

int main(int argc, char *argv[])
{
    int nums[] = {1, 3, 5, 7, 11, -1, -10, -100, 11, 3, 1, 1};
    printf("Creating list0: ");
    list *l0 = lcreate(nums, sizeof(nums)/sizeof(nums[0]));
    lprint(l0);

    printf("Creating list1: ");
    list *l1 = lcreate(nums, sizeof(nums)/sizeof(nums[0]));
    lprint(l1);

    printf("Making list1 circular: ");
    lmakecirc(l1);
    clprint(l1, l1->len * 2 + 1);

    printf("Printing list1 without reference in first arg: ");
    clprintn(NULL, l1->head, l1->len * 2 + 1);

    printf("Appending 15 to both:\n");
    lappend(l0, 15);
    printf("    l0: ");
    lprint(l0);
    lappend(l1, 15);
    printf("    l1: ");
    clprint(l1, l1->len + 1);

    printf("Searching for -100 in l0: ");
    lprintn(lsearch(l0, -100));

    printf("Searching for -100 in l1: ");
    clprintn(NULL, lsearch(l1, -100), 1);

    printf("Searching for 52 in l0: ");
    lprintn(lsearch(l0, 52));

    printf("Searching for 52 in l1: ");
    clprintn(NULL, lsearch(l1, 52), 1);

    printf("Reversing list0: ");
    lreverse(l0);
    lprint(l0);

    printf("Reversing list1: ");
    lreverse(l1);
    lprint(l1);
    clprint(l1, l1->len * 2 + 1);

    /*printf("Append and then delete 33: ");
    lappend(l, 33);
    ldeletev(l, 33);
    lprint(l);

    printf("Deleting pos 0: ");
    ldeletep(l, 0);
    lprint(l);

    printf("Deleting pos mid: ");
    ldeletep(l, l->len/2);
    lprint(l);

    printf("Deleting pos len: ");
    ldeletep(l, l->len - 1);
    lprint(l);

    printf("Delete all 1s: ");
    ldeletea(l, 1);
    lprint(l);

    printf("Delete all 11s: ");
    ldeletea(l, 11);
    lprint(l);

    printf("Freeing list: ");
    lfree(l);
    lprint(l);  */  
}