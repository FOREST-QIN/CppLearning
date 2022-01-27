//
// Created by Forrest on 1/26/22.
//

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <math.h>
#include

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
 public:
	int sum = 0;
	int rangeSumBST(TreeNode *root, int low, int high) {
		if (root == nullptr) return 0;
		range(root, low, high);
		return sum;
	}

	void range(TreeNode*root, int low, int high) {
		if (root == nullptr) return;

		if (root->val >= low && root->val <= high) sum += root->val;
		if (root->val < high) range(root->right, low, high);
		if (root->val > low) range(root->left, low, high);
	}

	vector<int> topKFrequent(vector<int> &nums, int k) {
		unordered_map<int, int> counts;
		priority_queue<int, vector<int>, greater<int>> max_k;
		for (int num : nums) {
			counts[num]++;
		}
		for (auto &i : counts) {
			max_k.push(i.second);
			while (max_k.size() > k) max_k.pop();
		}
		vector<int> res;
		for (auto &i : counts) {
			if (i.second >= max_k.top()) res.push_back(i.first);
		}
		return res;
	}

	vector<vector<int>> verticalOrder(TreeNode *root) {
		vector<vector<int>> res;
		if (root == nullptr) return res;
		map<int, vector<int>> map;
		queue<pair<TreeNode *, int>> q;
		q.push(make_pair(root, 0));

		while (!q.empty()) {
			int size = q.size();

			for (int i = 0; i < size; i++) {
				TreeNode *cur = q.front().first;
				int weight = q.front().second;
				q.pop();
				map[weight].push_back(cur->val);
				if (cur->left) {
					q.push(make_pair(cur->left, weight - 1));
				}
				if (cur->right) {
					q.push(make_pair(cur->right, weight + 1));
				}
			}
		}
		for (auto &v : map) {
			res.push_back(v.second);
		}
		return res;
	}

	int uniqueLetterString(string s) {
		int sum = 0;
		int cur = 0;
		int m = s.length();
		int last[26] = {};
		int prev[26] = {};
		for (int i = 0; i < 26; i++) {
			last[i] = -1;
			prev[i] = -1;
		}

		for (int i = 0; i < s.length(); i++) {
			char ch = s[i];
			int l = last[ch - 'A'] - prev[ch - 'A'];
			int f = i - last[ch - 'A'] - 1;
			cur += f - l + 1;
			sum += cur;
			prev[ch - 'A'] = last[ch - 'A'];
			last[ch - 'A'] = i;
		}
		return sum;
	}

	int search(vector<int> &nums, int target) {
		if (nums.empty()) return -1;
		return binarySearch(nums, 0, nums.size() - 1, target);
	}

	int binarySearch(vector<int> &nums, int left, int right, int target) {
		if (left > right) return -1;
		if (left == right) return nums[left] == target ? left : -1;

		if (nums[left] > nums[right]) {
			int mid = left + (right - left) / 2;
			int lRes = binarySearch(nums, left, mid, target);
			int rRes = binarySearch(nums, mid + 1, right, target);
			return lRes == -1 ? rRes : lRes;
		}
		while (left <= right) {
			int mid = left + (right - left) / 2;
			if (target == nums[mid]) {
				return mid;
			} else if (target > nums[mid]) {
				left = mid + 1;
			} else {
				right = mid - 1;
			}
		}
		return -1;
	}

	vector<string> letterCombinations(string digits) {
		vector<string> res;
		if (digits.empty()) return res;
		unordered_map<char, string> map;
		getMap(digits, map);
		string prefix;
		dfs(digits, 0, prefix, res, map);
		return res;
	}

	void dfs(string &digits, int index, string &prefix, vector<string> &res, unordered_map<char, string> &map) {
		if (index == digits.size()) {
			res.push_back(string(prefix));
			return;
		}

		for (char ch : map[digits[index]]) {
			prefix.push_back(ch);
			dfs(digits, index + 1, prefix, res, map);
			prefix.pop_back();
		}
	}

	void getMap(string &digits, unordered_map<char, string> &map) {
		map['2'] = "abc";
		map['3'] = "def";
		map['4'] = "ghi";
		map['5'] = "jkl";
		map['6'] = "mno";
		map['7'] = "pqrs";
		map['8'] = "tuv";
		map['9'] = "wxyz";
	}

	vector<int> spiralOrder(vector<vector<int>> &matrix) {
		vector<int> res;
		if (matrix.empty()) return res;
		int m = matrix.size();
		int n = matrix[0].size();

		int left = 0;
		int right = n - 1;
		int top = 0;
		int bottom = m - 1;

		while (left < right && top < bottom) {
			for (int i = left; i < right; i++) {
				res.push_back(matrix[top][i]);
			}
			for (int i = top; i < bottom; i++) {
				res.push_back(matrix[i][right]);
			}
			for (int i = right; i > left; i--) {
				res.push_back(matrix[bottom][i]);
			}
			for (int i = bottom; i > top; i--) {
				res.push_back(matrix[i][left]);
			}
			left++;
			right--;
			top++;
			bottom--;
		}

		if (left > right || top > bottom) {
			return res;
		}
		if (left == right) {
			for (int i = top; i <= bottom; i++) {
				res.push_back(matrix[i][left]);
			}
		} else {
			for (int i = left; i <= right; i++) {
				res.push_back(matrix[top][i]);
			}
		}
		return res;
	}

	vector<int> maxSlidingWindow(vector<int> &nums, int k) {
		deque<int> deque;
		int m = nums.size();
		vector<int> res(m - k + 1);
		int index = 0;
		for (int i = 0; i < m; i++) {
			while (!deque.empty() && nums[deque.back()] <= nums[i]) {
				deque.pop_back();
			}
			if (!deque.empty() && deque.front() <= i - k) {
				deque.pop_front();
			}
			deque.push_back(i);
			if (i >= k - 1) {
				res[index++] = nums[deque.front()];
			}
		}
		return res;
	}
};

int main() {
	Solution s;

	vector<int> arr{7, 2, 4};
	s.maxSlidingWindow(arr, 2);

}
