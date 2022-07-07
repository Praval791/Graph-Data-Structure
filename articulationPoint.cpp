#include <bits/stdc++.h>
using namespace std;

void dfsUtil(int node, int parent, vector<bool> &visited, vector<int> &low, vector<int> &tin, int timer, vector<int> adj[], unordered_set<int> &articulations_points)
{
    visited[node] = true;
    tin[node] = low[node] = timer++;
    int child = 0;
    for (auto it : adj[node])
    {
        if (it == parent)
            continue;
        if (!visited[it])
        {
            dfsUtil(it, node, visited, low, tin, timer, adj, articulations_points);
            low[node] = min(low[node], low[it]);
            if (parent != -1 && low[it] >= tin[node])
                articulations_points.insert(node);
            child++;
        }
        else
            low[node] = min(low[node], tin[it]);
    }
    if (parent != -1 && child > 1)
        articulations_points.insert(node);
}

unordered_set<int> dfsForAP(vector<int> adj[], int V)
{
    // tin :- stores time of insertion of nodes (we don't update them)
    // low :- stores lowest possible time to reach them (we can update them)
    unordered_set<int> articulations_points;
    vector<int> tin(V + 1, -1), low(V + 1, -1);
    vector<bool> visited(V + 1, false);

    for (int i = 0; i < V; i++)
    {
        if (!visited[i])
            dfsUtil(i, -1, visited, low, tin, 0, adj, articulations_points);
    }
    return articulations_points;
}

int main()
{
    int V, E;
    cout << "Enter number of vertices and edges: " << endl;
    cin >> V >> E;
    vector<int> adj[V + 1];
    cout << "please enter as: vertex vertex :\n";
    for (int i = 0; i < E; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    unordered_set<int> articulations_points = dfsForAP(adj, V);
    cout << "Articulations points :\n";
    for (auto it : articulations_points)
        cout << it << endl;
    return 0;
}