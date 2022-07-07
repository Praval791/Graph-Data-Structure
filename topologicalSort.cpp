#include <bits/stdc++.h>
using namespace std;

#include <bits/stdc++.h>
using namespace std;

void dfs(int node, vector<int> adj[], vector<bool> &visited, vector<int> &stk)
{
    visited[node] = true;
    for (auto it : adj[node])
        if (!visited[it])
            dfs(it, adj, visited, stk);
    stk.push_back(node);
}
vector<int> topoSortByDFS(int V, vector<int> adj[])
{
    // code here
    vector<bool> visited(V, false);
    vector<int> stk;
    for (int i = 0; i < V; i++)
    {
        if (!visited[i])
            dfs(i, adj, visited, stk);
    }

    reverse(stk.begin(), stk.end());
    return stk;
}

vector<int> KAHNsAlgo(int V, vector<int> adj[])
{
    // code here
    vector<int> inDegree(V, 0);
    // find InDegree
    for (int i = 0; i < V; i++)
        for (auto it : adj[i])
            inDegree[it]++;

    queue<int> q;
    // start of topo sort
    for (int i = 0; i < V; i++)
        if (inDegree[i] == 0)
            q.push(i);

    vector<int> ans;
    // simple bfs
    while (!q.empty())
    {
        int node = q.front();
        ans.push_back(node);
        q.pop();
        for (auto it : adj[node])
        {
            inDegree[it]--;
            if (inDegree[it] == 0)
                q.push(it);
        }
    }
    return ans;
}

int main()
{
    int V, E;
    cout << "Enter number of vertices and edges: " << endl;
    cin >> V >> E;
    vector<int> adj[V];
    cout << "please enter as: u -> v :\n";
    for (int i = 0; i < E; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }
    vector<int> ans = topoSortByDFS(V, adj);
    if (ans.size() != V)
        cout << "NIL";
    else
    {
        cout << "Topological Sort :-\n";
        for (int a : ans)
            cout << " " << a;
    }
    cout << endl;
    return 0;
}