#include <iostream>
using namespace std;

struct Node {
    int key;
    Node *left, *right;
    Node(int k) : key(k), left(NULL), right(NULL) {}
};

class BST {
    Node *root;

    Node *insert(Node *t, int key, bool &done) {
        if (t == NULL) { 
            done = true; 
            return new Node(key); 
        }
        if (key < t->key) 
            t->left = insert(t->left, key, done);
        else if (key > t->key) 
            t->right = insert(t->right, key, done);
        return t;
    }

    Node *minNode(Node *t) {
        while (t->left != NULL) 
            t = t->left;
        return t;
    }

    Node *remove(Node *t, int key, bool &done) {
        if (t == NULL) return NULL;

        if (key < t->key) {
            t->left = remove(t->left, key, done);
        } else if (key > t->key) {
            t->right = remove(t->right, key, done);
        } else {
            done = true;
            if (t->left == NULL) {
                Node *r = t->right;
                delete t;
                return r;
            }
            if (t->right == NULL) {
                Node *l = t->left;
                delete t;
                return l;
            }
            Node *s = minNode(t->right);
            t->key = s->key;
            bool d = false;
            t->right = remove(t->right, s->key, d);
        }
        return t;
    }

    void inorder(Node *t) {
        if (t) {
            inorder(t->left);
            cout << t->key << " ";
            inorder(t->right);
        }
    }

    void preorder(Node *t) {
        if (t) {
            cout << t->key << " ";
            preorder(t->left);
            preorder(t->right);
        }
    }

    void postorder(Node *t) {
        if (t) {
            postorder(t->left);
            postorder(t->right);
            cout << t->key << " ";
        }
    }

    void showTree(Node *t, int level) {
        if (t == NULL) return;
        showTree(t->right, level + 1);
        for (int i = 0; i < level; i++) cout << "    ";
        cout << t->key << "\n";
        showTree(t->left, level + 1);
    }

    int height(Node *t) {
        if (t == NULL) return 0;
        int l = height(t->left), r = height(t->right);
        return 1 + (l > r ? l : r);
    }

public:
    BST() : root(NULL) {}

    void insert(int key) {
        bool done = false;
        root = insert(root, key, done);
        if (done) 
            cout << "Key " << key << " inserted.\n";
        else 
            cout << "Key " << key << " already exists. Duplicate not inserted.\n";
    }

    void search(int key) {
        Node *t = root;
        int steps = 1;
        while (t != NULL) {
            if (key == t->key) {
                cout << "Key " << key << " found (comparisons: " << steps << ").\n";
                return;
            }
            t = (key < t->key) ? t->left : t->right;
            steps++;
        }
        cout << "Key " << key << " not found.\n";
    }

    void remove(int key) {
        if (root == NULL) {
            cout << "Tree is empty. Nothing to delete.\n";
            return;
        }
        bool done = false;
        root = remove(root, key, done);
        if (done) 
            cout << "Key " << key << " deleted.\n";
        else 
            cout << "Key " << key << " not found. Nothing deleted.\n";
    }

    void display() {
        if (root == NULL) {
            cout << "Tree is empty.\n";
            return;
        }
        cout << "Inorder: ";
        inorder(root);
        cout << "\n";

        cout << "Preorder : ";
        preorder(root);
        cout << "\n";

        cout << "Postorder: ";
        postorder(root);
        cout << "\n";

        cout << "Height of tree = " << height(root) << "\n";
        cout << "Tree (rotated left, root at the left side):\n";
        showTree(root, 0);
    }
};

int main() {
    BST t;
    int choice, key;

    do {
        cout << "\n===== BINARY SEARCH TREE =====\n"
             << "1. Insert\n2. Delete\n3. Search\n4. Display\n5. Exit\n"
             << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key to insert: ";
                cin >> key;
                t.insert(key);
                break;
            case 2:
                cout << "Enter key to delete: ";
                cin >> key;
                t.remove(key);
                break;
            case 3:
                cout << "Enter key to search: ";
                cin >> key;
                t.search(key);
                break;
            case 4:
                t.display();
                break;
            case 5:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
