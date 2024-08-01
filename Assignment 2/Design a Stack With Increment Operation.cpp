// Problem - https://leetcode.com/problems/design-a-stack-with-increment-operation/description/
// Solution - https://leetcode.com/problems/design-a-stack-with-increment-operation/submissions/1341042333/
class CustomStack {
public:
    int size;
    vector<int> a;
    public:
    CustomStack(int maxSize) {
       size = maxSize;
    }
    
    void push(int x) {
        if(a.size() < size)
            a.push_back(x);
    }
    
    int pop() {
        if(a.size() == 0)
            return -1;
        else{
            int res=a.back();
            a.pop_back();
            return res;
        }
        
    }
    
    void increment(int k, int val) {
        int x = k;
        if(a.size() < k)
            x = a.size();
        for(int i=0; i < x; i++){
            a[i] += val;
        }
    }
};

/**
 * Your CustomStack object will be instantiated and called as such:
 * CustomStack* obj = new CustomStack(maxSize);
 * obj->push(x);
 * int param_2 = obj->pop();
 * obj->increment(k,val);
 */