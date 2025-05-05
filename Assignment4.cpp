/*Consider telephone book database of N clients. Make use of a hash table
implementation to quickly look up client‘s telephone number. Make use
of two collision handling techniques and compare them using number of

comparisons required to find a set of telephone numbers (Note: Use lin-
ear probing with replacement and without replacement)*/

/*Consider telephone book database of N clients. Make use of a hash table
implementation to quickly look up client‘s telephone number. Make use
of two collision handling techniques and compare them using number of

comparisons required to find a set of telephone numbers (Note: Use lin-
ear probing with replacement and without replacement)*/



#include<bits/stdc++.h>
using namespace std;

int modFxn(int number) {
    return number % 10;
}

int Search(vector<int>& a, int number) {
    int index = modFxn(number);
    int count = 0;
    while (a[index] != number && a[index] != 0) {
        count++;
        index = (index + 1) % 10;
    }
    return count;
}

void LPwithRInsertion(vector<int>& a, int number) {
    int index = modFxn(number);
    if (a[index] != 0) {
        if (modFxn(a[index]) == index) {
            while (a[index] != 0 && a[index] % 10 == index) {
                index = (index + 1) % 10;
            }
            int t = a[index];
            a[index] = number;
            number = t;
            index = (index + 1) % 10;
            a[index] = number;
        } else {
            int temp = a[index];
            a[index] = number;
            while (a[index] != 0) {
                index = (index + 1) % 10;
            }
            a[index] = temp;
        }
    } else {
        a[index] = number;
    }
}

void LPwithoutRInsertion(vector<int>& a, int number) {
    int index = modFxn(number);
    if (a[index] != 0) {
        while (a[index] != 0) {
            index = (index + 1) % 10;
        }
    }
    a[index] = number;
}

void printHashTable(const vector<int>& a) {
    for (int i = 0; i < a.size(); ++i) {
        cout << "Index " << i << ": " << a[i] << endl;
    }
}

void menudriven() {
    vector<int> hashforwithR(10, 0);
    vector<int> hashforwithoutR(10, 0);

    while (true) {
        cout << "--------------------------------" << endl;
        cout << "Enter Choice : " << endl;
        cout << "1. Enter the numbers in the register" << endl;
        cout << "2. Check the number of Comparisons in With Replacement" << endl;
        cout << "3. Check the number of Comparisons in Without Replacement" << endl;
        cout << "4. Print Tables" << endl;
        cout << "5. Exit" << endl;

        int choice;
        cin >> choice;

        if (choice == 1) {
            int number;
            cout << "Enter the Number to Insert :" << endl;
            cin >> number;
            LPwithRInsertion(hashforwithR, number);
            LPwithoutRInsertion(hashforwithoutR, number);
        }
        else if (choice == 2) {
            int number;
            cout << "Enter Number to Search : " << endl;
            cin >> number;
            cout << "Number of Comparisons required in with replacement technique are: ";
            cout << Search(hashforwithR, number) << endl;
        }
        else if (choice == 3) {
            int number;
            cout << "Enter Number to Search : " << endl;
            cin >> number;
            cout << "Number of Comparisons required in Without replacement technique are: ";
            cout << Search(hashforwithoutR, number) << endl;
        }
        else if (choice == 4) {
            cout << "With Replacement Hash Table:" << endl;
            printHashTable(hashforwithR);
            cout << "--------------------------------" << endl;
            cout << "Without Replacement Hash Table:" << endl;
            printHashTable(hashforwithoutR);
        }
        else if (choice == 5) {
            cout<<"Exiting the code..."
            break;
        }
        else {
            cout << "Invalid Choice" << endl;
        }
    }
}

int main() {
    menudriven();
    return 0;
}
