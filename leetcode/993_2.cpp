/*
    Немного оптимизированная версия, т.к. не вополняется проверка размера.
*/

class RecentCounter {
    queue<int> q;
public:
    RecentCounter() {}
    
    int ping(int t) {
        q.push(t);
        while (q.front() + 3000 < t) {q.pop();}
        return q.size();
    }
};

/**
 * Your RecentCounter object will be instantiated and called as such:
 * RecentCounter* obj = new RecentCounter();
 * int param_1 = obj->ping(t);
 */