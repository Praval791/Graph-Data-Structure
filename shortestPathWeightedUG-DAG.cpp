#include <bits/stdc++.h>
using namespace std;

#define INF INT_MAX
// TC -> O[N+E]*2
// Sc => O[N]+O[N]
void findTopoSort(int node, vector<pair<int, int>> adj[], vector<bool> &visited, stack<int> &stk)
{
    visited[node] = true;
    for (auto it : adj[node])
        if (!visited[it.first])
            findTopoSort(it.first, adj, visited, stk);
    stk.push(node);
}

vector<int> shortestPathDirectedWeightedGraph(vector<pair<int, int>> adj[], int V, int src)
{
    vector<bool> visited(V, false);
    stack<int> stk;
    for (int i = 0; i < V; i++)
        if (!visited[i])
            findTopoSort(i, adj, visited, stk);

    vector<int> shortestDist(V, INF);
    shortestDist[src] = 0;
    while (!stk.empty())
    {
        int node = stk.top();
        stk.pop();
        if (shortestDist[node] != INF)
            for (auto it : adj[node])
                if (shortestDist[it.first] > shortestDist[node] + it.second)
                    shortestDist[it.first] = shortestDist[node] + it.second;
    }
    return shortestDist;
}

// TC -> O[N+E]*logN
// Sc => O[N]+O[N]
// * DJISKTRA's algorithm work for undirected graph and directed as well
// ! DJISKTRA's algorithm does not work with negative weights
vector<int> Djisktra(vector<pair<int, int>> adj[], int V, int src)
{
    vector<int> distFromSrc(V, INF);
    // Min-Heap    : (distance, node)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    distFromSrc[src] = 0;
    pq.push({0, src});
    while (!pq.empty())
    {
        int distance = pq.top().first;
        int prev = pq.top().second;
        pq.pop();
        for (auto it : adj[prev])
        {
            int neighbour = it.first;
            int weight = it.second;
            if (distFromSrc[neighbour] > weight + distFromSrc[prev])
            {
                distFromSrc[neighbour] = weight + distFromSrc[prev];
                pq.push({distFromSrc[neighbour], neighbour});
            }
        }
    }
    return distFromSrc;
}

// * Bellman Ford Algorithm work on every type of weight
// !  Detect Negative weight cycle in Graph because this is not work if there is an negative weight cycle
// TC :- O(N-1 * (E))
// SC :- O()
vector<int> Bellman_Ford(vector<vector<int>> &edges, int V, int src)
{
    vector<int> distFromSrc(V, INF);
    distFromSrc[src] = 0;
    for (int i = 1; i < V; i++) // do relax V-1 times
        for (auto edge : edges)
            if (distFromSrc[edge[1]] > distFromSrc[edge[0]] + edge[2])
                distFromSrc[edge[1]] = distFromSrc[edge[0]] + edge[2];

    for (auto edge : edges)
        if (distFromSrc[edge[1]] > distFromSrc[edge[0]] + edge[2])
            return {};
    return distFromSrc;
}

// { Driver Code Starts.
int main()
{
    bool directed;
    cout << "Directed, then press 1:\nUndirected, then press 0:\n";
    cin >> directed;
    bool havingNegativeEdge;
    cout << "If there is a negative edge then, press 1:\n otherwise, press 0:\n";
    cin >> havingNegativeEdge;
    int V, E;
    cout << "Enter number of vertices and edges: " << endl;
    cin >> V >> E;

    if (directed)
    {
        vector<pair<int, int>> adj[V];
        vector<vector<int>> edges(E, vector<int>(3));
        cout << "please enter u -> v then weight of edge:\n";
        for (int i = 0; i < E; i++)
        {
            int u, v, w;
            cin >> u >> v >> w;
            edges.push_back({u, v, w});
            adj[u].push_back({v, w});
        }
        int src;
        cout << "Enter Source node: " << endl;
        cin >> src;
        // Solution1 obj;
        vector<int> ans;
        if (havingNegativeEdge)
            ans = Bellman_Ford(edges, V, src);
        else
            ans = shortestPathDirectedWeightedGraph(adj, V, src);
        if (ans.size() == 0)
            cout << "Source is a isolated vertex or there may be Negative weight Cycle\n";
        else
        {
            cout << "The distances from source, " << src << " are : \n";
            for (int i = 0; i < V; i++)
                if (ans[i] == INF)
                    cout << "there is no path from " << src << " to " << i << "\n";
                else
                    cout << ans[i] << "\n";
        }
    }
    else
    {

        vector<pair<int, int>> adj[V];
        vector<vector<int>> edges(E, vector<int>(3));
        cout << "please enter as: vertex vertex weight :\n";
        for (int i = 0; i < E; i++)
        {
            int u, v, w;
            cin >> u >> v >> w;
            edges.push_back({u, v, w});
            edges.push_back({v, u, w});
            adj[u].push_back({v, w});
            adj[v].push_back({u, w});
        }
        int src;
        cout << "Enter Source node: " << endl;
        cin >> src;
        vector<int> ans;
        if (havingNegativeEdge)
            ans = Bellman_Ford(edges, V, src);
        else
            ans = Djisktra(adj, V, src);
        if (ans.size() == 0)
            cout << "Source is a isolated vertex or there may be Negative Cycle\n";
        else
        {
            cout << "The distances from source, " << src << " are : \n";
            for (int i = 0; i < V; i++)
                if (ans[i] == INF)
                    cout << "there is no path from " << src << " to " << i << "\n";
                else
                    cout << ans[i] << "\n";
        }
    }
    return 0;
}
// } Driver Code Ends