#include <iostream>
#include<math.h>
#include<cstring>
#include<string>
#include<unordered_map>
#include<vector>
#include "map"

using namespace std;

class Solution {
	// 1.22
 public:

	int maxProfit(vector<int>& prices) {
		if (prices.empty()) return 0;
		int minV = prices[0];
		int res = 0;

		for (int i = 1; i < prices.size(); i++) {
			if (prices[i] < minV) {
				minV = prices[i];
			} else if (prices[i] - minV > res) {
				res = prices[i] - minV;
			}
		}
		return res;
	}


	int subarraySum(vector<int>& nums, int k) {
		int curSum = 0;
		map<int, int> map;
		int res = 0;
		map[0] = 1;

		for (int num : nums) {
			curSum += num;
			res += map[curSum - k];
			map[curSum]++;
		}
		return res;
	}


	int lengthOfLongestSubstring(string s) {
		/*
		 * sliding window, O(n), O(1)
		 */
		int window[256] = {};
		int left = 0;
		int right = 0;
		int res = 0;

		while (right < s.size()) {
			char r = s[right];
			window[r]++;
			r++;

			while (window[r] > 1) {
				char l = s[left];
				l++;
				window[l]--;
			}
			res = max(res, right - left);
		}
		return res;
	}
};

int main() {

	Solution s;
	s.lengthOfLongestSubstring("abcabcbb");

}
