#include <stdio.h>

/*
 * There are two sorted arrays nums1 and nums2 of size m and n respectively.
 *
 * Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
 *
 * Example 1:
 *
 * nums1 = [1, 3]
 * nums2 = [2]
 *
 * The median is 2.0
 *
 * Example 2:
 *
 * nums1 = [1, 2]
 * nums2 = [3, 4]
 *
 * The median is (2 + 3)/2 = 2.5
 */

int isTargetAMedian(int targetVal, int itemsGreaterThanTarget, int* nums2, int nums2Size) {
	return 0;
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
	for(int i = 0; i < nums1Size; ++i) {
		printf("%i ", isTargetAMedian(nums1[i], nums1Size - i, nums2, nums2Size));
	}
	for(int i = 0; i < nums2Size; ++i) {
		printf("%i ", isTargetAMedian(nums2[i], nums2Size - i, nums1, nums1Size));
	}
	return 0;
}

int main () {
	int num1[] = {1, 2, 3, 4, 7};
	int num2[] = {0, 5, 6, 9};

	printf("median: %f", findMedianSortedArrays(num1, sizeof(num1), num2, sizeof(num2)));
}
