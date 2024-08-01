#include<bits/stdc++.h>
using namespace std;

class LRUCache {
private:
    int capacity;
    list<pair<int, int>> lru_list;
    unordered_map<int, list<pair<int, int>>::iterator> cache_map;

    void move_to_front(int key, int value) {
        auto it = cache_map[key];
        lru_list.erase(it);
        lru_list.push_front({key, value});
        cache_map[key] = lru_list.begin();
    }

public:
    LRUCache(int capacity) : capacity(capacity) {}

    int get(int key) {
        if (cache_map.find(key) == cache_map.end()) {
            return -1;
        }
        auto it = cache_map[key];
        int value = it->second;
        move_to_front(key, value);
        return value;
    }

    void put(int key, int value) {
        if (cache_map.find(key) != cache_map.end()) {
            move_to_front(key, value);
        } else {
            if (lru_list.size() >= capacity) {
                auto last = lru_list.back();
                cache_map.erase(last.first);
                lru_list.pop_back();
            }
            lru_list.push_front({key, value});
            cache_map[key] = lru_list.begin();
        }
    }
};

int main() {
    LRUCache cache(2);

    cache.put(1, 1);
    cache.put(2, 2);
    cout << cache.get(1) << endl;
    cache.put(3, 3);
    cout << cache.get(2) << endl;
    cache.put(4, 4);
    cout << cache.get(1) << endl;
    cout << cache.get(3) << endl;
    cout << cache.get(4) << endl;

    return 0;
}
