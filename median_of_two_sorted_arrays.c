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
		int  nums1TargetIndex,   // input
		enum MedianPosition pos, // input
		int  nums1Size,          // input
		int  nums2Size,          // input
		int* lower,              // output
		int* upper)              // output 
{

	if(pos == ODD) {
		int totalSize = nums1Size + nums2Size - 1;
		int itemsGreaterInNums1Array = nums1Size - nums1TargetIndex - 1;
		int itemsGreaterTotal = totalSize / 2;
		*lower = nums2Size - (itemsGreaterTotal - itemsGreaterInNums1Array) - 1;
		*upper = *lower + 1;
	} else if(pos == EVEN_LEFT) {
		int totalSize = nums1Size + nums2Size - 2;
		int itemsGreaterInNums1Array = nums1Size - nums1TargetIndex - 2;
		int itemsGreaterTotal = totalSize / 2;
		*lower = nums2Size - (itemsGreaterTotal - itemsGreaterInNums1Array) - 1;
		*upper = *lower + 1;
	} else if(pos == EVEN_RIGHT) {
		int totalSize = nums1Size + nums2Size - 2;
		int itemsGreaterInNums1Array = nums1Size - nums1TargetIndex - 2;
		int itemsGreaterTotal = totalSize / 2;
		*lower = nums2Size - (itemsGreaterTotal - itemsGreaterInNums1Array);
		*upper = *lower + 1;
	}

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
	} else if(pos == EVEN_RIGHT) {
		*start = middle - nums2Size;
		*end = total - middle;
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
			ODD,
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

int
binarySearchMedian(enum MedianPosition pos,
		int* nums1,
		int  nums1Size,
		int* nums2,
		int  nums2Size)
{
	int start = -1;
	int end   = -1;

	validIndexRangeForNums1Size(nums1Size, nums2Size, pos, &start, &end);

	if((start == -1) || (end == -1)) {
		return -1;
	}

	int mid = -1;
	while(start <= end) {
		mid = (start + end)/2;
		enum TargetVal result = isTargetAMedian(mid, nums1, nums1Size, nums2, nums2Size);
		if(result == TOO_HIGH) {
			end = mid - 1;
		} else if(result == TOO_LOW) {
			start = mid + 1;
		} else if(result == MEDIAN_FOUND) {
			return mid;
		} else if(result == UNKNOWN) {
			assert(0);
		}
	}

	return -1;
}

double
findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {

	// 1. Get valid index range for nums1
	// 2. Search nums1 for median using quick search
	// 3. If not in nums1, get valid index range for nums2
	// 4. Search nums2 for median by using quick search

	int isOdd = (nums1Size + nums2Size) % 2;

	if(isOdd) {
		int medianIndex = binarySearchMedian(ODD, nums1, nums1Size, nums2, nums2Size);

		if(medianIndex != -1) {
			return nums1[medianIndex];
		}

		medianIndex = binarySearchMedian(ODD, nums2, nums2Size, nums1, nums1Size);

		if(medianIndex != -1) {
			return nums2[medianIndex];
		} else {
			assert(0);
		}
	} else {

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
	validIndexRangeForNums1Size(8, 4, EVEN_LEFT, &start, &end);
	assert(start == 1);
	assert(end == 5);

	start = -1;
	end = -1;
	validIndexRangeForNums1Size(0, 4, EVEN_LEFT, &start, &end);
	assert(start == -1);
	assert(end == -1);

	start = -1;
	end = -1;
	validIndexRangeForNums1Size(4, 0, EVEN_LEFT, &start, &end);
	assert(start == 1);
	assert(end == 1);

	start = -1;
	end = -1;
	validIndexRangeForNums1Size(2, 0, EVEN_LEFT, &start, &end);
	assert(start == 0);
	assert(end == 0);

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
	validIndexRangeForNums1Size(10, 2, EVEN_RIGHT, &start, &end);
	assert(start == 4);
	assert(end == 6);

	start = -1;
	end = -1;
	validIndexRangeForNums1Size(8, 4, EVEN_RIGHT, &start, &end);
	assert(start == 2);
	assert(end == 6);

	start = -1;
	end = -1;
	validIndexRangeForNums1Size(0, 4, EVEN_RIGHT, &start, &end);
	assert(start == -1);
	assert(end == -1);

	start = -1;
	end = -1;
	validIndexRangeForNums1Size(4, 0, EVEN_RIGHT, &start, &end);
	assert(start == 2);
	assert(end == 2);

	start = -1;
	end = -1;
	validIndexRangeForNums1Size(2, 0, EVEN_RIGHT, &start, &end);
	assert(start == 1);
	assert(end == 1);

	start = -1;
	end = -1;
	validIndexRangeForNums1Size(3, 3, EVEN_RIGHT, &start, &end);
	assert(start == 0);
	assert(end == 2);

	start = -1;
	end = -1;
	validIndexRangeForNums1Size(10, 40, EVEN_RIGHT, &start, &end);
	assert(start == 0);
	assert(end == 9);



	start = -1;
	end = -1;
	validIndexRangeForNums1Size(3, 4, ODD, &start, &end);
	assert(start == 0);
	assert(end == 2);

	start = -1;
	end = -1;
	validIndexRangeForNums1Size(9, 4, ODD, &start, &end);
	assert(start == 2);
	assert(end == 6);

	start = -1;
	end = -1;
	validIndexRangeForNums1Size(7, 0, ODD, &start, &end);
	assert(start == 3);
	assert(end == 3);

	start = -1;
	end = -1;
	validIndexRangeForNums1Size(0, 5, ODD, &start, &end);
	assert(start == -1);
	assert(end == -1);

	start = -1;
	end = -1;
	validIndexRangeForNums1Size(0, 0, ODD, &start, &end);
	assert(start == -1);
	assert(end == -1);

	start = -1;
	end = -1;
	validIndexRangeForNums1Size(1, 4, ODD, &start, &end);
	assert(start == 0);
	assert(end == 0);

	printf("validIndexRangeForNums1Size passed\n");
}

void
testUpperLowerIndexVals() {
	int upper = 999;
	int lower = 999;

	getUpperLowerNum2IndexGivenTarget(0, ODD, 5, 2, &lower, &upper);
	assert(lower == -1);
	assert(upper == -1);

	upper = 999;
	lower = 999;
	getUpperLowerNum2IndexGivenTarget(1, ODD, 5, 2, &lower, &upper);
	assert(lower == 1);
	assert(upper == -1);

	upper = 999;
	lower = 999;
	getUpperLowerNum2IndexGivenTarget(2, ODD, 5, 2, &lower, &upper);
	assert(lower == 0);
	assert(upper == 1);

	upper = 999;
	lower = 999;
	getUpperLowerNum2IndexGivenTarget(3, ODD, 5, 2, &lower, &upper);
	assert(lower == -1);
	assert(upper == 0);

	upper = 999;
	lower = 999;
	getUpperLowerNum2IndexGivenTarget(4, ODD, 5, 2, &lower, &upper);
	assert(lower == -1);
	assert(upper == -1);



	upper = 999;
	lower = 999;
	getUpperLowerNum2IndexGivenTarget(0, EVEN_LEFT, 4, 2, &lower, &upper);
	assert(lower == 1);
	assert(upper == -1);

	upper = 999;
	lower = 999;
	getUpperLowerNum2IndexGivenTarget(1, EVEN_LEFT, 4, 2, &lower, &upper);
	assert(lower == 0);
	assert(upper == 1);

	upper = 999;
	lower = 999;
	getUpperLowerNum2IndexGivenTarget(2, EVEN_LEFT, 4, 2, &lower, &upper);
	assert(lower == -1);
	assert(upper == 0);

	upper = 999;
	lower = 999;
	getUpperLowerNum2IndexGivenTarget(3, EVEN_LEFT, 4, 2, &lower, &upper);
	assert(lower == -1);
	assert(upper == -1);



	upper = 999;
	lower = 999;
	getUpperLowerNum2IndexGivenTarget(0, EVEN_RIGHT, 4, 2, &lower, &upper);
	assert(lower == -1);
	assert(upper == -1);

	upper = 999;
	lower = 999;
	getUpperLowerNum2IndexGivenTarget(1, EVEN_RIGHT, 4, 2, &lower, &upper);
	assert(lower == 1);
	assert(upper == -1);

	upper = 999;
	lower = 999;
	getUpperLowerNum2IndexGivenTarget(2, EVEN_RIGHT, 4, 2, &lower, &upper);
	assert(lower == 0);
	assert(upper == 1);

	upper = 999;
	lower = 999;
	getUpperLowerNum2IndexGivenTarget(3, EVEN_RIGHT, 4, 2, &lower, &upper);
	assert(lower == -1);
	assert(upper == 0);

	printf("getUpperLowerNum2IndexGivenTarget passed\n");
}

#define SIZE_OF(array) (sizeof(array)/sizeof(array[0]))

int
main () {
	testValidRangeFunction();
	testUpperLowerIndexVals();

	int num1[] = {1, 2, 3, 4, 7, 11, 12};
	int num2[] = {0, 5, 6, 9};
	assert(findMedianSortedArrays(num1, SIZE_OF(num1), num2, SIZE_OF(num2)) == 5.0);
	assert(findMedianSortedArrays(num2, SIZE_OF(num2), num1, SIZE_OF(num1)) == 5.0);

	int num3[] = {1, 2, 4, 5};
	int num4[] = {3};
	assert(findMedianSortedArrays(num3, SIZE_OF(num3), num4, SIZE_OF(num4)) == 3.0);
	assert(findMedianSortedArrays(num4, SIZE_OF(num4), num3, SIZE_OF(num3)) == 3.0);

	assert(findMedianSortedArrays(num1, SIZE_OF(num1), num3, SIZE_OF(num3)) == 4.0);
	assert(findMedianSortedArrays(num3, SIZE_OF(num3), num1, SIZE_OF(num1)) == 4.0);

	printf("array test pass\n");
}
