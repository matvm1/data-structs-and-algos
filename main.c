#include "linkedlist.c"

int main(int argc, char *argv[])
{
    int nums[] = {1, 3, 3, 5, 7, 11, 4, -1, -10, -100, 11, 3, 1, 1, 2, 4, 3};
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

    printf("Deleting pos 0:\n   l0:");
    ldeletep(l0, 0);
    lprint(l0);
    printf("   l1: ");
    ldeletep(l1, 0);
    clprint(l1, l1->len + 1);

    printf("Deleting pos mid:\n   l0:");
    ldeletep(l0, l0->len/2);
    lprint(l0);
    printf("   l1: ");
    ldeletep(l1, l1->len/2);
    clprint(l1, l1->len + 1);

    printf("Deleting pos len:\n   l0:");
    ldeletep(l0, l0->len - 1);
    lprint(l0);
    printf("   l1: ");
    ldeletep(l1, l1->len - 1);
    clprint(l1, l1->len + 1);

    printf("Delete all 3s:\n   l0: ");
    ldeletea(l0, 3);
    lprint(l0);
    printf("   l1: ");
    ldeletea(l1, 3);
    clprint(l1, l1->len + 1);

    printf("Delete all 1s:\n   l0: ");
    ldeletea(l0, 1);
    lprint(l0);
    printf("   l1: ");
    ldeletea(l1, 1);
    clprint(l1, l1->len + 1);

    printf("Delete all 4s:\n   l0: ");
    ldeletea(l0, 4);
    lprint(l0);
    printf("   l1: ");
    ldeletea(l1, 4);
    clprint(l1, l1->len + 1);

    printf("Freeing lists:\n    l0: ");
    lfree(l0);
    lprint(l0);
    printf("    l1: ");
    lfree(l1);
    lprint(l1);
}