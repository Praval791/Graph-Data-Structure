#include <bits/stdc++.h>
using namespace std;

class CycleInDirected
{
    bool checkCycle(int node, vector<int> adj[], vector<bool> &visited, vector<bool> &dfsVisit)
    {
        visited[node] = true;
        dfsVisit[node] = true;
        for (auto it : adj[node])
            if ((!visited[it] and checkCycle(it, adj, visited, dfsVisit)) or dfsVisit[it])
                return true;
        dfsVisit[node] = false;
        return false;
    }

public:
    // Function to detect cycle in a directed graph.
    bool isCycleByDFS(int V, vector<int> adj[])
    {
        // code here
        vector<bool> visited(V, false), dfsVisit(V, false);

        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
                if (checkCycle(i, adj, visited, dfsVisit))
                    return true;
        }
        return false;
    }
    // Kahn's algorithm
    bool isCycleByBFS(int V, vector<int> adj[])
    {
        // code here
        vector<int> inDegree(V, 0);
        for (int i = 0; i < V; i++)
            for (auto it : adj[i])
                inDegree[it]++;

        queue<int> q;
        for (int i = 0; i < V; i++)
            if (inDegree[i] == 0)
                q.push(i);

        int count = 0;
        while (!q.empty())
        {
            int node = q.front();
            count++;
            q.pop();
            for (auto it : adj[node])
            {
                inDegree[it]--;
                if (inDegree[it] == 0)
                    q.push(it);
            }
        }
        return !(count == V);
    }
};

class CycleInUndirected
{
    vector<bool> visited;
    bool DFSUtil(int node, int parent, vector<int> adj[])
    {
        visited[node] = true;
        for (auto it : adj[node])
        {
            if (!visited[it] && DFSUtil(it, node, adj))
                return true;
            else if (it != parent)
                return true;
        }

        return false;
    }

public:
    bool isCycleByDFS(int V, vector<int> adj[])
    {
        vector<bool> visited(V, false);
        this->visited = visited;
        for (int i = 0; i < V; i++)
        {
            if (!visited[i] && DFSUtil(i, -1, adj))
                return true;
        }
        return false;
    }

    bool isCycleByBFS(int V, vector<int> adj[])
    {
        // Code here
        vector<bool> visited(V, false);
        for (int i = 0; i < V; i++)
        {
            if (!visited[i])
            {
                queue<pair<int, int>> que;
                que.push({i, -1});
                visited[i] = true;
                while (!que.empty())
                {
                    int node = que.front().first;
                    int prevNode = que.front().second;
                    que.pop();
                    for (auto it : adj[node])
                        if (!visited[it])
                        {
                            que.push({it, node});
                            visited[it] = true;
                        }
                        else

                            if (it != prevNode)
                            return true;
                }
            }
        }
        return false;
    }
};

int main()
{
    bool directed;
    cout << "Directed, then press 1:\nUndirected, then press 0:\n";
    cin >> directed;
    int V, E;
    cout << "Enter number of vertices and edges: " << endl;
    cin >> V >> E;

    if (directed)
    {
        vector<int> adj[V];
        cout << "please enter u -> v :\n";
        for (int i = 0; i < E; i++)
        {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
        }
        CycleInDirected obj;
        bool isCycle = obj.isCycleByDFS(V, adj);
        if (isCycle)
            cout << "There is a cycle" << endl;
        else
            cout << "There is no cycle" << endl;
    }
    else
    {

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
        CycleInUndirected obj;
        bool isCycle = obj.isCycleByBFS(V, adj);
        if (isCycle)
            cout << "There is a cycle" << endl;
        else
            cout << "There is no cycle" << endl;
    }
    return 0;
}
// } Driver Code Ends