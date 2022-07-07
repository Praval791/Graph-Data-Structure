#include <bits/stdc++.h>
using namespace std;

// TC -> O(N^2)
// SC -> O(2N)
vector<int> prims_brute(vector<pair<int, int>> adj[], int V)
{
    // key :- Index of minimum edge for given node (node represent by index)
    // mst :- Nodes that are already connected to spanning tree (node represent by index)
    vector<int> parent(V, -1), key(V, INT_MAX);
    vector<bool> mst(V, false);

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; ++count)
    {
        int minimumKey = INT_MAX, u = -1;
        for (int i = 0; i < V; ++i)
        {
            if (key[i] < minimumKey && !mst[i])
                minimumKey = key[i], u = i;
        }
        mst[u] = true;

        for (const auto &it : adj[u])
        {
            int neighbor = it.first;
            int weight = it.second;
            if (!mst[neighbor] && key[neighbor] > weight)
                key[neighbor] = weight, parent[neighbor] = u;
        }
    }
    return parent;
}

// TC -> O(N+E) + O(NlogN)
// SC -> O(2N + 2N)
vector<int> prims_optimize(vector<pair<int, int>> adj[], int V)
{
    // key :- Index of minimum edge for given node (node represent by index)
    // mst :- Nodes that are already connected to spanning tree (node represent by index)
    vector<int> parent(V, -1), key(V, INT_MAX);
    vector<bool> mst(V, false);
    // Min heap : (weight, vertex)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    key[0] = 0;
    parent[0] = -1;
    pq.push({0, 0});
    for (int count = 0; count < V - 1; ++count)
    {
        int u = pq.top().second;
        pq.pop();

        mst[u] = true;
        for (auto it : adj[u])
        {
            int neighbor = it.first;
            int weight = it.second;
            if (!mst[neighbor] && key[neighbor] > weight)
            {
                pq.push({weight, neighbor});
                key[neighbor] = weight, parent[neighbor] = u;
            }
        }
    }
    return parent;
}

class Disjoint_set
{
    int *parent, *rank;

public:
    Disjoint_set(int n)
    {
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; i++)
        {
            /* code */
            parent[i] = i;
            rank[i] = 0;
        }
    }
    int findParent(int i)
    {
        if (parent[i] == i)
            return i;
        return parent[i] = findParent(parent[i]);
    }

    void unnion(int comp1, int comp2)
    {
        int par1 = findParent(comp1), par2 = findParent(comp2);

        if (rank[par1] < rank[par2])
            parent[par1] = par2;
        else if (rank[par1] > rank[par2])
            parent[par2] = par1;
        else
            parent[par1] = par2, rank[comp1]++;
    }
};

vector<pair<int, int>> kruskals(vector<vector<int>> &edges, int V)
{
    // Sort all edges (weight u v)
    sort(edges.begin(), edges.end());
    Disjoint_set vertex(V);
    // int cost = 0;
    vector<pair<int, int>> mst;
    for (auto it : edges)
    {
        if (vertex.findParent(it[1]) != vertex.findParent(it[2]))
        {
            // cost += it[0];
            mst.push_back({it[1], it[2]});
            vertex.unnion(it[1], it[2]);
        }
    }
    return mst;
}

int main()
{
    int V, E;
    cout << "Enter number of vertices and edges: " << endl;
    cin >> V >> E;
    vector<pair<int, int>> adj[V];
    vector<vector<int>> edges(E);
    cout << "please enter as: vertex vertex weight :\n";
    for (int i = 0; i < E; i++)
    {
        int u, v, w;
        cin >> u >> v >> w;
        edges.push_back({w, u, v});
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }

    vector<int> ans = prims_brute(adj, V);
    vector<pair<int, int>> res = kruskals(edges, V);
    for (auto it : res)
        cout << it.first << "--" << it.second << endl;

    return 0;
}