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



/* Given a target index in nums1, this function returns an upper and lower index
 * for nums2. This allows for comparison of the nums1 target to nums2 values located
 * in upper and lower. If target value is smaller or equal than value in lower index AND 
 * target value is larger or equal to value in upper index, target is a median.
 *
 * Function returns -1 for index if out of bounds for nums2.
 */
void
getNums2ComparisonIndex(
		int  nums1TargetIndex,    // input
		int  nums1Size,           // input
		int  nums2Size,           // input
		int* lowerNums2Index,     // output, odd - lower index, even - left side lower
		int* upperNums2Index,     // output, odd - upper index, even - left side upper
		int* evenLowerNums2Index, // output, odd - ignore, even - right side lower
		int* evenUpperNums2Index) // output, odd - ignore, even - right side upper
{
	int totalSize = nums1Size + nums2Size;
	int itemsGreaterInNums1Array = nums1Size - nums1TargetIndex - 1;
	int itemsGreaterTotal = totalSize / 2;

	*lowerNums2Index = nums2Size - (itemsGreaterTotal - itemsGreaterInNums1Array) - 1;
	*upperNums2Index = *lowerNums2Index + 1;
	if(*lowerNums2Index < 0 || *lowerNums2Index >= nums2Size) {
		*lowerNums2Index = -1;
	}
	if(*upperNums2Index < 0 || *upperNums2Index >= nums2Size) {
		*upperNums2Index = -1;
	}

	// even only
	if(totalSize % 2 == 0) {
		*evenLowerNums2Index = *upperNums2Index;
		// TODO: clunky logic
		if(*evenLowerNums2Index != -1) {
			if(*evenLowerNums2Index + 1 < nums2Size) {
				*evenUpperNums2Index = *evenLowerNums2Index + 1;
			} else {
				*evenUpperNums2Index = -1;
			}
		} else {
			*evenUpperNums2Index = -1;
		}
	}
	return;
}

/* Returns a start and end index values for nums1. The index range represents
 * valid locations where the median could reside.
 */
void
validIndexRangeForNums1Size(
		int  nums1Size,   // input
		int  nums2Size,   // input
		int* start,       // output, including start
		int* end)         // output, including end
{
	int total = nums1Size + nums2Size;
	int middle = total / 2;

	*start = nums1Size - middle - 1;
	if(*start < 0) {
		*start = 0;
	}
	if(*start >= nums1Size) {
		*start = -1;
	}

	*end = middle;
	if(*end >= nums1Size) {
		*end = nums1Size - 1;
	}
	if(*end < 0) {
		*end = -1;
	}
}

enum TargetVal {
	UNKNOWN                  = 0,
	TOO_HIGH                 = 1,
	TOO_LOW                  = 2,
	MEDIAN_FOUND             = 3,

	EVEN_LEFTFOUND_RIGHTHIGH = 4,
	EVEN_LEFTFOUND_RIGHTLOW  = 5,
	EVEN_LEFTHIGH_RIGHTFOUND = 6,
	EVEN_LEFTLOW_RIGHTFOUND  = 7,
};

