/*
    Решение за O(n * |A|) Time 
    И за O(|A|) Space
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

        for (int i = sn1; i <= sn2; ++i) {
            if (a1 == a2) {
                return true;
            }
            if (i < sn2) {
                --a2[s2[i - sn1] - 'a'];
                ++a2[s2[i] - 'a'];
            }
        }
        return false;
    }
};