#include <iostream>
#include <algorithm>

using namespace std;

int BinarySearch(int array[], int n, int key) {
    int low = 0;
    int high = n - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (array[mid] == key) {
            return mid;
        }

        if (array[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
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

    sort(array, array + n);
    cout << "\n";

    int key;
    cout << "Enter customer ID to search: ";
    cin >> key;

    int BinIndex = BinarySearch(array, n, key);

    if (BinIndex != -1) {
        cout << "[Binary Search] " << key << " found at index : " << BinIndex << endl;
    } else {
        cout << "[Binary Search] " << key << " not found" << endl;
    }

    delete[] array;

    return 0;
}
