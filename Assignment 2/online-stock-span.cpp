// Problem - https://leetcode.com/problems/online-stock-span/description/
// Solution - https://leetcode.com/problems/online-stock-span/submissions/1341078737/
class StockSpanner {
public:
    stack<pair<int,int>> s;
    StockSpanner() {
        
    }
    
    int next(int price) {
        long long int count=1;
        while(s.size()!=0 && s.top().first<=price){
            count=count+s.top().second;
            s.pop();
        }
        s.push({price,count});
        return count;
    }
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */