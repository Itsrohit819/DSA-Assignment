#include<bits/stdc++.h>
using namespace std;
class Node{
public:
	int val;
	Node* next;
	Node(int data,Node* next=nullptr){
		val=data;
		this->next=next;
	}
};
class SLL{
private:
	Node* head;
	int size;
public:
	SLL(){
        head=nullptr;
        size=0;
    }
	int getSize(){
		return size;
	}
	bool isEmpty() {
		return size==0;
	}
	void appendatlast(int data) {
		Node* newnode=new Node(data);
		if(isEmpty()) {
			head=newnode;
		}else{
			Node* last=head;
			while(last->next!=nullptr){
				last=last->next;
			}
			last->next=newnode;
		}
		size++;
	}
	void addFirst(int data) {
		Node* newnode=new Node(data);
		if(isEmpty()){
			head=newnode;
		}else{
			newnode->next=head;
			head=newnode;
		}
		size++;
	}
	void insertAt(int index,int data){
		if(index<0 || index>size){
			throw out_of_range("Index out of bounds");
		}
		Node* newnode=new Node(data);
		if(index==0){
			addFirst(data);
		}else if(index == size){
			appendatlast(data);
		}else{
			Node* pos=head;
			for(int i=0;i<index-1;i++){
				pos=pos->next;
			}
			Node* nextpos=pos->next;
			pos->next=newnode;
			newnode->next=nextpos;
			size++;
		}
		
	}
	void delat(int index){
		if(index<0 || index>size){
			throw out_of_range("Index out of bounds");
		}
		if(index==0){
			Node* nexthead=head->next;
			head->next=nullptr;
			head=nexthead;
			size--;
		}else{
			Node* current=head;
			for(int i=0;i<index-1;i++){
				current=current->next;
			}
			Node* curnext=current->next->next;
			current->next->next=nullptr;
			current->next=curnext;
			size--;
		}
	}
	int middle(){
		if(isEmpty()){
			return -1;
		}
		int c=0;
        Node* demo=head;
        while(demo!=NULL){
            c+=1;
            demo=demo->next;
        }
        int t=c/2;
        Node* ans=head;
        for(int j=0;j<t;j++){
            ans=ans->next;
        }
        return ans->val;
	}
	void reverse(){
		Node* prev=nullptr;
        Node* current=head;
        while(current!=nullptr){
            Node* nxt=current->next;
            current->next=prev;
            prev=current;
            current=nxt;
        }
        head=prev;
	}
	int indexat(int data){
		Node* current=head;
		int index=0;
		while(current->next!=nullptr){
			if(current->val==data){
				return index;
			}
			current=current->next;
			index+=1;
		}
		if(current->val==data){
			return index;
		}
		return -1;
	}
	Node* mergeTwoLists(Node* list1, Node* list2){
        if(!list1){
            return list2;
        }
        if(!list2){
            return list1;
        }
        Node* head=nullptr;
        Node* index=nullptr;
        while(list1!=nullptr && list2!=nullptr){
            if(head==nullptr && list1->val>=list2->val){
                head=list2;
                list2=list2->next;
                index=head;
            }else if(head==nullptr && list2->val>list1->val){
                head=list1;
                list1=list1->next;
                index=head;
            }else if(list1->val>=list2->val){
                index->next=list2;
                index=index->next;
                list2=list2->next;
            }else if(list2->val>list1->val){
                index->next=list1;
                index=index->next;
                list1=list1->next;
            }
        }
        if(list1!=nullptr){
            index->next=list1;
        }else{
            index->next=list2;
        }
        return head;
    }
    Node* interleave(Node* list1, Node* list2){
    	Node* l1=list1;
        Node* l2=list2;
        while(l1!=nullptr && l2!=nullptr){
            Node* l1p=l1->next;
            Node* l2p=l2->next;
            l1->next=l2;
            l2->next=l1p;
            l1=l1p;
            l2=l2p;
        }
        return list1;
	}
	Node* twoparts(Node* head,int index){
		Node* list2=head;
		for(int i=0;i<index-1;i++){
			list2=list2->next;
		}
		Node* random=list2->next;
		list2->next=nullptr;
		list2=random;
		return list2;
	}
	void rotate(int k){
		int diff=k%size;
		if(diff==0){
			return ;
		}
		Node* rot=head;
		int move=size-diff;
		for(int j=0;j<move-1;j++){
			rot=rot->next;
		}
		Node* rot2=rot->next;
		rot->next=nullptr;
		Node* rot3=rot2;
		while(rot3->next!=nullptr){
			rot3=rot3->next;
		}
		rot3->next=head;
		head=rot2;
	}
	void printList(){
		Node* current=head;
		while(current != nullptr){
			cout << current->val << " ";
			current=current->next;
		}
		cout << endl;
	}
};

int main(){
	SLL l;
	cout << l.getSize() << endl;
	l.addFirst(1);
	l.appendatlast(3);
	l.insertAt(2,5);
	cout << l.indexat(3) << endl;
	cout << l.middle() << endl;
	l.printList();
	l.delat(0);
	l.printList();
	l.reverse();
	l.printList();
	l.rotate(1);
	l.printList();
}