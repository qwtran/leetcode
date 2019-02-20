#include <vector>
#include <iostream>

/*
Given an array of non-negative integers, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.

Example 1:

Input: [2,3,1,1,4]
Output: true
Explanation: Jump 1 step from index 0 to 1, then 3 steps to the last index.
Example 2:

Input: [3,2,1,0,4]
Output: false
Explanation: You will always arrive at index 3 no matter what. Its maximum
             jump length is 0, which makes it impossible to reach the last index.
*/

class Solution {
public:
    bool canJump(std::vector<int>& nums) {
        if(nums.size() == 1) {
            return true;
        }

        int steps = 0;
        for(int i = nums.size() - 2; i >= 0; --i) {
            ++steps;
            if(nums[i] >= steps) {
                steps = 0;
            }
        }
        
        if(!steps) {
            return true;
        } else {
            return false;
        }
    }
};

int main() {
    Solution solution;
    std::vector<int> nums{3,0,2,0,1,3};
    std::cout << "Can jump? " << solution.canJump(nums) << std::endl;
}
