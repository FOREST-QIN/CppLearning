#include <iostream>
#include<math.h>
#include<cstring>
#include<string>

using namespace std;

class Solution {
	// 1.22
 public:
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
