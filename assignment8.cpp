/*Given sequence k = k1 <k2 < … <kn of n sorted keys, with a successful and unsuccessful search probability pi and qi for each key ki. Build the Binary search tree that has the least search cost given the access probability for each key.*/

#include <bits/stdc++.h>
using namespace std;

class OBST
{
public:
    int n;
    vector<float> p, q;
    vector<vector<float>> wt, c;
    vector<vector<int>> r;

    void inputProbabilities()
    {
        cout << "\nEnter the number of keys: ";
        cin >> n;
        p.resize(n + 1);
        q.resize(n + 1);
        wt.assign(n + 1, vector<float>(n + 1, 0));
        c.assign(n + 1, vector<float>(n + 1, 0));
        r.assign(n + 1, vector<int>(n + 1, 0));

        cout << "\nEnter the probability for successful search:\n";
        for (int i = 1; i <= n; i++)
        {
            cout << "p[" << i << "]: ";
            cin >> p[i];
        }

        cout << "\nEnter the probability for unsuccessful search:\n";
        for (int i = 0; i <= n; i++)
        {
            cout << "q[" << i << "]: ";
            cin >> q[i];
        }
    }

    void constructOBST()
    {
        for (int i = 0; i < n; i++)
        {
            c[i][i] = 0.0;
            r[i][i] = 0;
            wt[i][i] = q[i];
            wt[i][i + 1] = q[i] + q[i + 1] + p[i + 1];
            c[i][i + 1] = wt[i][i + 1];
            r[i][i + 1] = i + 1;
        }
        c[n][n] = 0.0;
        r[n][n] = 0;
        wt[n][n] = q[n];

        for (int length = 2; length <= n; length++)
        {
            for (int i = 0; i <= n - length; i++)
            {
                int j = i + length;
                wt[i][j] = wt[i][j - 1] + p[j] + q[j];
                c[i][j] = FLT_MAX;
                for (int k = i + 1; k <= j; k++)
                {
                    float cost = c[i][k - 1] + c[k][j];
                    if (cost < c[i][j])
                    {
                        c[i][j] = cost;
                        r[i][j] = k;
                    }
                }
                c[i][j] += wt[i][j];
            }
        }
        cout << "\nOptimal BST Constructed Successfully!";
        cout << "\nMinimum Cost of OBST: " << c[0][n];
        cout << "\nRoot of OBST: " << r[0][n] << endl;
    }

    void printTree(int left, int right)
    {
        if (left >= right)
            return;

        if (r[left][r[left][right] - 1] != 0)
            cout << "\n Left child of " << r[left][right] << " :: " << r[left][r[left][right] - 1];

        if (r[r[left][right]][right] != 0)
            cout << "\n Right child of " << r[left][right] << " :: " << r[r[left][right]][right];

        printTree(left, r[left][right] - 1);
        printTree(r[left][right], right);
    }

    void print_COST()
    {
        int n = c.size();
        int m = c[0].size();
        cout << "Cost Matrix is: \n";
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                cout << c[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    OBST obst;
    int choice;

    do
    {
        cout << "Enter your choice: \n";
        cout << "1. Enter probabilities\n";
        cout << "2. Display Optimal BST Structure\n";
        cout << "3. Display Cost Matrix\n";
        cout << "4. Exit\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            obst.inputProbabilities();
            obst.constructOBST();
            break;
        case 2:
            cout << "\nOptimal BST Structure:";
            obst.printTree(0, obst.n);
            cout << endl;
            break;
        case 3:
            obst.print_COST();
            break;
        case 4:
            cout << "Exiting the program..." << endl;
            break;
        }
    } while (choice != 4);
    return 0;
}

/*#include<bits/stdc++.h>
using namespace std;

class KeyInfo
{
public:
    int k;
    double p, q;
    KeyInfo(int k, double p) : k(k), p(p), q(1 - p) {}
};

class OBST
{
public:
    vector<KeyInfo> keys;
    int n;

    OBST(vector<KeyInfo> &keys){
        this->keys = keys;
        this->n = keys.size();
    }


    void constructOBST()
    {
        vector<vector<double>> cost(n + 1, vector<double>(n + 1, 0));
        vector<vector<int>> root(n + 1, vector<int>(n + 1, 0));

        // Initialize cost for single keys
        for (int i = 0; i < n; i++)
        {
            cost[i][i] = keys[i].p;
        }

        // Initialize the cost for the case where no keys are present (empty subtrees)
        for (int i = 1; i <= n; i++)
        {
            cost[i][i - 1] = keys[i - 1].q;
        }

        // Fill the cost and root tables
        for (int len = 1; len <= n; len++)
        {
            for (int i = 0; i <= n - len; i++)
            {
                int j = i + len - 1;

                // Sum of probabilities from i to j
                double sumP = 0;
                for (int k = i; k <= j; k++)
                {
                    sumP += keys[k].p;
                }

                cost[i][j] = INT_MAX;
                for (int r = i; r <= j; r++)
                {
                    double leftCost = (r > i) ? cost[i][r - 1] : 0;
                    double rightCost = (r < j) ? cost[r + 1][j] : 0;
                    double totalCost = leftCost + rightCost + sumP;

                    // cost [i][j] = min(cost[i][j], totalCost)
                    if (totalCost < cost[i][j])
                    {
                        cost[i][j] = totalCost;
                        root[i][j] = r;
                    }
                }
            }
        }

        cout << "Minimum search cost: " << cost[0][n - 1] << endl;
        printOptimalBST(root, 0, n - 1);
    }

    void printOptimalBST(const vector<vector<int>> &root, int i, int j)
    {
        if (i > j)
            return;

        int r = root[i][j];
        cout << "Root of subtree [" << keys[i].k << ", " << keys[j].k << "] is " << keys[r].k << endl;

        printOptimalBST(root, i, r - 1);
        printOptimalBST(root, r + 1, j);
    }
};

int main()
{

    vector<KeyInfo> keys;
    OBST *obst = nullptr;
    int choice, n, k;
    double p;

    do
    {
        cout << "\n--- Optimal BST Menu ---" << endl;
        cout << "1. Enter keys and probabilities" << endl;
        cout << "2. Construct OBST and Display Results" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            // Input number of keys
            cout << "Enter the number of keys: ";
            cin >> n;
            keys.clear();

            cout << "Enter each key followed by its probability (p):" << endl;

            for (int i = 0; i < n; i++)
            {
                cout << "Enter key " << i + 1 << ": ";
                cin >> k;
                cout << "Enter probabililty for key " << k << ": ";
                cin >> p;
                keys.push_back(KeyInfo(k, p));
            }

            obst = new OBST(keys);
            cout << "Keys and probabililtes entered successfully." << endl;
            break;

        case 2:

            if (obst == nullptr)
            {
                cout << "No keys and probabilities entered yet. Please enter them first." << endl;
            }
            else
            {
                obst->constructOBST();
            }
            break;

        case 3:
            cout << "Exiting the program." << endl;
            break;

        default:
            cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 3);

    return 0;
}*/