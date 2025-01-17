// Problem - https://leetcode.com/problems/insert-delete-getrandom-o1-duplicates-allowed/description/
// Solution - https://leetcode.com/problems/insert-delete-getrandom-o1-duplicates-allowed/submissions/1341072808/
class RandomizedCollection {
public:
    vector<int>v;
    unordered_map<int,int>mp;

    RandomizedCollection() {}

    bool insert(int val) 
    {
        if(mp[val] == 0)  
        {
            v.push_back(val);
            mp[val]++;  
            return true;
        }
        else if(mp[val] > 0)   
        {
            v.push_back(val);
            mp[val]++;
            return false;
        }
        return false;
    }

    bool remove(int val) 
    {  
        if(mp[val] > 0)  
        {
            auto it = find(v.begin(),v.end(),val);
            v.erase(it);
            mp[val]--;
            return true;
        }
        return false;
    }

    int getRandom() 
    {
        return v[rand()%v.size()];
    }

};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */