#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:

    static bool cmp(const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second || (a.second == b.second && a.first > b.first);
    }

    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> mp;

        for (size_t i = 0; i < nums.size(); ++i) {
            if (!mp.contains(nums[i])) {
                mp[nums[i]] = 0;
            }
            ++mp[nums[i]];
        }
         
        vector<pair<int, int>> pairs;
        for (auto& pr : mp) {
            pairs.push_back(pr);
        }

        sort(pairs.begin(), pairs.end(), cmp);
        vector<int> res(k);

        for (size_t i = 0; i < k; ++i) {
            res[i] = pairs[i].first;
        }

        return  res;
    }
};


int main() {
    Solution sol;


}