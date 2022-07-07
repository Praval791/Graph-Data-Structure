#include <bits/stdc++.h>
using namespace std;

// Works on directed graphs only.
// * KOSARAJU'S Algorithm is used for finding the strongly connected components of a graph
// ! TC :- O(N+E)
// ! SC :- O(N) + O(N) + O(N + E)

void dfsUtil(int node, vector<bool> &visited, vector<int> transpose[], vector<int> &ans)
{
    ans.push_back(node);
    visited[node] = true;
    for (auto it : transpose[node])
    {
        if (!visited[it])
        {
            dfsUtil(it, visited, transpose, ans);
        }
    }
}

void dfsTopoSort(int node, vector<bool> &visited, stack<int> &stk, vector<int> adj[])
{
    visited[node] = true;
    for (auto it : adj[node])
        if (!visited[it])
            dfsTopoSort(it, visited, stk, adj);

    stk.push(node);
}

vector<vector<int>> kosaraju_algo(vector<int> adj[], int V)
{
    vector<vector<int>> SCCs;
    // * Step 1: Sort the nodes in order of finishing time
    // ! TC :- O(N)
    vector<bool> visited(V, false);
    stack<int> stk;

    for (int i = 0; i < V; i++)
        if (!visited[i])
            dfsTopoSort(i, visited, stk, adj);

    // * Step 2: Find transpose of graph
    // ! TC :- O(N+E)
    vector<int> transpose[V];
    for (int i = 0; i < V; i++)
    {
        visited[i] = 0;
        for (auto it : adj[i])
            transpose[it].push_back(i);
    }

    // * Step 3: do DFS According to finishing time (last finish first do DFS)
    // ! TC :- O(N+E)
    while (!stk.empty())
    {
        int node = stk.top();
        stk.pop();
        if (!visited[node])
        {
            vector<int> oneSCC;
            dfsUtil(node, visited, transpose, oneSCC);
            SCCs.push_back(oneSCC);
        }
    }
    return SCCs;
}

int main()
{
    int V, E;
    cout << "Enter number of vertices and edges: " << endl;
    cin >> V >> E;
    vector<int> adj[V];
    cout << "please enter as: vertex vertex :\n";
    for (int i = 0; i < E; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[v].push_back(u);
    }
    vector<vector<int>> stronglyConnectedComponents = kosaraju_algo(adj, V);
    cout << "All strongly connected components of given graph are :\n";
    for (int i = 0; i < stronglyConnectedComponents.size(); i++)
    {
        cout << i + 1 << " : ";
        for (auto node : stronglyConnectedComponents[i])
            cout << node << " ";
        cout << endl;
    }

    return 0;
}
