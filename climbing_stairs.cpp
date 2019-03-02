/*
You are climbing a stair case. It takes n steps to reach to the top.

Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?

Note: Given n will be a positive integer.

Example 1:

Input: 2
Output: 2
Explanation: There are two ways to climb to the top.
1. 1 step + 1 step
2. 2 steps
Example 2:

Input: 3
Output: 3
Explanation: There are three ways to climb to the top.
1. 1 step + 1 step + 1 step
2. 1 step + 2 steps
3. 2 steps + 1 step
*/


/* Analysis:

After trying some examples, the pattern is fibonacci sequence.

f(1) = 1
f(2) = 2
f(3) = 3
f(4) = 5

f(n) = f(n-1) + f(n-2)

 */

#include <map>
#include <iostream>

int fib(int n) {
    static std::map<int, int> solved;
    solved[0] = 1;
    solved[1] = 1;
    if(solved.find(n) == solved.end()) {
        solved[n] = fib(n-1) + fib(n-2);
        return solved[n];
    } else {
        return solved[n];
    }
}

class Solution {
public:
    int climbStairs(int n) {
        return fib(n);
    }
};

int main() {
    Solution sol;
    std::cout << sol.climbStairs(4) << std::endl;
}

