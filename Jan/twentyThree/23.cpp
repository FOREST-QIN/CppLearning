//
// Created by Forrest on 1/23/22.
//
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <math.h>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
 public:

	vector<vector<string>> groupAnagrams(vector<string> &strs) {

	}

	TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
		if (root == nullptr || root == p || root == q) return root;

		TreeNode *left = lowestCommonAncestor(root->left, p, q);
		TreeNode *right = lowestCommonAncestor(root->right, p, q);
		if (left != nullptr && right != nullptr) return root;
		return left == nullptr ? right : left;
	}

	int findKthLargest(vector<int> &nums, int k) {
		priority_queue<int, vector<int>, greater<>> minHeap;

		for (int num : nums) {
			if (minHeap.size() < k) {
				minHeap.push(num);
			} else if (minHeap.top() < num) {
				minHeap.pop();
				minHeap.push(num);
			}
		}
		return minHeap.top();
	}

	vector<string> generateParenthesis(int n) {
		vector<string> res;
		string prefix;
		dfs(0, 0, n, prefix, res);
		return res;
	}

	void dfs(int l, int r, int n, string &prefix, vector<string> &res) {
		if (l == n && r == n) {
			res.push_back(string(prefix));
			return;
		}

		if (l < n) {
			prefix.push_back('(');
			dfs(l + 1, r, n, prefix, res);
			prefix.pop_back();
		}

		if (r < l) {
			prefix.push_back(')');
			dfs(l, r + 1, n, prefix, res);
			prefix.pop_back();
		}
	}

	string longestCommonPrefix(vector<string> &strs) {
		int n = strs.size();
		string ans;
		sort(strs.begin(), strs.end());
		string a = strs[0];
		string b = strs[n - 1];

		for (int i = 0; i < a.size(); i++) {
			if (a[i] == b[i]) {
				ans += a[i];
			} else {
				break;
			}
		}
		return ans;
	}

	int firstMissingPositive(vector<int> &nums) {
		int n = nums.size();
		for (int i = 0; i < n; i++) {
			if (nums[i] <= 0 || nums[i] > n) {
				nums[i] = n + 1;
			}
		}
		for (int i = 0; i < n; i++) {
			int num = abs(nums[i]);
			if (num > n) continue;
			num--;
			if (nums[num] > 0) {
				nums[num] = -nums[num];
			}
		}
		for (int i = 0; i < n; i++) {
			if (nums[i] >= 0) return i + 1;
		}
		return n + 1;
	}

	void nextPermutation(vector<int> &nums) {
		if (nums.empty()) return;

		int n = nums.size();
		int index = n - 2;
		while (index >= 0 && nums[index] >= nums[index + 1]) {
			index--;
		}
		if (index < 0) {
			reverse(nums, 0, nums.size() - 1);
			return;
		}
		for (int i = n - 1; i > index; i--) {
			if (nums[i] > nums[index]) {
				swap(nums, i, index);
				reverse(nums, index + 1, n - 1);
				return;
			}
		}
	}

	void reverse(vector<int> &nums, int i, int j) {
		while (i <= j) {
			swap(nums, i++, j--);
		}
	}

	void swap(vector<int> &nums, int i, int j) {
		int tmp = nums[i];
		nums[i] = nums[j];
		nums[j] = tmp;
	}

	int minMeetingRooms(vector<vector<int>> &intervals) {
		int n = intervals.size();
		int begin[n];
		int end[n];

		for (int i = 0; i < n; i++) {
			begin[i] = intervals[i][0];
			end[i] = intervals[i][1];
		}
		sort(begin, begin + n);
		sort(end, end + n);
		int count = 0;
		int res = 0;
		int i = 0;
		int j = 0;
		while (i < n && j < n) {
			if (begin[i] < end[j]) {
				count++;
				i++;
			} else {
				count--;
				j++;
			}
			res = count > res ? count : res;
		}
		return res;
	}

	bool validPalindrome(string s) {
		return check(s, 0, s.size() - 1, false);
	}

	bool check(string &s, int i, int j, bool flag) {
		while (i <= j) {
			if (s[i] == s[j]) {
				i++;
				j--;
			} else {
				if (flag) return false;
				return check(s, i + 1, j, true) || check(s, i, j - 1, true);
			}
		}
		return true;
	}

	int i = 0;
	int j = 0;
	int max = 0;
	string longestPalindrome(string s) {
		if (s.empty()) return s;

		for (int i = 0; i < s.size(); i++) {
			getLongest(s, i, i);
			getLongest(s, i, i + 1);
		}
		return s.substr(i, max);
	}

	void getLongest(string &s, int l, int r) {
		while (l >= 0 && r < s.size() && s[l] == s[r]) {
			l--;
			r++;
		}
		if (r - l - 1 > max) {
			max = r - l - 1;
			i = l + 1;
			j = r - 1;
		}
	}

	int numBusesToDestination(vector<vector<int>> &routes, int source, int target) {
		unordered_map<int, vector<int>> to_routes;
		for (int i = 0; i < routes.size(); i++) {
			for (int station : routes[i]) {
				to_routes[station].push_back(i);
			}
		}
		queue<pair<int, int>> bfs;
		bfs.push({source, 0});
		unordered_set<int> seen = {source};

		while (!bfs.empty()) {
			int stop = bfs.front().first;
			int step = bfs.front().second;
			bfs.pop();
			if (stop == target) {
				return step;
			}
			for (int i : to_routes[stop]) {
				for (int station : routes[i]) {
					if (seen.find(station) == seen.end()) {
						seen.insert(station);
						bfs.push({station, step + 1});
					}
				}
				routes[i].clear();
			}
		}
		return -1;
	}
};

int main() {
	Solution s;
	s.longestPalindrome("babad");
}