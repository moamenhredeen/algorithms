#include <stdio.h>

#include "algorithms.h"


int main() {
    int arr[] = {5, 2, 8, 1, 9};
    insertion_sort(arr, 5);
    printf("Sorted array: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
