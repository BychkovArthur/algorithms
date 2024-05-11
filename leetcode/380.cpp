class RandomizedSet {
public:
    unordered_map<int, int> mp;
    vector<int> vct;

    RandomizedSet() {}
    
    bool insert(int val) {
        if (!mp.contains(val)) {
            mp[val] = vct.size();
            vct.push_back(val);
            return true;
        }
        return false;
    }
    
    bool remove(int val) {
        if (mp.contains(val)) {
            mp[vct[vct.size() - 1]] = mp[val];
            swap(vct[mp[val]], vct[vct.size() - 1]);
            vct.pop_back();
            mp.erase(val);
            return true;
        }
        return false;
    }
    
    int getRandom() {
        return vct[rand() % vct.size()];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */