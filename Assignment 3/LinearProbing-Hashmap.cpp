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
        bool is_active;

        Entry(K key, V value) : key(key), value(value), is_active(true) {}
    };

    vector<Entry*> table;
    int size;
    int capacity;

    int hash_key(const K& key) const {
        // Simple hash function, can be improved based on key type
        return std::hash<K>()(key) % capacity;
    }

    int find_position(const K& key) const {
        int idx = hash_key(key);
        int start_idx = idx;

        while (table[idx] != nullptr) {
            if (table[idx]->is_active && table[idx]->key == key) {
                return idx;
            }
            idx = (idx + 1) % capacity;
            if (idx == start_idx) {
                break;
            }
        }
        return -1;
    }

    void resize() {
        int old_capacity = capacity;
        vector<Entry*> old_table = table;

        capacity *= 2;
        table.assign(capacity, nullptr);
        size = 0;

        for (int i = 0; i < old_capacity; ++i) {
            if (old_table[i] != nullptr && old_table[i]->is_active) {
                insert(old_table[i]->key, old_table[i]->value);
                delete old_table[i];
            }
        }
    }

public:
    HashTable() : size(0), capacity(INITIAL_CAPACITY) {
        table.assign(capacity, nullptr);
    }

    ~HashTable() {
        for (auto entry : table) {
            delete entry;
        }
    }

    void insert(const K& key, const V& value) {
        if ((double)size / capacity > MAX_LOAD_FACTOR) {
            resize();
        }

        int idx = hash_key(key);
        while (table[idx] != nullptr && table[idx]->key != key && table[idx]->key != "-1") {
            idx = (idx + 1) % capacity;
        }

        if (table[idx] == nullptr || table[idx]->key == "-1") {
            if (table[idx] == nullptr) {
                table[idx] = new Entry(key, value);
                ++size;
            } else {
                table[idx]->key = key;
                table[idx]->value = value;
                table[idx]->is_active = true;
            }
        } else {
            table[idx]->value = value;
        }
    }

    V find(const K& key) const {
        int idx = find_position(key);
        if (idx != -1) {
            return table[idx]->value;
        }
        throw std::runtime_error("Key not found.");
    }

    void remove(const K& key) {
        int idx = find_position(key);
        if (idx != -1) {
            table[idx]->is_active = false;
            --size;
        } else {
            throw std::runtime_error("Key not found.");
        }
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
