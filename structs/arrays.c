#include "structs.h"

void arrmerge(int arr[], int start, int end, int mid);

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
// Time-Complexity:
//   O(n^2)
//   Omega(n) if already sorted
// Space-Complexity: O(1)
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

// Merge sort helper
void mergesort_h(int *arr, int start, int end, int d)
{
    if(start < 0 || end < 0)
        return;
    if(start == end || end < start)
        return;

    int mid = (end - start + 1)/2 + start;

    mergesort_h(arr, start, mid - 1, d + 1);
    mergesort_h(arr, mid, end, d + 1);

    arrmerge(arr, start, end, mid);
}

// Merges subarray[start...(mid - 1)] and subarray[mid...end] into arr[start...end]
void arrmerge(int arr[], int start, int end, int mid)
{
    if(end - start < 1)
        return;

    int len1 = mid - start;
    int len2 = end - mid + 1;

    int arr1[len1];
    int arr2[len2];

    for(int i = 0; i < len1; i++)
        arr1[i] = arr[i + start];

    for(int i = 0; i < len2; i++)
        arr2[i] = arr[i + mid];

    int i = 0;
    int j = 0;
    while(i < len1 && j < len2)
    {
        while(i < len1 && j < len2 && arr1[i] <= arr2[j])
        {
            arr[i + j + start] = arr1[i];
            i++;
        }
        
        while(i < len1 && j < len2 && arr2[j] <= arr1[i])
        {
            arr[i + j + start] = arr2[j];
            j++;
        }
    }

    while(i < len1)
    {
        arr[i + j + start] = arr1[i];
        i++;
    }

    while(j < len2)
    {
        arr[i + j + start] = arr2[j];
        j++;
    }
}

// Merge sorts arr
// Time-complexity:
//    Theta(n log n)
// Space-Complexity: O(n)
void merge(int *arr, int len)
{
    mergesort_h(arr, 0, len - 1, 1);
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