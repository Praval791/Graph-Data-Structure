#include <bits/stdc++.h>
using namespace std;

// lowest possible time for a adjacent(it) is less then the insertion time of the node(parent) that means we can reach to the adjacent(it) before the insertion of node therfore there is no need to kill that edge hence we can reach adjacent(it) with other edge that's why we get the lowest possible time lower than the insertion time of node
// that means if the lowest possible time is greater than the insertion time that means we can only reach the adjacent(it) with the path that have parent(node)

void dfsUtil(int node, int parent, vector<bool> &visited, vector<int> &low, vector<int> &tin, int timer, vector<int> adj[], vector<pair<int, int>> &bridges)
{
    visited[node] = true;
    tin[node] = low[node] = timer++;
    for (auto it : adj[node])
    {
        if (it == parent)
            continue;
        if (!visited[it])
        {
            dfsUtil(it, node, visited, low, tin, timer, adj, bridges);
            low[node] = min(low[node], low[it]);
            if (low[it] > tin[node])
                bridges.push_back({node, it});
        }
        else
            low[node] = min(low[node], tin[it]);
    }
}

vector<pair<int, int>> dfsForBridges(vector<int> adj[], int V)
{
    vector<pair<int, int>> bridges;
    vector<bool> visited(V + 1, false);
    // tin :- stores time of insertion of nodes (we don't update them)
    // low :- stores lowest possible time to reach them (we can update them)
    vector<int> low(V + 1, -1), tin(V + 1, -1);
    int timer = 0;
    for (int i = 0; i < V; i++)
    {
        if (!visited[i])
            dfsUtil(i, -1, visited, low, tin, timer, adj, bridges);
    }
    return bridges;
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
    cout << "JBB" << endl;
    vector<pair<int, int>> bridges = dfsForBridges(adj, V);
    if (!bridges.empty())
        cout << "Edges that are Bridges if graph :\n";
    for (auto it : bridges)
        cout << it.first << "--" << it.second << endl;
    return 0;
}