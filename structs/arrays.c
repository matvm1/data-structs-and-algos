#include "structs.h"

void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// Sort arr using algo_callback
// algo_callback functions: selection, bubble, insertion, merge
void arrsort(int *arr, int len, algo_callback algo_callback)
{
    if(!arr)
        return;

    algo_callback(arr, len);
}

// Runs selection sort on arr
// Time-Complexity:
//    Theta(n^2)
// Space-Complexity: O(1)
static void selection(int *arr, int len)
{
    for(int i = 0; i < len; i++)
    {
        int max = 0;
        for(int j = 0; j < len - i; j++)
            if(arr[j] > arr[max])
                max = j;

        swap(&arr[len - i], &arr[max]);
    }
}

// Run bubble sort on arr
// Time-Complexity:
//    O(n^2)
//    Omega(n) (if already sorted)
// Space-Complexity: O(1)
static void bubble(int *arr, int len)
{
    for(int i = 0; i < len; i++)
    {
        int swaps = 0;
        for(int j = 0; j < len - i - 1; j++)
        {
            if(arr[i] > arr[j])
            {
                swap(&arr[i], &arr[j]);
                swaps++;
            }
        }

        if(!swaps)
            return;
    }
}

// Insertion sorts arr
static void insertion(int *arr, int len)
{
    for(int i = 1; i < len; i++)
    {
        int j = i - 1;
        int curr = arr[i];
        while(j >= 0 && curr < arr[j])
        {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = curr;
    }
}

// Prints an array
void arrprint(int *arr, int len)
{
    if(!arr)
    {
        printf("NULL array");
        return;
    }

    printf("{");
    for(int i = 0; i < len - 1; i++)
        printf("%i, ", arr[i]);
    printf("%i}\n", arr[len - 1]);
}