//
// Created by Forrest on 1/21/22.
//
#include "iostream"
#include<vector>
#include "string"
#include "stack"
#include "unordered_map"
#ifndef PROJECTS_SOLUTION_H
#define PROJECTS_SOLUTION_H

using namespace std;





class Solution {
    public:

        bool isValid(string s) {
            if (s.empty()) return true;
            unordered_map<char, char> map;
            map['}'] = '{';
            map[')'] = '(';
            map[']'] = '[';
            stack<char> stack;

            for (char ch : s) {
                if (ch == '(' || ch == '{' || ch == '[') {
                    stack.push(ch);
                } else {
                    if (stack.empty() || stack.top() != map[ch]) {
                        return false;
                    }
                    stack.pop();
                }
            }
            return stack.empty();
        }

        string minRemoveToMakeValid(string s) {
            if (s.empty()) return s;
            string remove_right;
            int left = 0;
            int unmatched = 0;
            for (char ch : s) {
                if (ch == '(') {
                    left++;
                    unmatched++;
                } else if (ch == ')') {
                    if (unmatched == 0) continue;
                    unmatched--;
                }
                remove_right.push_back(ch);
            }
            string res;
            int valid_left = left - unmatched;
            for (char ch : remove_right) {
                if (ch == '(') {
                    if (valid_left == 0) continue;
                    valid_left--;
                }
                res.push_back(ch);
            }
            return res;
        }


        double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
            int left = (nums1.size() + nums2.size() + 1) / 2;
            int right = (nums1.size() + nums2.size() + 2) / 2;

            int l = binarySearch(nums1, 0, nums2, 0, left);
            int r = binarySearch(nums1, 0, nums2, 0, right);
            return (l + r) / 2.0;
        }

        int binarySearch(vector<int> &one, int i, vector<int> &two, int j, int k) {
            if (i >= one.size()) return two[j + k - 1];
            if (j >= two.size()) return one[i + k - 1];
            if (k == 1) return min(one[i], two[j]);
            int oneRes = (i + k / 2 - 1 >= one.size()) ? INT_MAX : one[i + k / 2 - 1];
            int twoRes = (j + k / 2 - 1 >= two.size()) ? INT_MAX : two[j + k / 2 - 1];
            if (oneRes <= twoRes) {
                return binarySearch(one, i + k / 2, two, j, k - k / 2);
            } else {
                return binarySearch(one, i, two, j + k / 2, k - k / 2);
            }
        }
};


#endif //PROJECTS_SOLUTION_H
