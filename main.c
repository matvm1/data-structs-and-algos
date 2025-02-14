#include "linkedlist.c"

int main(int argc, char *argv[])
{
    int nums[] = {1, 3, 5, 7, 11, -1, -10, -100, 11, 3, 1, 1};
    printf("Creating list: ");
    list *l = lcreate(nums, sizeof(nums)/sizeof(nums[0]));
    lprint(l);

    printf("Making list circular: ");
    lmakecirc(l);
    clprint(l, l->len * 2 + 1);

    printf("Printing list without reference in first arg: ");
    clprintn(NULL, l->head, l->len * 2 + 1);

    printf("Appending 15: ");
    //lappend(l, 15);
    lprint(l);

    /*printf("Searching for 52: ");
    lprintn(lsearch(l, 52));

    printf("Reversing the list: ");
    lreverse(l);
    lprint(l);

    printf("Append and then delete 33: ");
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