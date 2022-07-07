#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
	// TC -> O[N+E]
	// Sc => O[N]+O[N]
	vector<int> shortestPathUnweightedUndirectedGraph(vector<int> adj[], int V, int src)
	{
		vector<int> shortestDist(V, INT_MAX);
		queue<int> q;
		shortestDist[src] = 0;
		q.push(src);

		while (!q.empty())
		{
			int node = q.front();
			q.pop();
			for (auto it : adj[node])
			{
				if (shortestDist[it] > shortestDist[node] + 1)
				{
					shortestDist[it] = shortestDist[node] + 1;
					q.push(it);
				}
			}
		}
		return shortestDist;
	}
};
// { Driver Code Starts.
int main()
{
	int tc;
	cin >> tc;
	while (tc--)
	{
		int V, E;
		cout << "Enter number of vertices and edges: " << endl;
		cin >> V >> E;

		vector<int> adj[V];

		for (int i = 0; i < E; i++)
		{
			int u, v;
			cin >> u >> v;
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		int src;
		cout << "Enter Source node: " << endl;
		cin >> src;
		Solution obj;
		vector<int> ans = obj.shortestPathUnweightedUndirectedGraph(adj, V, src);
		for (int x : ans)
			cout << x << " ";
		cout << endl;
	}
	return 0;
} // } Driver Code Ends