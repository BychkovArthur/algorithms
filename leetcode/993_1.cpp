class RecentCounter {
    queue<int> q;
public:
    RecentCounter() {}
    
    int ping(int t) {
        while (!q.empty() && q.front() + 3000 < t) {q.pop();}
        q.push(t);
        return q.size();
    }
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */