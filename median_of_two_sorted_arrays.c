#include <stdio.h>
#include <assert.h>

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


enum MedianPosition {
	ODD        = 0,
	EVEN_LEFT  = 1,
	EVEN_RIGHT = 2,
};


/* Given a target index in nums1, this function returns an upper and lower index
 * for nums2. This allows for comparison of the nums1 target to nums2 values located
 * in upper and lower. If target value is smaller or equal than value in lower index AND 
 * target value is larger or equal to value in upper index, target is a median.
 *
 * Function returns -1 for index if out of bounds for nums2.
 */
void
getUpperLowerNum2IndexGivenTarget(
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
	*upper = *lower + 1;
	if(*lower < 0 || *lower >= nums2Size) {
		*lower = -1;
	}
	if(*upper < 0 || *upper >= nums2Size) {
		*upper = -1;
	}
	return;
}

/* Returns a start and end index values for nums1. The index range represents
 * valid locations where the median could reside.
 */
void
validIndexRangeForNums1Size(
		int  nums1Size,          // input
		int  nums2Size,          // input
		enum MedianPosition pos, // input
		int* start,              // output, including start
		int* end)                // output, including end
{
	int total = nums1Size + nums2Size;
	int middle = total / 2;

	if(pos == ODD) {
		*start = nums1Size - middle - 1;
		*end = middle;
	} else if(pos == EVEN_LEFT) {
		*start = middle - nums2Size  - 1;
		*end = total - middle - 1;
	}

	if(*end >= nums1Size) {
		*end = nums1Size - 1;
	}
	if(*end < 0) {
		*end = -1;
	}

	if(*start < 0) {
		*start = 0;
	}
	if(*start >= nums1Size) {
		*start = -1;
	}
}

enum TargetVal {
	MEDIAN_FOUND = 0,
	TOO_HIGH = 1,
	TOO_LOW  = -1,
	UNKNOWN = 999
};

enum TargetVal
isTargetAMedian(int nums1TargetIndex, int* nums1, int nums1Size,  int* nums2, int nums2Size) {
	int lower = 0;
	int upper = 0;
	getUpperLowerNum2IndexGivenTarget(nums1TargetIndex,
			nums1Size,
			nums2Size,
			&lower,
			&upper);

	if(lower != -1) {
		if(nums1[nums1TargetIndex] < nums2[lower]) {
			return TOO_LOW;
		}
	}

	if(upper != -1) {
		if(nums1[nums1TargetIndex] > nums2[upper]) {
			return TOO_HIGH;
		}
	}

	if(lower == -1 && upper == -1) {
		return UNKNOWN;
	}

	return MEDIAN_FOUND;
}

double
findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {

	// 1. Get valid index range for nums1
	// 2. Search nums1 for median using quick search
	// 3. If not in nums1, get valid index range for nums2
	// 4. Search nums2 for median by using quick search

	for(int i = 0; i < nums1Size; ++i) {
		printf("index:%i %i\n", i, isTargetAMedian(i, nums1, nums1Size, nums2, nums2Size));
	}
	for(int i = 0; i < nums2Size; ++i) {
		printf("index:%i %i\n", i, isTargetAMedian(i, nums2, nums2Size, nums1, nums1Size));
	}
	return 0;
}

void
testValidRangeFunction() {
	int start = -1;
	int end = -1;
	validIndexRangeForNums1Size(10, 2, EVEN_LEFT, &start, &end); 

	assert(start == 3);
	assert(end == 5);

	start = -1;
	end = -1;
	validIndexRangeForNums1Size(3, 3, EVEN_LEFT, &start, &end);
	assert(start == 0);
	assert(end == 2);

	start = -1;
	end = -1;
	validIndexRangeForNums1Size(10, 40, EVEN_LEFT, &start, &end);
	assert(start == 0);
	assert(end == 9);

	start = -1;
	end = -1;
	validIndexRangeForNums1Size(3, 4, ODD, &start, &end);
	assert(start == 0);
	assert(end == 2);
}

int
main () {
	testValidRangeFunction();

	int num1[] = {1, 2, 3, 4, 7, 11, 12};
	int num2[] = {0, 5, 6, 9};
	//int num2[] = {0};

	printf("median: %f\n", findMedianSortedArrays(num1, sizeof(num1)/sizeof(int), num2, sizeof(num2)/sizeof(int)));
}
