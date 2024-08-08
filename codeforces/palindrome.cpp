/*

    Задача: https://codeforces.com/contest/1883/problem/B
*/


bool CanBePalindrome(string s, int n, int k) {
    std::array<int, 26> arr;
    
    for (char c : s) {
        ++arr[c - 'a'];
    }
    
    
    int m = 0;
    for (int cnt : arr) {
        if (cnt % 2) ++m;
    }
    
    if (m > k + 1) return false;
    return true;
}