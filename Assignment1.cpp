// Date: 07/01/2005, 10/01/2005
//2 3 4 -1 -1 -1 5 -1 -1
//1 5 6 4 -1 -1 -1 2 -1 -1 7 -1 -1
/*Beginning with an empty binary tree, Construct binary tree by inserting
the values in the order given. After constructing a binary tree perform
following operations on it-
Perform inorder, preorder and post order traversal
Change a tree so that the roles of the left and right pointers are swapped at every node
Find the height of tree
Copy this tree to another [operator=]
Count number of leaves, number of internal nodes.
Erase all nodes in a binary tree.
(Implement both recursive and non-recursive methods)*/
#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = nullptr;
        right = nullptr;
    }
};

Node* insert(Node* root) {
    int value;
    cout << "Enter the value for the node (-1 for no node): ";
    cin >> value;

    if (value == -1) {
        return nullptr;
    }

    root = new Node(value);

    cout << "Entering left of " << value << endl;
    root->left = insert(root->left);

    cout << "Entering right of " << value << endl;
    root->right = insert(root->right);

    return root;
}

void inorderTraversal(Node* root) {
    if (root != nullptr) {
        inorderTraversal(root->left);
        cout << root->data << " ";
        inorderTraversal(root->right);
    }

}

void preorderTraversal(Node* root, int& cnt) {
    if (root != nullptr) {
        cout << root->data << " ";
        if (root->left == nullptr && root->right == nullptr) {
            cnt++;
        }
        preorderTraversal(root->left, cnt);
        preorderTraversal(root->right, cnt);
    }
}

void postorderTraversal(Node* root) {
    if (root != nullptr) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        cout << root->data << " ";
    }
}

int heightOfTree(Node* root) {
    if (root == nullptr) {
        return -1;
    }
    int lheight = heightOfTree(root->left);
    int rheight = heightOfTree(root->right);

    return max(lheight, rheight) + 1;
}

void swapNodes(Node* node) {
    if (node == nullptr) {
        return;
    }
    swap(node->left, node->right);
    swapNodes(node->left);
    swapNodes(node->right);
}

Node* copy(Node* root) {
    if (root == nullptr) {
        return nullptr;
    }
    Node* temp = new Node(root->data);
    temp->left = copy(root->left);
    temp->right = copy(root->right);
    return temp;
}

void deleteTree(Node* root) {
    if (root == nullptr) {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);

    delete root;
}

void iterativePreorder(Node* root) {
    if (root == nullptr) {
        return;
    }

    stack<Node*> st;
    st.push(root);
    while (!st.empty()) {
        Node* curr = st.top();
        st.pop();
        cout << curr->data << " ";

        if (curr->right != nullptr) {
            st.push(curr->right);
        }
        if (curr->left != nullptr) {
            st.push(curr->left);
        }
    }
}

void iterativePostorder(Node* root) {
    if (root == nullptr) {
        return;
    }

    stack<Node*> s1;
    stack<Node*> s2;
    s1.push(root);
    while (!s1.empty()) {
        Node* top = s1.top();
        s1.pop();
        s2.push(top);
        if (top->left != nullptr) {
            s1.push(top->left);
        }
        if (top->right != nullptr) {
            s1.push(top->right);
        }
    }

    while (!s2.empty()) {
        Node* temp = s2.top();
        cout << temp->data << " ";
        s2.pop();
    }
}

void iterativeInorder(Node* root) {
    stack<Node*> st;
    Node* curr = root;

    while (curr != nullptr || !st.empty()) {
        while (curr != nullptr) {
            st.push(curr);
            curr = curr->left;
        }

        curr = st.top();
        st.pop();
        cout << curr->data << " ";
        curr = curr->right;
    }
}

int main() {
    Node* root = nullptr;
    Node* copiedTree = nullptr;
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert Node\n";
        cout << "2. Inorder Traversal\n";
        cout << "3. Preorder Traversal\n";
        cout << "4. Postorder Traversal\n";
        cout << "5. Iterative Inorder Traversal\n";
        cout << "6. Iterative Preorder Traversal\n";
        cout << "7. Iterative Postorder Traversal\n";
        cout << "8. Height of Tree\n";
        cout << "9. Number of Leaf Nodes\n";
        cout << "10. Swap Nodes\n";
        cout << "11. Create a Copy of Tree\n";
        cout << "12. Delete Tree\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            root = insert(root);
            break;
        case 2:
            cout << "Inorder Traversal: ";
            inorderTraversal(root);
            cout << endl;
            break;
        case 3: {
            int cnt = 0;
            cout << "Preorder Traversal: ";
            preorderTraversal(root, cnt);
            cout << endl;
            break;
        }
        case 4:
            cout << "Postorder Traversal: ";
            postorderTraversal(root);
            cout << endl;
            break;
        case 5:
            cout << "Iterative Inorder Traversal: ";
            iterativeInorder(root);
            cout << endl;
            break;
        case 6:
            cout << "Iterative Preorder Traversal: ";
            iterativePreorder(root);
            cout << endl;
            break;
        case 7:
            cout << "Iterative Postorder Traversal: ";
            iterativePostorder(root);
            cout << endl;
            break;
        case 8: {
            int height = heightOfTree(root);
            cout << "Height of Tree: " << height << endl;
            break;
        }
        case 9: {
            int cnt = 0;
            preorderTraversal(root, cnt);
            cout << "Number of Leaf Nodes: " << cnt << endl;
            break;
        }
        case 10:
            swapNodes(root);
            cout << "Nodes swapped successfully." << endl;
            break;
        case 11:
            copiedTree = copy(root);
            cout << "Tree copied successfully." << endl;
            break;
        case 12:
            deleteTree(root);
            root = nullptr;
            cout << "Tree deleted successfully." << endl;
            break;
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}
