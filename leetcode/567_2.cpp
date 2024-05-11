/*
    Time: O(n + |A|)
    Space: O(|A|)
*/

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        int sn1 = s1.size();
        int sn2 = s2.size();
        if (sn1 > sn2) {
            return false;
        }
        array<int, 26> a1;
        array<int, 26> a2;
        for (int i = 0; i < sn1; ++i) {
            ++a1[s1[i] - 'a'];
            ++a2[s2[i] - 'a'];
        }
        int matches = 0;
        for (int i = 0; i < 26; ++i) {
            matches += (a1[i] == a2[i]);
        }

        for (int i = sn1; i <= sn2; ++i) {
            if (matches == 26) {
                return true;
            }
            if (i < sn2) {
                --a2[s2[i - sn1] - 'a'];
                if (a2[s2[i - sn1] - 'a'] == a1[s2[i - sn1] - 'a']) ++matches;
                if (a2[s2[i - sn1] - 'a'] == a1[s2[i - sn1] - 'a'] - 1) --matches;
                ++a2[s2[i] - 'a'];
                if (a2[s2[i] - 'a'] == a1[s2[i] - 'a']) ++matches;
                if (a2[s2[i] - 'a'] == a1[s2[i] - 'a'] + 1) --matches;
            }
        }
        return false;
    }
};