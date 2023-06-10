#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
const int BIGmode = 1000000007;

/* Topological Sort and DP */

void dfs(vector<vector<int>>& adj, vector<int>& visited, vector<int>& topoOrder, int source) {
    visited[source-1] = 1;

    for(int neighbor: adj[source-1]) {
        if(visited[neighbor-1] == 0) {
            dfs(adj, visited, topoOrder, neighbor);
        }
    }

    visited[source-1] = 2;
    topoOrder.push_back(source);
}

vector<int> topoSort(vector<vector<int>>& adj) {
    int n = adj.size();
    vector<int> topoOrder;
    vector<int> visited(n, 0);
    dfs(adj, visited, topoOrder, 1);
    std::reverse(topoOrder.begin(), topoOrder.end());

    return topoOrder;
}

int calculateWay(vector<vector<int>>& adj) {
    
    vector<int> topoOrder = topoSort(adj);
    int n = adj.size();
    vector<int> ways(n, 0);
    ways[0] = 1;

    for(int node: topoOrder) {
        if(node == n) {
            break;
        }
        for(int v: adj[node-1]) {
            ways[v-1] = (ways[node-1] + ways[v-1]) % BIGmode;
        }
    }
    return ways[n-1];
}

int main() {
    int n, m;
    cin >> n >> m; // node, edge
    vector<vector<int>> adj(n);
    
    for(int i = 0, a, b; i < m; i++) {
        cin >> a >> b; 
        adj[a-1].push_back(b);
    }
    int ans = calculateWay(adj);
    cout << ans << endl;

    return 0;
}