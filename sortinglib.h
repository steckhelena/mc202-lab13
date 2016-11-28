#ifndef LAB13_SORTINGLIB_H
#define LAB13_SORTINGLIB_H

#include <stdlib.h>

void bubble_sort(int *vec, size_t length);

void selection_sort(int *vec, size_t length);

void insertion_sort(int *vec, size_t length);

void merge_sort(int *vec, size_t start, size_t end);

void heap_sort(int *vec, size_t length);

void quick_sort(int *vec, size_t start, size_t end);

#endif //LAB13_SORTINGLIB_H
