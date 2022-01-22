//
// Created by Forrest on 1/20/22.
//

#include<vector>
#include<unordered_map>
#ifndef PROJECTS_SOLUTION_H
#define PROJECTS_SOLUTION_H
using namespace std;

class Solution {
    public:

        vector<int> twoSum(vector<int>& nums, int target) {
            unordered_map<int, int> map;
            vector<int> res;
            for (int i = 0; i < nums.size(); i++) {
                int num = nums[i];
                int cur_target = target - num;
                if (map.find(cur_target) != map.end()) {
                    res.push_back(map[cur_target]);
                    res.push_back(i);
                    return res;
                }
                map[num] = i;
            }
            return res;
        }


        int minEatingSpeed(vector<int> &piles, int h) {
            int l = 1;
            int r = INT_MIN;
            for (int pile : piles) {
                if (pile > r) {
                    r = pile;
                }
            }
            while (l < r) {
                int mid = l + (r - l) / 2;
                int consume_hour = getHours(piles, mid);
                if (consume_hour <= h) {
                    r = mid;
                } else {
                    l = mid + 1;
                }
            }

            return l;
        }

        int getHours(vector<int> &piles, int hour) {
            int consume_hour = 0;
            for (int pile : piles) {
                consume_hour += pile / hour;
                consume_hour += pile % hour == 0 ? 0 : 1;
            }
            return consume_hour;
        }

};


#endif //PROJECTS_SOLUTION_H
