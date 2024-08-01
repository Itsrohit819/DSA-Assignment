#include<bits/stdc++.h>
using namespace std;

#define INITIAL_CAPACITY 16
#define MAX_LOAD_FACTOR 0.75

template<typename K, typename V>
class HashTable {
private:
    struct Entry {
        K key;
        V value;

        Entry(K key, V value) : key(key), value(value) {}
    };

    vector<list<Entry>> table;
    int size;
    int capacity;

    int hash_key(const K& key) const {
        // Simple hash function, can be improved based on key type
        return std::hash<K>()(key) % capacity;
    }

    void resize() {
        int old_capacity = capacity;
        vector<list<Entry>> old_table = table;

        capacity *= 2;
        table.assign(capacity, list<Entry>());
        size = 0;

        for (const auto& bucket : old_table) {
            for (const auto& entry : bucket) {
                insert(entry.key, entry.value);
            }
        }
    }

public:
    HashTable() : size(0), capacity(INITIAL_CAPACITY) {
        table.assign(capacity, list<Entry>());
    }

    void insert(const K& key, const V& value) {
        if ((double)size / capacity > MAX_LOAD_FACTOR) {
            resize();
        }

        int idx = hash_key(key);
        auto& bucket = table[idx];

        for (auto& entry : bucket) {
            if (entry.key == key) {
                entry.value = value;
                return;
            }
        }

        bucket.emplace_back(key, value);
        ++size;
    }

    V find(const K& key) const {
        int idx = hash_key(key);
        const auto& bucket = table[idx];

        for (const auto& entry : bucket) {
            if (entry.key == key) {
                return entry.value;
            }
        }
        throw std::runtime_error("Key not found.");
    }

    void remove(const K& key) {
        int idx = hash_key(key);
        auto& bucket = table[idx];

        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->key == key) {
                bucket.erase(it);
                --size;
                return;
            }
        }
        throw std::runtime_error("Key not found.");
    }

    int get_size() const {
        return size;
    }

    bool empty() const {
        return size == 0;
    }
};

int main() {
    HashTable<string, int> hash_table;

    hash_table.insert("one", 1);
    hash_table.insert("two", 2);
    hash_table.insert("three", 3);

    cout << "Value for 'one': " << hash_table.find("one") << '\n';
    cout << "Value for 'two': " << hash_table.find("two") << '\n';

    hash_table.remove("two");
    cout << "Size after removing 'two': " << hash_table.get_size() << '\n';
    return 0;
}
