// Problem - https://leetcode.com/problems/design-linked-list/description/
// Solution - https://leetcode.com/problems/design-linked-list/submissions/1341037288/
class MyLinkedList {
public:
    vector<int>a;
    MyLinkedList() {
    }
    int get(int index) {
      for(int i=0;i<a.size();i++){
          if(i==index)
           return a[i];
      }   
        return -1;
    }
    void addAtHead(int val) {
    a.insert(a.begin(),val);
    }
    void addAtTail(int val) {
      a.push_back(val);   
    }
    void addAtIndex(int index, int val) {
       if(index < a.size())
        a.insert(a.begin()+index,val);
         else if(index==a.size())
          a.push_back(val);
    }
    void deleteAtIndex(int index) {
       if(index < a.size())
       a.erase(a.begin()+index); 
    }
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */