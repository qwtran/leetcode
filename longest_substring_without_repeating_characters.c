#include <stdio.h>
#include <string.h>

int max(int a, int b) {
	return (a > b) ? a : b;
}


int lengthOfLongestSubstring(char* s) {
	int map[128];
	int length = 0;
	memset(map, 0, sizeof(map));

	char* start = s;
	char* end   = s;

	if(*start == '\0') {
		return length;
	} else {
		map[(int) *start] = 1;
		end = end + sizeof(char);
		length = 1;
	}


	while(*end != '\0') {
		// Test if end pointer is a repeat char
		if(map[(int) *end] != 1) {
			// not a repeat, add end val to array
			map[(int) *end] = 1;
			
			// advance end pointer
			end = end + sizeof(char);
			
			// calculate length
			length = max(length, (int) (end - start)/sizeof(char));
		} else {
			// is a repeat, remove start val from arrary
			map[(int) *start] = 0;
			
			// advance start pointer
			start = start + sizeof(char);
		}
	}

	return length;
}

int main() {
	char t[] = "pwwkew";
	int i = lengthOfLongestSubstring(t);
	printf("length: %i\n", i);
}
