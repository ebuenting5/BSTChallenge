#include <iostream>

using namespace std;

template <typename T>
struct Node
{
    T data;
    Node<T>* left;
    Node<T>* right;
    Node(T data) {
        this->data = data;
        left = right = nullptr;
    }
};

template <typename T>
class BST {
public:
    Node<T>* root;
    BST() {
        root = nullptr;
    }
    void insert(T data) {
        Node<T>* node = new Node<T>(data);
        if (root == nullptr) {
            root = node;
            return;
        }
        Node<T>* current = root;
        Node<T>* parent = nullptr;
        while (true) {
            parent = current;
            if (data < current->data) {
                current = current->left;
                if (current == nullptr) {
                    parent->left = node;
                    break;
                }
            }
            else {
                current = current->right;
                if (current == nullptr) {
                    parent->right = node;
                    break;
                }
            }
        }
    }
    bool isEmpty() {
        return root == nullptr;
    }
    bool isFull() {
        return false;
    }
    int size() {
        return size(root);
    }
    int size(Node<T>* node) {
        if (node == nullptr) {
            return 0;
        }
        else {
            return size(node->left) + 1 + size(node->right);
        }
    }
    Node<T>* remove(Node<T>* node, T data) {
        if (node == nullptr) {
            return node;
        }
        if (data < node->data) {
            node->left = remove(node->left, data);
        }
        else if (data > node->data) {
            node->right = remove(node->right, data);
        }
        else {
            if (node->left == nullptr) {
                Node<T>* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node<T>* temp = node->left;
                delete node;
                return temp;
            }
            Node<T>* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data);
        }
        return node;
    }
    Node<T>* minValueNode(Node<T>* node) {
        Node<T>* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }
    void printInOrder() {
        printInOrder(root);
    }
    void printInOrder(Node<T>* node) {
        if (node == nullptr) {
            return;
        }
        printInOrder(node->left);
        cout << node->data << " ";
        printInOrder(node->right);
    }
    Node<T>* getNext(Node<T>* node, T data) {
        Node<T>* current = search(node, data);
        if (current == nullptr) {
            return nullptr;
        }
        if (current->right != nullptr) {
            return minValueNode(current->right);
        }
        else {
            Node<T>* successor = nullptr;
            Node<T>* ancestor = root;
            while (ancestor != current) {
                if (current->data < ancestor->data) {
                    successor = ancestor;
                    ancestor = ancestor->left;
                }
                else {
                    ancestor = ancestor->right;
                }
            }
            return successor;
        }
    }
    Node<T>* search(Node<T>* node, T data) {
        if (node == nullptr || node->data == data) {
            return node;
        }
        if (node->data < data) {
            return search(node->right, data);
        }
        return search(node->left, data);
    }
    bool isBST(Node<T>* root, Node<T>* lessthan, Node<T>* greaterthan) {
        if (root == nullptr) {
            return true;
        }
        if (lessthan != nullptr && root->data <= lessthan->data) {
            return false;
        }
        if (greaterthan != nullptr && root->data >= greaterthan->data) {
            return false;
        }
        return isBST(root->left, lessthan, root) && isBST(root->right, root, greaterthan);
    }

    bool is_bst() {
        return isBST(root, nullptr, nullptr);
    }

    int kth_smallest(int k)
    {
        Node<T>* current = root;
        for (int i = 0; i < k; i++)
        {
            current = current->left;
            if (current == nullptr)
                return NULL;
        }
        return current->data;
    }
};

int main(int k) {
    BST<int> bst;
    bst.insert(5);
    bst.insert(3);
    bst.insert(7);
    bst.insert(1);
    bst.insert(9);
    bst.printInOrder();
    if (bst.is_bst())
        cout << "\nTree is valid\n";
    else
        cout << "\nTree is not valid\n";
    cout << "Insert k:\n";
    cin >> k;
    cout << bst.kth_smallest(k);
    return 0;
}