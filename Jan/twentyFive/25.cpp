//
// Created by Forrest on 1/25/22.
//

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <math.h>

using namespace std;

class Solution {
 public:

	int ladderLength(string beginWord, string endWord, vector<string> &wordList) {

		unordered_set<string> set;
		for (string str : wordList) set.insert(str);
		if (beginWord == endWord) return 0;
		if (set.empty() || !set.count(endWord)) return 0;
		queue<string> one;
		unordered_set<string> visitedOne;
		one.push(beginWord);
		visitedOne.insert(beginWord);

		queue<string> two;
		unordered_set<string> visitedTwo;
		two.push(endWord);
		visitedTwo.insert(endWord);

		int steps = 0;

		while (!one.empty() && !two.empty()) {
			steps++;

			if (one.size() > two.size()) {
				queue<string> pt = one;
				one = two;
				two = pt;

				unordered_set<string> tmp = visitedOne;
				visitedOne = visitedTwo;
				visitedTwo = tmp;
			}

			int size = one.size();
			for (int i = 0; i < size; i++) {
				string cur = one.front();
				one.pop();
				for (int j = 0; j < cur.size(); j++) {
					for (char ch = 'a'; ch <= 'z'; ch++) {
						char tmp = cur[j];
						cur[j] = ch;

						if (set.count(cur) && !visitedOne.count(cur)) {
							one.push(string(cur));
							visitedOne.insert(string(cur));
						}
						if (visitedTwo.count(string(cur))) return steps + 1;
						cur[j] = tmp;
					}
				}
			}
		}
		return 0;
	}

};

int *test() {
	int ph = 10;
	return &ph;
}

int main() {

	int a = 10;

	cout << *(&a) << endl;
}