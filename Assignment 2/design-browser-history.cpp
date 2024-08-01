// problem - https://leetcode.com/problems/design-browser-history/description/
// solution - https://leetcode.com/problems/design-browser-history/submissions/1341024599/
class BrowserHistory {
public:
    vector<string> a;
    int curr ;

    BrowserHistory(string homepage) {
        curr = 0;
        a.push_back(homepage);
    }
    
    void visit(string url) {
        int end = a.size()-1;
        while(end>curr){
            a.pop_back();
            end--;
        }
        curr++;
        a.push_back(url);
    }
    
    string back(int steps) {
        curr = max(0,curr-steps);
        return a[curr];
    }
    
    string forward(int steps) {
        int end = a.size()-1;
        curr = min(end,curr+steps);
        return a[curr];
    }
};

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */