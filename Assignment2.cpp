#include <bits/stdc++.h>
#include <iomanip>
using namespace std;

class Node {
public:
    pair<string, string> data;
    Node* left;
    Node* right;

    Node(pair<string, string> x) {
        data = x;
        left = nullptr;
        right = nullptr;
    }
};

void insert(Node*& root, Node* p) {
    if (root == nullptr) {
        root = p;
        return;
    }
    if (root->data.first > p->data.first) {
        insert(root->left, p);
    } else if (root->data.first < p->data.first) {
        insert(root->right, p);
    } else {
        cout << "No repetition is allowed in a binary search tree!" << endl;
    }
}

void displayAscending(Node* root) {
    if (root != nullptr) {
        displayAscending(root->left);
        cout << root->data.first << "\t" << root->data.second << endl;
        displayAscending(root->right);
    }
}

void displayDescending(Node* root) {
    if (root != nullptr) {
        displayDescending(root->right);
        cout << root->data.first << "\t" << root->data.second << endl;
        displayDescending(root->left);
    }
}

Node* findMin(Node* root) {
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}

Node* del(Node* root, string x) {
    if (root == nullptr)
        return root;

    if (x < root->data.first) {
        root->left = del(root->left, x);
    } else if (x > root->data.first) {
        root->right = del(root->right, x);
    } else {
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }

        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = del(root->right, temp->data.first);
    }
    return root;
}

void update(Node*& root, string oldData, pair<string, string> newData) {
    root = del(root, oldData);
    Node* newNode = new Node(newData);
    insert(root, newNode);
}

int findMaxComparisons(Node* root) {
    if (root == nullptr) {
        return 0;
    }
    int leftHeight = findMaxComparisons(root->left);
    int rightHeight = findMaxComparisons(root->right);
    return max(leftHeight, rightHeight) + 1;
}

int main() {
    Node* root = nullptr;
    int choice;
    string keyword, meaning, newKeyword;

    do {
        cout << "\n" << setw(30) << "MENU" << endl;
        cout << setw(30) << "1. Insert A Node" << endl;
        cout << setw(30) << "2. Ascending Order" << endl;
        cout << setw(30) << "3. Descending Order" << endl;
        cout << setw(30) << "4. Find Minimum" << endl;
        cout << setw(30) << "5. Delete A Node" << endl;
        cout << setw(30) << "6. Update A Node" << endl;
        cout << setw(30) << "7. Max Comparisons" << endl;
        cout << setw(30) << "8. Exit" << endl;

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter keyword: ";
                cin >> keyword;
                cout << "Enter meaning: ";
                cin.ignore();
                getline(cin, meaning);
                insert(root, new Node({keyword, meaning}));
                break;

            case 2:
                cout << "Displaying in Ascending Order:" << endl;
                displayAscending(root);
                break;

            case 3:
                cout << "Displaying in Descending Order:" << endl;
                displayDescending(root);
                break;

            case 4:
                if (root == nullptr) {
                    cout << "The dictionary is empty!" << endl;
                } else {
                    Node* minNode = findMin(root);
                    cout << "Minimum Keyword: " << minNode->data.first
                         << ", Meaning: " << minNode->data.second << endl;
                }
                break;

            case 5:
                cout << "Enter keyword to delete: ";
                cin >> keyword;
                root = del(root, keyword);
                break;

            case 6: {
                cout << "Enter old keyword: ";
                cin >> keyword;
                cout << "Enter new keyword: ";
                cin >> newKeyword;
                cout << "Enter new meaning: ";
                cin.ignore();
                getline(cin, meaning);
                update(root, keyword, {newKeyword, meaning});
                break;
            }

            case 7:
                cout << "Maximum comparisons needed for search: " << findMaxComparisons(root) << endl;
                break;

            case 8:
                cout << "Exiting the program." << endl;
                break;

            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 8);

    return 0;
}
