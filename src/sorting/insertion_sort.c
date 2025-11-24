#include "algorithms.h"

void insertion_sort(int arr[], int len) {
    int i = 0;
    int j = 0;
    int key = 0;
    for (i = 1; i < len; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}
