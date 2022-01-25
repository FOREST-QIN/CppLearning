//
// Created by Forrest on 1/24/22.
//

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <math.h>

using namespace std;

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
 public:
	bool exist(vector<vector<char>> &board, string word) {
		for (int i = 0; i < board.size(); i++) {
			for (int j = 0; j < board[0].size(); j++) {
				if (dfs(i, j, board,0,word)) return true;
			}
		}
		return false;
	}

	bool dfs(int i, int j, vector<vector<char>> &board, int index, string &word) {
		if (index == word.size()) return true;
		if (i < 0 || j < 0 || i >= board.size() || j >= board[0].size() || board[i][j] == '*' || word[index] != board[i][j]) {
			return false;
		}
		char ch = board[i][j];
		board[i][j] = '*';

		bool ret =
			dfs(i, j + 1, board, index + 1, word)
			|| dfs(i, j - 1, board, index + 1, word)
			|| dfs(i + 1, j, board, index + 1, word)
			|| dfs(i - 1, j, board, index + 1, word);
		if (ret) return true;
		board[i][j] = ch;
		return false;
	}

	ListNode *mergeKLists(vector<ListNode *> &lists) {
		if (lists.empty() || lists.size() == 0) return NULL;

		auto comp = [&](ListNode *a, ListNode *b) {
			return a->val > b->val;
		};

		priority_queue<ListNode *, vector<ListNode *>, decltype(comp)> minHeap(comp);
		for (ListNode *node : lists) {
			if (node != nullptr) {
				minHeap.push(node);
			}
		}
		ListNode dummy(0);
		ListNode *cur = &dummy;

		while (!minHeap.empty()) {
			ListNode *node = minHeap.top();
			minHeap.pop();
			cur->next = node;
			cur = cur->next;
			node = node->next;
			if (node != nullptr) {
				minHeap.push(node);
			}
		}
		return dummy.next;
	}

	vector<vector<string>> groupAnagrams(vector<string> &strs) {
		vector<vector<string>> res;
		unordered_map<string, vector<string>> map;
		for (string str : strs) {
			map[sortLowercase(str)].push_back(str);
		}
		for (auto &p : map) {
			res.push_back(p.second);
		}
		return res;
	}

	string sortLowercase(string &s) {
		int count[26] = {0};
		for (int i = 0; i < s.size(); i++) {
			count[s[i] - 'a']++;
		}
		string res;
		for (int i = 0; i < 26; i++) {
			res.push_back(count[i]);
		}
		return res;
	}

};

int main() {

}