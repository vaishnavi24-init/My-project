// Program (C++): HASHING 2
#include <iostream>
using namespace std;

#define SIZE 10
#define EMPTY -1
#define DELETED -2

class HashTable {
    int table[SIZE];

public:
    HashTable() {
        for (int i = 0; i < SIZE; i++) table[i] = EMPTY;
    }

    // Division method hash function
    int hashFunction(int key) {
        return key % SIZE;
    }

    // Insert using linear probing: index = (h(key) + i) % SIZE
    void insert(int key) {
        if (key < 0) {
            cout << "Only non-negative keys are allowed.\n";
            return;
        }

        int h = hashFunction(key);
        int firstFree = -1; // first EMPTY/DELETED slot seen

        for (int i = 0; i < SIZE; i++) {
            int idx = (h + i) % SIZE;

            if (table[idx] == key) {
                cout << "Key " << key << " already exists at index " << idx << ".\n";
                return;
            }

            if (table[idx] == DELETED && firstFree == -1) {
                firstFree = idx;
            }

            if (table[idx] == EMPTY) {
                if (firstFree == -1) firstFree = idx;
                break; // key cannot be further ahead
            }
        }

        if (firstFree == -1) {
            cout << "Hash table is full. Cannot insert " << key << ".\n";
            return;
        }

        table[firstFree] = key;
        if (firstFree != h)
            cout << "Collision at index " << h << ". Key " << key
                 << " placed at index " << firstFree << " (linear probing).\n";
        else
            cout << "Key " << key << " inserted at index " << firstFree << ".\n";
    }

    // Search - probe until key found, an EMPTY slot is hit, or table is traversed
    void search(int key) {
        int h = hashFunction(key);
        for (int i = 0; i < SIZE; i++) {
            int idx = (h + i) % SIZE;
            if (table[idx] == EMPTY) break;
            if (table[idx] == key) {
                cout << "Key " << key << " found at index " << idx
                     << " (probes: " << i + 1 << ").\n";
                return;
            }
        }
        cout << "Key " << key << " not found.\n";
    }

    // Delete - mark slot as DELETED so later probe chains are not broken
    void remove(int key) {
        int h = hashFunction(key);
        for (int i = 0; i < SIZE; i++) {
            int idx = (h + i) % SIZE;
            if (table[idx] == EMPTY) break;
            if (table[idx] == key) {
                table[idx] = DELETED;
                cout << "Key " << key << " deleted from index " << idx << ".\n";
                return;
            }
        }
        cout << "Key " << key << " not found. Nothing deleted.\n";
    }

    void display() {
        cout << "\n--- Hash Table (Linear Probing) ---\n";
        cout << "Index Key\n";
        for (int i = 0; i < SIZE; i++) {
            cout << i << " ";
            if (table[i] == EMPTY) cout << "EMPTY";
            else if (table[i] == DELETED) cout << "DELETED";
            else cout << table[i];
            cout << "\n";
        }
        cout << "-----------------------------------\n";
    }
};

int main() {
    HashTable ht;
    int choice, key;

    do {
        cout << "\n===== HASH TABLE USING LINEAR PROBING =====\n"
             << "1. Insert\n2. Search\n3. Delete a key\n4. Display the table\n5. Exit\n"
             << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key to insert: ";
                cin >> key;
                ht.insert(key);
                break;
            case 2:
                cout << "Enter key to search: ";
                cin >> key;
                ht.search(key);
                break;
            case 3:
                cout << "Enter key to delete: ";
                cin >> key;
                ht.remove(key);
                break;
            case 4:
                ht.display();
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



// Program (C++): HASHING 1
#include <iostream>
#include <string>
using namespace std;

#define SIZE 10

// Node of a chain (singly linked list) - one key-value pair
struct Node {
    int key;
    string value;
    Node *next;
    Node(int k, string v) : key(k), value(v), next(NULL) {}
};

class HashTable {
    Node *table[SIZE]; // array of chain heads

public:
    HashTable() {
        for (int i = 0; i < SIZE; i++) {
            table[i] = NULL;
        }
    }

    // Division method hash function
    int hashFunction(int key) {
        return key % SIZE;
    }

    // Insert(key, value) - new node added at the end of the chain
    void insert(int key, string value) {
        int index = hashFunction(key);
        Node *temp = table[index];

        // Duplicate key: update value
        while (temp != NULL) {
            if (temp->key == key) {
                temp->value = value;
                cout << "Key " << key << " already present. Value updated.\n";
                return;
            }
            temp = temp->next;
        }

        Node *newNode = new Node(key, value);
        if (table[index] == NULL) {
            table[index] = newNode;
        } else {
            cout << "Collision at index " << index << ". Chaining used.\n";
            temp = table[index];
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        cout << "Inserted (" << key << ", " << value << ") at index " << index << ".\n";
    }

    // Search(key)
    void search(int key) {
        int index = hashFunction(key);
        Node *temp = table[index];
        int pos = 1;

        while (temp != NULL) {
            if (temp->key == key) {
                cout << "Key " << key << " found. Value = " << temp->value
                     << " (index " << index << ", position " << pos << " in chain).\n";
                return;
            }
            temp = temp->next;
            pos++;
        }
        cout << "Key " << key << " not found.\n";
    }

    // Delete(key)
    void remove(int key) {
        int index = hashFunction(key);
        Node *curr = table[index];
        Node *prev = NULL;

        while (curr != NULL && curr->key != key) {
            prev = curr;
            curr = curr->next;
        }

        if (curr == NULL) {
            cout << "Key " << key << " not found. Nothing deleted.\n";
            return;
        }

        if (prev == NULL) {
            table[index] = curr->next; // deleting head node
        } else {
            prev->next = curr->next;   // deleting inner/last node
        }

        delete curr;
        cout << "Key " << key << " deleted from index " << index << ".\n";
    }

    // Display hash table
    void display() {
        cout << "\n--- Hash Table (Chaining) ---\n";
        for (int i = 0; i < SIZE; i++) {
            cout << "[" << i << "] ";
            Node *temp = table[i];
            if (temp == NULL) {
                cout << "NULL";
            }
            while (temp != NULL) {
                cout << "(" << temp->key << ", " << temp->value << ")";
                if (temp->next != NULL) {
                    cout << " -> ";
                }
                temp = temp->next;
            }
            cout << "\n";
        }
        cout << "-----------------------------\n";
    }
};

int main() {
    HashTable ht;
    int choice, key;
    string value;

    do {
        cout << "\n===== HASH TABLE USING CHAINING =====\n"
             << "1. Insert\n"
             << "2. Search\n"
             << "3. Delete\n"
             << "4. Display\n"
             << "5. Exit\n"
             << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter key (integer): ";
                cin >> key;
                cout << "Enter value (string): ";
                cin >> value;
                ht.insert(key, value);
                break;
            case 2:
                cout << "Enter key to search: ";
                cin >> key;
                ht.search(key);
                break;
            case 3:
                cout << "Enter key to delete: ";
                cin >> key;
                ht.remove(key);
                break;
            case 4:
                ht.display();
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
