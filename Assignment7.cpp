/*You have a business with several offices; you want to lease phone lines to connect them up with each other; and the phone company charges different amounts of money
to connect different pairs of cities. You want a set of lines that connects all your offices with a minimum total cost. Solve the problem by suggesting appropriate data structures.*/

//0 1 2, 0 3 6, 1 2 3, 1 3 8, 1 4 5, 2 4 7, 3 4 9
#include <bits/stdc++.h>
using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adjMatrix;
    vector<vector<int>> edges;

public:
    Graph(int V) : V(V) {
        adjMatrix.resize(V, vector<int>(V, 0));
    }

    void addEdge(int u, int v, int w) {
        adjMatrix[u][v] = w;
        adjMatrix[v][u] = w;
        edges.push_back({u, v, w});
    }

    void displayGraph() {
        cout << "Adjacency Matrix:\n";
        for (const auto& row : adjMatrix) {
            for (int val : row)
                cout << val << " ";
            cout << "\n";
        }
    }

    int findMinKeyVertex(const vector<int>& key, const vector<bool>& inMST) {
        int minKey = INT_MAX, minIndex = -1;
        for (int v = 0; v < V; v++) {
            if (!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                minIndex = v;
            }
        }
        return minIndex;
    }

    void primMST() {
        vector<int> parent(V, -1), key(V, INT_MAX);
        vector<bool> inMST(V, false);
        key[0] = 0;

        for (int count = 0; count < V - 1; count++) {
            int u = findMinKeyVertex(key, inMST);
            inMST[u] = true;

            for (int v = 0; v < V; v++) {
                if (adjMatrix[u][v] && !inMST[v] && adjMatrix[u][v] < key[v]) {
                    parent[v] = u;
                    key[v] = adjMatrix[u][v];
                }
            }
        }

        cout << "Prim's MST:\nEdge\tWeight\n";
        for (int i = 1; i < V; i++)
            cout << parent[i] << " - " << i << "\t" << adjMatrix[parent[i]][i] << "\n";
    }

    int find(int i, vector<int>& parent) {
        return (parent[i] == i) ? i : (parent[i] = find(parent[i], parent));
    }

    void unite(int x, int y, vector<int>& parent, vector<int>& rank) {
        int rootX = find(x, parent), rootY = find(y, parent);
        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY])
                parent[rootX] = rootY;
            else if (rank[rootX] > rank[rootY])
                parent[rootY] = rootX;
            else {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

    int kruskalsMST() {
        sort(edges.begin(), edges.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[2] < b[2];
        });

        vector<int> parent(V), rank(V, 1);
        iota(parent.begin(), parent.end(), 0);

        int mstCost = 0, edgeCount = 0;

        for (const auto& edge : edges) {
            int u = edge[0], v = edge[1], w = edge[2];

            if (find(u, parent) != find(v, parent)) {
                unite(u, v, parent, rank);
                mstCost += w;
                if (++edgeCount == V - 1) break;
            }
        }

        return mstCost;
    }
};

int main() {
    int V, choice, u, v, w;
    cout << "Enter number of vertices: ";
    cin >> V;

    Graph g(V);

    do {
        cout << "\nMenu:\n1. Add Edge\n2. Display Graph\n3. Prim's MST\n4. Kruskal's MST\n5. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter edge (u v weight): ";
                cin >> u >> v >> w;
                g.addEdge(u, v, w);
                break;
            case 2:
                g.displayGraph();
                break;
            case 3:
                g.primMST();
                break;
            case 4:
                cout << "Kruskal's MST Cost: " << g.kruskalsMST() << "\n";
                break;
        }
    } while (choice != 5);

    return 0;
}
