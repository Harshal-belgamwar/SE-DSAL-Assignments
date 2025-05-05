
/*A Dictionary stores keywords & its meanings. Provide facility for adding new keywords, deleting keywords, updating values of any
entry. Provide facility to display whole data sorted in ascending/ Descending order. Also find how many maximum comparisons may
require for finding any keyword. Use Height balance tree and find the complexity for finding a keyword.*/

#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    string keyword, meaning;
    Node *left, *right;
    int height;

    Node(string k, string m)
    {
        keyword = k;
        meaning = m;
        left = right = nullptr;
        height = 1;
    }
};

class AVLTree
{
public:
    Node *root;

    AVLTree() { root = nullptr; }

    int height(Node *n) { return n ? n->height : 0; }

    int balanceFactor(Node *n) { return n ? height(n->left) - height(n->right) : 0; }

    Node *rotateRight(Node *y)
    {
        Node *x = y->left;
        Node *T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        cout << "Balance Factor of node " << x->keyword << ": " << balanceFactor(x) << endl;
        cout << "Balance Factor of node " << y->keyword << ": " << balanceFactor(y) << endl;

        return x;
    }

    Node *rotateLeft(Node *x)
    {
        Node *y = x->right;
        Node *T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        cout << "Balance Factor of node " << x->keyword << ": " << balanceFactor(x) << endl;
        cout << "Balance Factor of node " << y->keyword << ": " << balanceFactor(y) << endl;

        return y;
    }

    Node *insert(Node *node, string k, string m)
    {
        if (!node)
        {
            return new Node(k, m);
        }
        if (k < node->keyword)
        {
            node->left = insert(node->left, k, m);
        }
        else if (k > node->keyword)
        {
            node->right = insert(node->right, k, m);
        }
        else
        {
            node->meaning = m;
            return node;
        }

        node->height = max(height(node->left), height(node->right)) + 1;
        int balance = balanceFactor(node);

        cout << "Balance Factor of node " << node->keyword << ": " << balanceFactor(node) << endl;

        if (balance > 1 && k < node->left->keyword)
        {
            return rotateRight(node);
        }
        if (balance < -1 && k > node->right->keyword)
        {
            return rotateLeft(node);
        }
        if (balance > 1 && k > node->left->keyword)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }
        if (balance < -1 && k < node->right->keyword)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }

    Node *minValueNode(Node *node)
    {
        Node *current = node;
        while (current->left)
        {
            current = current->left;
        }
        return current;
    }

    Node *deleteNode(Node *root, string k)
    {
        if (!root)
        {
            return root;
        }
        if (k < root->keyword)
        {
            root->left = deleteNode(root->left, k);
        }
        else if (k > root->keyword)
        {
            root->right = deleteNode(root->right, k);
        }
        else
        {
            if (!root->left || !root->right)
            {
                Node *temp = root->left ? root->left : root->right;
                if (!temp)
                {
                    temp = root;
                    root = nullptr;
                }
                else
                    *root = *temp;
                delete temp;
            }
            else
            {
                Node *temp = minValueNode(root->right);
                root->keyword = temp->keyword;
                root->meaning = temp->meaning;
                root->right = deleteNode(root->right, temp->keyword);
            }
        }
        if (!root)
        {
            return root;
        }
        root->height = max(height(root->left), height(root->right)) + 1;
        int balance = balanceFactor(root);

        if (balance > 1 && balanceFactor(root->left) >= 0)
        {
            return rotateRight(root);
        }
        if (balance > 1 && balanceFactor(root->left) < 0)
        {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
        if (balance < -1 && balanceFactor(root->right) <= 0)
            return rotateLeft(root);
        if (balance < -1 && balanceFactor(root->right) > 0)
        {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
        return root;
    }

    void inorder(Node *root)
    {
        if (root)
        {
            inorder(root->left);
            cout << root->keyword << " : " << root->meaning << " (Balance Factor: " << balanceFactor(root) << ")\n";
            inorder(root->right);
        }
    }

    void reverseInorder(Node *root)
    {
        if (root)
        {
            reverseInorder(root->right);
            cout << root->keyword << " : " << root->meaning << " (Balance Factor: " << balanceFactor(root) << ")\n";
            reverseInorder(root->left);
        }
    }

    Node *search(Node *root, string k, int &comparisons)
    {
        if (!root || root->keyword == k)
        {
            comparisons++;
            return root;
        }
        comparisons++;
        if (k < root->keyword)
        {
            return search(root->left, k, comparisons);
        }
        return search(root->right, k, comparisons);
    }
};

int main()
{
    AVLTree dict;
    int choice;
    string keyword, meaning;
    do
    {
        cout << "\nMENU\n";
        cout << "1. Insert a word\n";
        cout << "2. Search for a word\n";
        cout << "3. Delete a word\n";
        cout << "4. Display Dictionary (Ascending order)\n";
        cout << "5. Display dictionary (Descending Order)\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
            cout << "Enter Keyword: ";
            getline(cin, keyword);
            cout << "Enter meaning: ";
            getline(cin, meaning);
            dict.root = dict.insert(dict.root, keyword, meaning);
            cout << "Word inserted successfully!\n";
            cout << "Current Dictionary:\n";
            dict.inorder(dict.root);
            break;

        case 2:
        {
            cout << "Enter keyword to search: ";
            getline(cin, keyword);
            int comparisons = 0;
            Node *res = dict.search(dict.root, keyword, comparisons);
            if (res)
            {
                cout << "Found: " << res->keyword << " -> " << res->meaning << " (Comparisons: " << comparisons << ")\n";
            }
            else
            {
                cout << "Word not found in the dictionary.\n";
            }
            break;
        }

        case 3:
            cout << "Enter keyword to delete: ";
            getline(cin, keyword);
            dict.root = dict.deleteNode(dict.root, keyword);
            cout << "Word deleted (if it existed).\n";
            break;

        case 4:
            cout << "Dictionary in Ascending Order:\n";
            dict.inorder(dict.root);
            break;

        case 5:
            cout << "Dictionary in Descending Order:\n";
            dict.reverseInorder(dict.root);
            break;

        case 6:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 6);

    return 0;
}
