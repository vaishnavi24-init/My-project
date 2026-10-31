#include <iostream>
#include <string>
using namespace std;

struct Event {
    int eventId;
    string eventName;
    int priority;
    Event* next;
    Event* prev;
};

class EventQueue {
private:
    Event* front;
    Event* rear;
    int count;

public:
    EventQueue() {
        front = nullptr;
        rear = nullptr;
        count = 0;
    }

    bool isEmpty() {
        return front == nullptr;
    }

    void addEvent(int id, string name, int priority) {
        Event* newEvent = new Event{id, name, priority, nullptr, nullptr};

        if (isEmpty()) {
            front = rear = newEvent;
        } else {
            rear->next = newEvent;
            newEvent->prev = rear;
            rear = newEvent;
        }

        count++;
        cout << "Event [ID: " << id << ", \"" << name
             << "\"] added to the queue." << endl;
    }

    void processNextEvent() {
        if (isEmpty()) {
            cout << "No pending events to process. Queue is empty." << endl;
            return;
        }

        Event* temp = front;
        cout << "Processing Event -> ID: " << temp->eventId
             << ", Name: \"" << temp->eventName
             << "\", Priority: " << temp->priority << endl;

        front = front->next;

        if (front != nullptr)
            front->prev = nullptr;
        else
            rear = nullptr;

        delete temp;
        count--;
    }

    void displayPendingEvents() {
        if (isEmpty()) {
            cout << "No pending events. Queue is empty." << endl;
            return;
        }

        cout << "Pending Events (" << count << ") [Front -> Rear]:" << endl;

        Event* temp = front;
        int position = 1;

        while (temp != nullptr) {
            cout << position << ". ID: " << temp->eventId
                 << ", Name: \"" << temp->eventName
                 << "\", Priority: " << temp->priority << endl;

            temp = temp->next;
            position++;
        }
    }

    void cancelEvent(int id) {
        if (isEmpty()) {
            cout << "Cannot cancel. Queue is empty." << endl;
            return;
        }

        Event* temp = front;

        while (temp != nullptr && temp->eventId != id)
            temp = temp->next;

        if (temp == nullptr) {
            cout << "Event with ID " << id
                 << " not found." << endl;
            return;
        }

        if (temp->prev != nullptr)
            temp->prev->next = temp->next;
        else
            front = temp->next;

        if (temp->next != nullptr)
            temp->next->prev = temp->prev;
        else
            rear = temp->prev;

        cout << "Event [ID: " << id << ", \""
             << temp->eventName << "\"] has been cancelled." << endl;

        delete temp;
        count--;
    }

    ~EventQueue() {
        while (!isEmpty()) {
            Event* temp = front;
            front = front->next;
            delete temp;
        }
    }
};

void printMenu() {
    cout << "\n--------- Real-Time Event Processing System ---------" << endl;
    cout << "1. Add an Event" << endl;
    cout << "2. Process the Next Event" << endl;
    cout << "3. Display Pending Events" << endl;
    cout << "4. Cancel an Event" << endl;
    cout << "5. Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    EventQueue eq;
    int choice;

    do {
        printMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                int id, priority;
                string name;

                cout << "Enter Event ID: ";
                cin >> id;

                cout << "Enter Event Name: ";
                cin >> name;

                cout << "Enter Event Priority: ";
                cin >> priority;

                eq.addEvent(id, name, priority);
                break;
            }

            case 2:
                eq.processNextEvent();
                break;

            case 3:
                eq.displayPendingEvents();
                break;

            case 4: {
                int id;

                cout << "Enter Event ID to cancel: ";
                cin >> id;

                eq.cancelEvent(id);
                break;
            }

            case 5:
                cout << "Exiting Event Processing System." << endl;
                break;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 5);

    return 0;
}
