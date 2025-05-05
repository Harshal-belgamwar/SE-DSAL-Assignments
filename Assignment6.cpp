/*Represent a given graph using adjacency list to perform DFS and BFS.
 Use the map of the area around the college as the graph. Identify the
 prominent landmarks as nodes and perform DFS and BFS on that.*/

#include <bits/stdc++.h>
using namespace std;

class Graph
{
	unordered_map<int, vector<int>> adj;
	unordered_map<int, bool> nodes;

public:
	void insertNode();
	void insertEdge(int v, int w);
	void DFS(int start);
	void BFS(int start);
	void DFSUtil(int v, unordered_set<int> &visited);
	void findDegrees();
};

void Graph::insertNode()
{
	int newNode;
	cout << "Enter the value of the new node: ";
	cin >> newNode;

	if (nodes.find(newNode) != nodes.end())
	{
		cout << "Node " << newNode << " already exists." << endl;
		return;
	}

	nodes[newNode] = true;
	cout << "Node " << newNode << " added." << endl;

	for (const auto &[existingNode, _] : nodes)
	{
		if (existingNode != newNode)
		{
			char isAdjacent;
			cout << "Is Node " << newNode << " adjacent to Node "
				 << existingNode << "? (y/n): ";
			cin >> isAdjacent;
			if (isAdjacent == 'y' || isAdjacent == 'Y')
			{
				insertEdge(newNode, existingNode);
			}
		}
	}
}

void Graph::insertEdge(int v, int w)
{
	adj[v].push_back(w);
	adj[w].push_back(v);
}

void Graph::DFSUtil(int v, unordered_set<int> &visited)
{
	visited.insert(v);
	cout << v << " ";

	for (int neighbor : adj[v])
	{
		if (visited.find(neighbor) == visited.end())
		{
			DFSUtil(neighbor, visited);
		}
	}
}

void Graph::DFS(int start)
{
	unordered_set<int> visited;
	cout << "DFS Traversal starting from node " << start << ": ";
	DFSUtil(start, visited);
	cout << endl;
}

void Graph::BFS(int start)
{
	unordered_set<int> visited;
	queue<int> q;

	visited.insert(start);
	q.push(start);

	cout << "BFS Traversal starting from node " << start << ": ";

	while (!q.empty())
	{
		int node = q.front();
		q.pop();
		cout << node << " ";

		for (int neighbor : adj[node])
		{
			if (visited.find(neighbor) == visited.end())
			{
				visited.insert(neighbor);
				q.push(neighbor);
			}
		}
	}
	cout << endl;
}

void Graph::findDegrees()
{
	cout << "Degrees of nodes:" << endl;
	for (const auto &pair : adj)
	{
		cout << "Node " << pair.first << " has degree " << pair.second.size()
			 << endl;
	}
}

int main()
{
	Graph g;
	int choice, startNode;

	do
	{
		cout << "\nMENU: " << endl;
		cout << "1. Insert a Node" << endl;
		cout << "2.Perform DFS" << endl;
		cout << "3.Perform BFS" << endl;
		cout << "4. Degree of Nodes" << endl;
		cout << "5. Exit" << endl;
		cout << "Enter your choice" << endl;
		cin >> choice;

		switch (choice)
		{
		case 1:
			g.insertNode();
			break;
		case 2:
			cout << "Enter the start node of DFS: ";
			cin >> startNode;
			g.DFS(startNode);
			break;
		case 3:
			cout << "Enter the start node for BFS";
			cin >> startNode;
			g.BFS(startNode);
			break;
		case 4:
			cout << "Degree of each node is: " << endl;
			g.findDegrees();
			break;
		case 5:
			cout << "Exiting the program..." << endl;
			break;
		default:
			cout << "Invalid choice! Please enter a valid option." << endl;
		}
	} while (choice != 5);
	return 0;
}
