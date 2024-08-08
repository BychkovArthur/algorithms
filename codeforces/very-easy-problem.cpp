/*
    Задача: https://codeforces.com/group/QmrArgR1Jp/contest/254626/problem/G
*/


using ll = long long int;

int VeryEasyProblem(int n, int x, int y) {
    if (n == 1) return min(x, y);
    
    ll ans = min(x, y);
    --n;
    
    ll l = -1, r = max(x, y) * n;
    
    while (l < r - 1) { // int m = l + (r - l) / 2;
        ll m = (l + r) / 2;
        
        if ((m / x + m / y) >= n) {
            r = m;
        } else {
            l = m;
        }
    }
    
    ans += r;
    return ans;
}