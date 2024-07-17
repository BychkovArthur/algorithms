class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char, int> mp;

        for (char c : t) ++mp[c];

        int l = 0;
        int mn = 1e9;
        int diff = t.size();

        int ll = 0;

        for (int r = 0; r < s.size(); ++r) {
            if (mp.contains(s[r]) && mp[s[r]]-- > 0) --diff;
            while (diff == 0) {
                if (r - l + 1 < mn) {
                    ll = l;
                    mn = r - l + 1;
                }
                if (mp.contains(s[l++]) && mp[s[l - 1]]++ == 0) ++diff;
            }
        }
        if (mn == 1e9) return "";
        return s.substr(ll, mn);
    }
};