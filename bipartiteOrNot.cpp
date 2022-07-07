#include <bits/stdc++.h>
using namespace std;

bool dfsUtil(int node, vector<int> adj[], vector<int> &visited)
{
    if (visited[node] == -1)
        visited[node] = 1;
    // cout<<node<<" "<<color<<endl;
    for (auto it : adj[node])
    {
        if (visited[it] == -1)
        {
            visited[it] = 1 - visited[node];
            if (!dfsUtil(it, adj, visited))
                return false;
        }
        else if (visited[it] == visited[node])
            return false;
    }
    return true;
}
bool isBipartiteByDFS(int V, vector<int> adj[])
{
    vector<int> visited(V, -1);
    for (int i = 0; i < V; i++)
    {
        if (visited[i] == -1 && !(dfsUtil(i, adj, visited)))
            return false;
    }
    return true;
}

bool isBipartiteByBFS(int V, vector<int> adj[])
{
    // '0' unvisited
    // '1' and '2' colours
    vector<char> visited(V, '0');

    for (int i = 0; i < V; i++)
    {
        if (visited[i] == '0')
        {

            queue<int> q;
            q.push(i);
            visited[i] = '1';
            while (!q.empty())
            {
                int node = q.front();
                q.pop();
                for (auto it : adj[node])
                {
                    if (visited[it] == '0')
                    {
                        if (visited[node] == '1')
                            visited[it] = '2';
                        else
                            visited[it] = '1';
                        q.push(it);
                    }
                    else if (visited[it] == visited[node])
                        return false;
                }
            }
        }
    }
    return true;
}

int main()
{
    int V, E;
    cout << "Enter number of vertices and edges: " << endl;
    cin >> V >> E;

    vector<int> adj[V];
    vector<vector<int>> edges(E, vector<int>(3));
    cout << "please enter as: vertex vertex :\n";
    for (int i = 0; i < E; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    bool isBipartite = isBipartiteByDFS(V, adj);
    if (isBipartite)
        cout << "This is Bipartite Graph" << endl;
    else
        cout << "This is not a Bipartite graph" << endl;

    return 0;
}
// } Driver Code Ends