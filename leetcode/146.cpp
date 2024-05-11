class LRUCache {
private:
    unordered_map<int, pair<int, list<int>::iterator>> mp;
    list<int> lst;
    int capacity;
public:
    LRUCache(int capacity) : capacity(capacity) {}
    
    int get(int key) {
        auto map_it = mp.find(key);
        if (map_it == mp.end()) return -1;

        auto list_it = map_it->second.second;
        int value = map_it->second.first;
        lst.erase(list_it);
        auto lst_it = lst.insert(lst.end(), key);
        mp[key].second = lst_it;

        return value;
    }
    
    void put(int key, int value) {
        auto lst_it = lst.insert(lst.end(), key);
        if (mp.contains(key)) {
            auto remove_lst_it = mp[key].second;
            lst.erase(remove_lst_it);
        } else {
            if (mp.size() == capacity) {
                int key_to_delete = lst.front();
                lst.pop_front();
                mp.erase(key_to_delete);
            }
        }
        mp[key] = {value, lst_it};
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */