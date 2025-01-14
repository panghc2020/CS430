//
// Created by 庞海臣 on 2021/5/29.
//
#include "binary_search.h"

#include <iostream>
#include <memory>

/***
 * Exercises 2.3-4
 * @param A
 * @param length
 */
void insertion_sort_recursive(int* A, int length) {
    if (length <= 1) {
        return;
    }

    insertion_sort_recursive(A, length - 1);

    int insertIndex = length - 1;
    int key = A[insertIndex];
    while (insertIndex > 0 && key < A[insertIndex - 1]) {
        A[insertIndex] = A[insertIndex - 1];
        --insertIndex;
    }
    A[insertIndex] = key;
}

/***
 * Exercises 2.3-2
 * @param A
 * @param p
 * @param q
 * @param r
 */
void merge(int* A, int p, int q, int r) {

    // copy the left part to a new alloc memory
    int leftHalfElementCount = q - p;
    int* leftStart = (int*)malloc(sizeof(int) * leftHalfElementCount);
    memcpy(leftStart, A + p, sizeof(int) * leftHalfElementCount);

    // right part use the original array memory
    int rightHalfElementCount = r - q;
    int* rightStart = A + q;

    int leftHalfElementTraveled = 0;
    int rightHalfElementTraveled = 0;

    // the merge target is the begin of the original left part, we have made a
    // copy of the left part, so we don't worry about overriding.
    int* target = A + p;

    // if the two part all have element untraveled, we compare them
    while (leftHalfElementTraveled < leftHalfElementCount &&
           rightHalfElementTraveled < rightHalfElementCount) {

        if (leftStart[leftHalfElementTraveled] <=
            rightStart[rightHalfElementTraveled]) {
            *(target++) = leftStart[leftHalfElementTraveled++];
        } else {
            *(target++) = rightStart[rightHalfElementTraveled++];
        }
    }

    // if the right part exhaust it's elements, we copy all left elements of
    // the left part to the target, if the left part exhaust it's elements, we
    // do nothing, because it's already sorted in the target
    if (rightHalfElementTraveled == rightHalfElementCount) {
        memcpy(target,
               leftStart + leftHalfElementTraveled,
               sizeof(int) * (leftHalfElementCount - leftHalfElementTraveled));
    }

    // free the left copy
    free(leftStart);
}

void merge_sort(int* A, int p, int r) {
    if (r - p > 1) {
        int q = (p + r) / 2;
        merge_sort(A, p, q);
        merge_sort(A, q, r);
        merge(A, p, q, r);
    }
}

/***
 * Exercises 2.3-7
 * @param A
 * @param length
 * @param target
 * @return
 */
bool set_two_element_sum_equal_to(int* A, int length, int target) {
    if (length < 2) {
        return false;
    }

    // O(nlgn)
    merge_sort(A, 0, length);

    // n times
    for (int i = 0; i < length; i++) {
        // O(lgn)
        int j = binary_search(A, 0, length, target - A[i]);
        if (j != -1 && j != i) {
            std::cout << A[i] << " + " << A[j] << " == " << target << std::endl;
            return true;
        }
    }

    return false;
}

int main() {
    int arr[] = {2, 4, 8, 5, 1};

    int length = sizeof(arr) / sizeof(arr[0]);

    printf("Inputs: ");
    for (int i = 0; i < length; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    if (set_two_element_sum_equal_to(arr, 5, 7)) {
        std::cout << "Found" << std::endl;
    } else {
        std::cout << "Not Found" << std::endl;
    }
}