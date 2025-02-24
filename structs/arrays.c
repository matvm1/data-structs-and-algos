#include "structs.h"

// Swaps the values of a and b in memory
void swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

// Sort arr using sortalgo_callback
// sortalgo_callback functions: selection, bubble, insertion, merge
void arrsort(int *arr, int len, sortalgo_callback sortalgo_callback)
{
    if(!arr || len < 1)
        return;

    sortalgo_callback(arr, len);
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

// Merges subarray[start...(mid - 1)] and subarray[mid...end] into arr[start...end]
static void arrmerge(int arr[], int start, int end, int mid)
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

// Merge sort helper
static void mergesort_h(int *arr, int start, int end, int d)
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

// Merge sorts arr
// Time-complexity:
//    Theta(n log n)
// Space-Complexity: O(n)
void merge(int *arr, int len)
{
    mergesort_h(arr, 0, len - 1, 1);
}

// Searches for val in arr and returns the index of the first instance. Returns -1 if arr NULL or val is not found
// searchalgo_callback functions: linear, binary
int arrsearch(int *arr, int len, int val, searchalgo_callback searchalgo_callback)
{
    if(!arr || len < 1)
        return -1;

    return searchalgo_callback(arr, len, val);
}

// Brute search for val in arr
// Theta(n)
static int linear(int *arr, int len, int val)
{
    int i = 0;
    while(i < len)
    {
        if(arr[i] == val)
            return i;
        ++i;
    }

    return -1;
}

// Binary search helper
static int binary_h(int *arr, int start, int end, int val)
{
    if(start == end && val != arr[start])
        return -1;
        
    int mid = (end - start + 1)/2 + start;

    if(val == arr[mid])
        return mid;

    if(val < arr[mid])
        return binary_h(arr, start, mid - 1, val);
    else
        return binary_h(arr, mid + 1, end, val); 
}

// Searches for val in arr and returns the index of the first instance. Returns -1 if arr NULL or val is not found
// arr must be sorted
// O(log n)
// Omega(1)
static int binary(int *arr, int len, int val)
{
    if(!arr || len < 0)
        return -1;

    return binary_h(arr, 0, len - 1, val);
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