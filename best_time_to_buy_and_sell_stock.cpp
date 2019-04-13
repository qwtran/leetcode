/*

Best Time to Buy and Sell Stock

Say you have an array for which the ith element is the price of a given stock on day i.

If you were only permitted to complete at most one transaction (i.e., buy one and sell one share of the stock), design an algorithm to find the maximum profit.

Note that you cannot sell a stock before you buy one.

Example 1:

Input: [7,1,5,3,6,4]
Output: 5
Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
Not 7-1 = 6, as selling price needs to be larger than buying price.

Example 2:

Input: [7,6,4,3,1]
Output: 0
Explanation: In this case, no transaction is done, i.e. max profit = 0.
*/

#include <vector>
#include <iostream>
#include <climits>

class Solution {
public:
int maxProfit(std::vector<int>& prices) {
	int lowestPrice = INT_MAX;
	int highestProfit = 0;

	for(const auto& i : prices) {
		// Replace lowest cost if found and continue searching
		if(i < lowestPrice) {
			lowestPrice = i;
			continue;
		}
		// Calculate profile
		int profit = i - lowestPrice;
		if(profit > highestProfit) {
			highestProfit = profit;
		}
	}
	return highestProfit;
}
};

int main() {
	//std::vector<int> prices{7,1,5,3,6,4};
	std::vector<int> prices{7,6,4,3,1};
	Solution sol;
	std::cout << "result: " << sol.maxProfit(prices) << std::endl;

}
