#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter number of members: ";
    cin >> n;

    int a[n];
    cout << "Enter borrow counts:\n";
    for (int i = 0; i < n; i++) cin >> a[i];

    int sum = 0, maxVal = a[0], minVal = a[0], zeroCount = 0;

    for (int i = 0; i < n; i++) {
        sum += a[i];
        if (a[i] > maxVal) maxVal = a[i];
        if (a[i] < minVal) minVal = a[i];
        if (a[i] == 0) zeroCount++;
    }

    // Mode calculation using nested loops
    int mode = a[0], maxFreq = 0;
    for (int i = 0; i < n; i++) {
        int count = 0;
        for (int j = 0; j < n; j++) {
            if (a[j] == a[i]) count++;
        }
        if (count > maxFreq) {
            maxFreq = count;
            mode = a[i];
        }
    }

    cout << "\nAverage: " << (float)sum / n
         << "\nMaximum: " << maxVal
         << "\nMinimum: " << minVal
         << "\nZero Borrow Count: " << zeroCount
         << "\nMode: " << mode << endl;

    return 0;
}
