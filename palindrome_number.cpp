#include <vector>
#include <stdio.h>

class Solution {
public:
    bool isPalindrome(int x) {
        if(x < 0) return false;
        std::vector<int> intList;
        while(x != 0) {
            intList.push_back(x % 10);
            x /= 10;
        }
        int i = 0;
        int j = intList.size() - 1;
        while(i <= j) {
            if(intList[i++] != intList[j--]) {
                return false;
            }
        }
        return true;
    }
};

int main() {
	Solution solution;
	printf("%i\n", solution.isPalindrome(123));
	printf("%i\n", solution.isPalindrome(12321));
	return 0;
}
