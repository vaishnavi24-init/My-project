#include <iostream>
#include <string>
using namespace std;

const int MAX = 50;

class Stack {
    string data[MAX];
    int top;

public:
    Stack() {
        top = -1;
    }

    bool isEmpty() {
        return top == -1;
    }

    bool isFull() {
        return top == MAX - 1;
    }

    void push(string s) {
        if (isFull()) {
            cout << "Stack is full!" << endl;
            return;
        }
        data[++top] = s;
    }

    string pop() {
        if (isEmpty()) {
            return "";
        }
        return data[top--];
    }

    void clear() {
        top = -1;
    }
};

int main() {
    Stack undoStack, redoStack;
    string currentState = "";
    int choice;
    string input;

    cout << "=== Real-Time Undo/Redo Text Editor (Stack-based) ===" << endl;

    do {
        cout << "\nCurrent Document: \"" << currentState << "\"" << endl;
        cout << "1. Make a Change" << endl;
        cout << "2. Undo Action" << endl;
        cout << "3. Redo Action" << endl;
        cout << "4. Display Current Document" << endl;
        cout << "5. Exit" << endl;
        cout << "\nEnter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter text to add: ";
                getline(cin, input);
                undoStack.push(currentState);
                currentState = currentState + input;
                redoStack.clear();
                cout << "Change made successfully." << endl;
                break;

            case 2:
                if (undoStack.isEmpty()) {
                    cout << "Nothing to undo!" << endl;
                } else {
                    redoStack.push(currentState);
                    currentState = undoStack.pop();
                    cout << "Undo successful." << endl;
                }
                break;

            case 3:
                if (redoStack.isEmpty()) {
                    cout << "Nothing to redo!" << endl;
                } else {
                    undoStack.push(currentState);
                    currentState = redoStack.pop();
                    cout << "Redo successful." << endl;
                }
                break;

            case 4:
                cout << "Current Document State: \"" << currentState << "\"" << endl;
                break;

            case 5:
                cout << "Exiting the editor..." << endl;
                break;

            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}
