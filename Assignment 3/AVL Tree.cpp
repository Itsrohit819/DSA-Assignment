#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int data, height, subtreeSize;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = nullptr;
        height = 1;
        subtreeSize = 1;
    }
};

class AVLTree {
private:
    Node *root;
    int sz;

public:
    AVLTree() {
        sz = 0;
        root = nullptr;
    }

    int size() {
        return sz;
    }

    void insert(int data) {
        root = add(root, data);
    }

    void remove(int data) {
        root = del(root, data);
    }

    void inorder() {
        inorderTraversal(root);
        cout << '\n';
    }

    void postorder() {
        postorderTraversal(root);
        cout << '\n';
    }

    int order_of_key(int key) {
        return orderOfKey(root, key);
    }

    int get_by_order(int k) {
        return getByOrder(root, k);
    }

private:
    int height(Node *node) {
        if (node == nullptr) {
            return 0;
        }
        return node->height;
    }

    int balanceFactor(Node *node) {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    Node* rightRotate(Node *node) {
        Node *leftChild = node->left;
        Node *leftRightSubtree = leftChild->right;

        leftChild->right = node;
        node->left = leftRightSubtree;

        node->height = 1 + max(height(node->left), height(node->right));
        leftChild->height = 1 + max(height(leftChild->left), height(leftChild->right));

        node->subtreeSize = 1 + getSubtreeSize(node->left) + getSubtreeSize(node->right);
        leftChild->subtreeSize = 1 + getSubtreeSize(leftChild->left) + getSubtreeSize(leftChild->right);

        return leftChild;
    }

    Node* leftRotate(Node *node) {
        Node *rightChild = node->right;
        Node *rightLeftSubtree = rightChild->left;

        rightChild->left = node;
        node->right = rightLeftSubtree;

        node->height = 1 + max(height(node->left), height(node->right));
        rightChild->height = 1 + max(height(rightChild->left), height(rightChild->right));

        node->subtreeSize = 1 + getSubtreeSize(node->left) + getSubtreeSize(node->right);
        rightChild->subtreeSize = 1 + getSubtreeSize(rightChild->left) + getSubtreeSize(rightChild->right);

        return rightChild;
    }

    void inorderTraversal(Node *node) {
        if (node == nullptr)
            return;

        inorderTraversal(node->left);
        cout << node->data << ' ';
        inorderTraversal(node->right);
    }

    Node* add(Node *node, int data) {
        if (node == nullptr) {
            sz++;
            return new Node(data);
        }
        
        if (data < node->data) {
            node->left = add(node->left, data);
        } else if (data > node->data) {
            node->right = add(node->right, data);
        } else {
            return node;
        }

        node->height = 1 + max(height(node->left), height(node->right));
        node->subtreeSize = 1 + getSubtreeSize(node->left) + getSubtreeSize(node->right);

        int balance = balanceFactor(node);

        if (balance > 1 && data < node->left->data) {
            return rightRotate(node);
        }

        if (balance < -1 && data > node->right->data) {
            return leftRotate(node);
        }

        if (balance > 1 && data > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && data < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void postorderTraversal(Node *node) {
        if (node == nullptr)
            return;
        postorderTraversal(node->left);
        postorderTraversal(node->right);
        cout << node->data << ' ';
    }

    Node* del(Node *node, int data) {
        if (node == nullptr)
            return node;
        
        if (data < node->data) {
            node->left = del(node->left, data);
        } else if (data > node->data) {
            node->right = del(node->right, data);
        } else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                sz--;
                return nullptr;
            } else if (node->left == nullptr) {
                Node *temp = node->right;
                delete node;
                sz--;
                return temp;
            } else if (node->right == nullptr) {
                Node *temp = node->left;
                delete node;
                sz--;
                return temp; 
            } else {
                Node *predecessor = node->left;
                while (predecessor->right) {
                    predecessor = predecessor->right;
                }
                node->data = predecessor->data;
                node->left = del(node->left, predecessor->data);
            }
        }

        if (node == nullptr)
            return node;
        
        node->height = 1 + max(height(node->left), height(node->right));
        node->subtreeSize = 1 + getSubtreeSize(node->left) + getSubtreeSize(node->right);

        int balance = balanceFactor(node);

        if (balance > 1 && balanceFactor(node->left) >= 0) {
            return rightRotate(node);
        }

        if (balance > 1 && balanceFactor(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && balanceFactor(node->right) <= 0) {
            return leftRotate(node);
        }

        if (balance < -1 && balanceFactor(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    int getSubtreeSize(Node *node) {
        return node ? node->subtreeSize : 0;
    }

    int orderOfKey(Node *node, int key) {
        if (node == nullptr) {
            return 0;
        }
        if (key <= node->data) {
            return orderOfKey(node->left, key);
        } else {
            return 1 + getSubtreeSize(node->left) + orderOfKey(node->right, key);
        }
    }

    int getByOrder(Node *node, int k) {
        if (node == nullptr) {
            return -1; // invalid k
        }

        int leftSize = getSubtreeSize(node->left);

        if (k < leftSize) {
            return getByOrder(node->left, k);
        } else if (k > leftSize) {
            return getByOrder(node->right, k - leftSize - 1);
        } else {
            return node->data;
        }
    }
};

int main() {
    AVLTree avl;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        avl.insert(x);
    }

    cout << "PostOrder:\n";
    avl.postorder();
    cout << "InOrder:\n";
    avl.inorder();

    int key;
    cin >> key;
    cout << "Order of key " << key << ": " << avl.order_of_key(key) << '\n';

    int k;
    cin >> k;
    cout << k << " : " << avl.get_by_order(k) << '\n';

    return 0;
}