enum TargetVal
medianTest(int nums1TargetIndex,
		int lower,
		int upper,
		int* nums1,
		int* nums2)
{
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

enum TargetVal
isTargetAMedian(int nums1TargetIndex, int* nums1, int nums1Size,  int* nums2, int nums2Size) {
	int lower = 0;
	int upper = 0;
	int evenLower = 0;
	int evenUpper = 0;
	
	int totalSize = nums1Size + nums2Size;

	getNums2ComparisonIndex(nums1TargetIndex,
			nums1Size,
			nums2Size,
			&lower,
			&upper,
			&evenLower,
			&evenUpper);

	enum TargetVal result = medianTest(nums1TargetIndex,
			lower,
			upper,
			nums1,
			nums2);

	if(totalSize % 2) {
		return result;
	}

	enum TargetVal evenLeft  = result;
	enum TargetVal evenRight= medianTest(nums1TargetIndex,
			evenLower,
			evenUpper,
			nums1,
			nums2);
printf("target %i\tevenLower %i\tevenUpper %i\tleft %i\tright %i\n", nums1TargetIndex, evenLower, evenUpper, evenLeft, evenRight);
	if((evenLeft == TOO_HIGH) && (evenRight == TOO_HIGH)) {
		return TOO_HIGH;
	} else if((evenLeft == TOO_LOW) && (evenRight == TOO_LOW)) {
		return TOO_LOW;
	} else if((evenLeft == MEDIAN_FOUND) && (evenRight == TOO_HIGH)) {
		return EVEN_LEFTFOUND_RIGHTHIGH;
	} else if((evenLeft == MEDIAN_FOUND) && (evenRight == TOO_LOW)) {
		return EVEN_LEFTFOUND_RIGHTLOW;
	} else if((evenLeft == TOO_HIGH) && (evenRight == MEDIAN_FOUND)) {
		return EVEN_LEFTHIGH_RIGHTFOUND;
	} else if((evenLeft == TOO_LOW) && (evenRight == MEDIAN_FOUND)) {
		return EVEN_LEFTLOW_RIGHTFOUND;
	} else {
		return UNKNOWN;
	}
}

void
quickSearchMedian(int nums1Start,
		int nums1End,
		int* nums1,
		int nums1Size,
		int* nums2,
		int nums2Size,
		int** returnVal,
		int** evenReturnVal)
{
	int rightFound = 0;
	int leftFound = 0;

	while(nums1Start <= nums1End) {
		int mid = (nums1Start + nums1End)/2;

		enum TargetVal result =
			isTargetAMedian(mid, nums1, nums1Size, nums2, nums2Size);

		if(result == TOO_LOW) {
			nums1Start = mid + 1;
		} else if(result == TOO_HIGH) {
			nums1End = mid - 1;
		} else if(result == MEDIAN_FOUND) {
			**returnVal = nums1[mid];
			return;
		} else if(result == EVEN_LEFTFOUND_RIGHTHIGH) {
			leftFound = 1;
			**returnVal = nums1[mid];
			if(rightFound && leftFound) return;
			nums1End = mid - 1;
		} else if(result == EVEN_LEFTFOUND_RIGHTLOW) { 
			leftFound = 1;
			**returnVal = nums1[mid];
			if(rightFound && leftFound) return;
			nums1Start = mid + 1;
		} else if(result == EVEN_LEFTHIGH_RIGHTFOUND) { 
			rightFound = 1;
			**evenReturnVal = nums1[mid];
			if(rightFound && leftFound) return;
			nums1End = mid - 1;
		} else if(result == EVEN_LEFTLOW_RIGHTFOUND) { 
			rightFound = 1;
			**evenReturnVal = nums1[mid];
			if(rightFound && leftFound) return;
			nums1Start = mid + 1;
		} else if(result == UNKNOWN) {
			// Need to handle this case
			assert(0);
		}
	}

	if((nums1Size + nums2Size) % 2) {
		*returnVal = 0;
		*evenReturnVal = 0;
		return;
	}

	if(!rightFound) {
		*evenReturnVal = 0;
	}

	if(!leftFound) {
		*returnVal = 0;
	}
}

double
findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {

	// 1. Get valid index range for nums1
	// 2. Search nums1 for median by using quick search
	// 3. If not in nums1, get valid index range for nums2
	// 4. Search nums2 for median by using quick search

	int totalSize = nums1Size + nums2Size;

	int start = -1;
	int end   = -1;

	int rightFound = 0;
	int leftFound = 0;

	validIndexRangeForNums1Size(nums1Size,
			nums2Size,
			&start,
			&end);

	int result = 0;
	int* resultPtr = &result;
	int evenResult = 0;
	int* evenResultPtr = &evenResult;

	quickSearchMedian(start, end, nums1, nums1Size, nums2, nums2Size, &resultPtr, &evenResultPtr);
	if(resultPtr != 0) {
		if(totalSize % 2) {
			return result;
		}
		if(resultPtr) {
			leftFound = 1;
		}
		if(evenResultPtr) {
			rightFound = 1;
		}
		if(rightFound && leftFound) {
			return (result + evenResult) / 2.0;
		}
	}

	validIndexRangeForNums1Size(nums2Size,
			nums1Size,
			&start,
			&end);

	resultPtr = &result;
	evenResultPtr = &evenResult;

	quickSearchMedian(start, end, nums2, nums2Size, nums1, nums1Size, &resultPtr, &evenResultPtr);
	if(resultPtr != 0) {
		if(totalSize % 2) {
			return result;
		}
		if(resultPtr) {
			leftFound = 1;
		}
		if(evenResultPtr) {
			rightFound = 1;
		}
		if(rightFound && leftFound) {
			return (result + evenResult) / 2.0;
		}
	}

	return 0;
}

void
testValidRangeFunction() {
	int start = -1;
	int end = -1;
	validIndexRangeForNums1Size(10, 2, &start, &end); 
	assert(start == 3);
	assert(end == 6);

	start = -1;
	end = -1;
	validIndexRangeForNums1Size(3, 3, &start, &end);
	assert(start == 0);
	assert(end == 2);

	start = -1;
	end = -1;
	validIndexRangeForNums1Size(3, 4, &start, &end);
	assert(start == 0);
	assert(end == 2);

	start = -1;
	end = -1;
	validIndexRangeForNums1Size(1, 4, &start, &end);
	assert(start == 0);
	assert(end == 0);

	start = -1;
	end = -1;
	validIndexRangeForNums1Size(0, 4, &start, &end);
	assert(start == -1);
	assert(end == -1);

	printf("pass\n");
}

int
main () {
	testValidRangeFunction();

	int num1[] = {1, 2, 3, 4};
	int num2[] = {5, 6, 7, 8, 9, 10};

	printf("median: %f\n", findMedianSortedArrays(num1, sizeof(num1)/sizeof(int), num2, sizeof(num2)/sizeof(int)));
}
