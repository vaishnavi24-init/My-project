#include <iostream>
using namespace std;

int main() {
    int n;
    cout << "Enter no of employee: ";
    cin >> n;

    float salary[n], temp;
    cout << "Enter emp Salary: ";
    for (int i = 0; i < n; i++) {
        cin >> salary[i];
    }

    // Selection Sort Algorithm
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (salary[j] < salary[min]) {
                min = j;
            }
        }
        temp = salary[i];
        salary[i] = salary[min];
        salary[min] = temp;
    }

    cout << "\nSalaries after selection sort\n";
    for (int i = 0; i < n; i++) {
        cout << salary[i] << " ";
    }
    cout << endl;

    // Display Top 5 Highest Salaries
    cout << "Top 5 Highest Salary = ";
    int count = 0;
    for (int i = n - 1; i >= 0 && count < 5; i--) {
        cout << salary[i] << " ";
        count++;
    }

    return 0;
}
