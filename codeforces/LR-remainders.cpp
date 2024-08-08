/*
    Задача: https://codeforces.com/contest/1932/problem/C
*/


vector<int> LRmod(int n, int m, vector<int> a, string s) {
    vector<int> ans(n);
    
    int l = 0, r = n - 1;
    
    for (int i = 0; i < n - 1; ++i) {
        if (s[i] == 'L') ++l;
        else --r;
    }
    
    int prod = a[l] % m;
    ans[0] = prod;
    
    
    for (int i = 1; i < n; ++i) {
        if (s[n - i - 1] == 'R') {
            ++r;
            prod = (prod * (a[r] % m)) % m;
        } else {
            --l;
            prod = (prod * (a[l] % m)) % m;
        } 
        ans[i] = prod;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}