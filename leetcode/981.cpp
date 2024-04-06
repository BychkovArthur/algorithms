class TimeMap {
unordered_map<string, pair<vector<string>, vector<int>>> mp;
public:
    TimeMap() {}
    
    void set(string key, string value, int timestamp) {
        mp[key].first.push_back(move(value));
        mp[key].second.push_back(timestamp);
    }
    
    string get(string key, int timestamp) {
        if (!mp.contains(key)) {
            return "";
        }
        
        vector<int>& vct = mp[key].second;
        vector<string>& strs = mp[key].first;
        int l = 0;
        int r = vct.size() - 1;

        if (vct[l] > timestamp) {
            return "";
        }
        if (vct[r] <= timestamp) {
            return strs[r];
        }

        while (l < r - 1) {
            int m = (l + r) / 2;

            if (vct[m] <= timestamp) {
                l = m;
            } else {
                r = m;
            }
        }
        return strs[l];
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */