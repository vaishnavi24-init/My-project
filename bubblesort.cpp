#include <iostream>
#include <vector>
#include <iomanip> // Step 1: Required for fixed and setprecision

using namespace std;

int main() {
    int n;
    cout << "Enter no of employee : ";
    cin >> n;

    vector<float> salary(n);
    float temp;

    cout << "Enter employee salary : ";
    for(int i = 0; i < n; i++) {
        cin >> salary[i];
    }

    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(salary[j] > salary[j + 1]) {
                temp = salary[j];
                salary[j] = salary[j + 1];
                salary[j + 1] = temp;
            }
        }
    }

    cout << fixed << setprecision(2);

    cout << "\nSalaries after Bubble sort \n";
    for(int i = 0; i < n; i++) {
        cout << salary[i] << " ";
    }
    cout << endl;

    cout << "\nTop 5 Highest Salary = ";
    int count = 0;
    int limit = (n < 5) ? n : 5;
    for(int i = n - 1; i >= 0 && count < limit; i--) {
        cout << salary[i] << " ";
        count++;
    }
    cout << endl;

    return 0;
}
