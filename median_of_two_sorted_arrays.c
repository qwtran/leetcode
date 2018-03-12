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

void
calculateLowerUpperIndex(
		int  nums1TargetIndex, // input
		int  nums1Size,        // input
		int  nums2Size,        // input
		int* lower,            // output
		int* upper)            // output 
{
	int totalSize = nums1Size + nums2Size;
	int itemsGreaterInNums1Array = nums1Size - nums1TargetIndex - 1;
	int itemsGreaterTotal = totalSize / 2;

	*lower = nums2Size - (itemsGreaterTotal - itemsGreaterInNums1Array) - 1;
	if(*lower < 0 || *lower >= nums2Size) {
		*lower = -1;
	}
	*upper = *lower + 1;
	if(*upper < 0 || *upper >= nums2Size) {
		*upper = -1;
	}
	return;
}

int
isTargetAMedian(int nums1TargetIndex, int* nums1, int nums1Size,  int* nums2, int nums2Size) {
	int lower = 0;
	int upper = 0;
	calculateLowerUpperIndex(nums1TargetIndex, nums1Size, nums2Size, &lower, &upper);

	if(lower != -1) {
		if(nums1[nums1TargetIndex] < nums2[lower]) {
			return 0;
		}
	}

	if(upper != -1) {
		if(nums1[nums1TargetIndex] > nums2[upper]) {
			return 0;
		}
	}

	if(lower == -1 && upper == -1) {
		return 0;
	}

	return 1;
}

double
findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
	for(int i = 0; i < nums1Size; ++i) {
		printf("index:%i  %i\n", i, isTargetAMedian(i, nums1, nums1Size, nums2, nums2Size));
	}
	for(int i = 0; i < nums2Size; ++i) {
		printf("index:%i %i\n", i, isTargetAMedian(i, nums2, nums2Size, nums1, nums1Size));
	}
	return 0;
}

int
main () {
	int num1[] = {1, 2, 3, 4, 7, 11};
	//int num2[] = {0, 5, 6, 9};
	int num2[] = {0};

	printf("median: %f\n", findMedianSortedArrays(num1, sizeof(num1)/sizeof(int), num2, sizeof(num2)/sizeof(int)));
}
