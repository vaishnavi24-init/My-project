#include <iostream>
using namespace std;

int LinearSearch(int array[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (array[i] == key) {
            return i;
        }
    }
    return -1;
}

int main() {
    int n;
    cout << "Enter number of customer Account ID's : ";
    cin >> n;

    int* array = new int[n];
    cout << "Enter customer account ID's :\n";
    for (int i = 0; i < n; i++) {
        cin >> array[i];
    }

    int key;
    cout << "Enter customer ID to search: ";
    cin >> key;

    int LinIndex = LinearSearch(array, n, key);

    if (LinIndex != -1) {
        cout << "[Linear Search] " << key << " found at index : " << LinIndex << endl;
    } else {
        cout << "[Linear Search] " << key << " not found" << endl;
    }

    delete[] array;

    return 0;
}
