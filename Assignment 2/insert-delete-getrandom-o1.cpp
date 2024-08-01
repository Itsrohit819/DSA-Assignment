// Problem - https://leetcode.com/problems/insert-delete-getrandom-o1/description/
// Solution - https://leetcode.com/problems/insert-delete-getrandom-o1/submissions/1341059563/
class RandomizedSet {
public:
    unordered_set<int> s;
    RandomizedSet() {
        
    }
    
    bool insert(int val) {
        if(s.count(val))return false;
        s.insert(val);
        return true;
    }
    
    bool remove(int val) {
        if(!s.count(val))return false;
        s.erase(val);
        return true;
    }
    
    int getRandom() {
        int r = rand() % s.size();
        int cnt = 0;
        for(auto i : s){
            if(r == cnt)return i;
            cnt++;
        }
        return 0;
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */