#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
/* find Topological sort order and do relax */

bool relax(vector<int>& dis, vector<int>& parent, int source, int neighbor) {
    // cout << "Neighbor " << neighbor << ", Source: " << source << endl;
    if(dis[neighbor-1] < dis[source-1] + 1) {
        dis[neighbor-1] = dis[source-1] + 1;
        parent[neighbor-1] = source;
        return true;
    }
    return false;
}

vector<int> topoRelax(vector<vector<int>>& adj, vector<int>& dis, vector<int>& topoOrder) {
    int n = adj.size();
    vector<bool> visited(n, false);
    vector<int> parent(n);

    for(int source: topoOrder) {
        for(int neighbor : adj[source-1]) {
            relax(dis, parent, source, neighbor);
        }
    }
    // cout << "Parent" << endl;
    // for(auto x: parent) {
    //     cout << x << " ";
    // }
    vector<int> longestPath;
    longestPath.push_back(n);
    int last_one = parent[n-1];
    while(last_one != 1) {
        longestPath.push_back(last_one);
        last_one = parent[last_one-1];
    }
    longestPath.push_back(1);
    reverse(longestPath.begin(), longestPath.end());
    
    return longestPath;
}

void dfs(vector<vector<int>>& adj, vector<int>& visited, vector<int>& topoOrder, int node) {
    visited[node-1] = 1;

    for(int v: adj[node-1]) {
        if(visited[v-1] == 0) {
            dfs(adj, visited, topoOrder, v);
        }
    }

    visited[node-1] = 2;
    topoOrder.push_back(node);
}
vector<int> topoSort(vector<vector<int>>& adj) { // return {} if can't reach destination
    int n = adj.size();
    vector<int> visited(n, 0);
    vector<int> topoOrder;
    dfs(adj, visited, topoOrder, 1);
    
    reverse(topoOrder.begin(), topoOrder.end());

    int dest_pos = 0;
    for(; dest_pos < topoOrder.size(); dest_pos++) {
        if(topoOrder[dest_pos] == n) {
            break;
        }
    }
    if(dest_pos == topoOrder.size()) {
        return {};
    }
    topoOrder = vector<int>(topoOrder.begin(), topoOrder.begin() + (dest_pos+1));
    
    return topoOrder;
}

int main() {
    int n, m;
    cin >> n >> m; // node, edge
    vector<vector<int>> adj(n);
    vector<int> dis(n, 0);
    
    for(int i = 0, a, b; i < m; i++) {
        cin >> a >> b; 
        adj[a-1].push_back(b);
    }

    vector<int> topoOrder = topoSort(adj); // return {} if can't reach destination
    if(topoOrder.size() == 0) { 
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }
    // cout << "TOPOloigcal" << endl;
    // for(auto x: topoOrder) {
    //     cout << x << " ";
    // }

    vector<int> longest = topoRelax(adj, dis, topoOrder);
    cout << (dis[n-1]+1) << endl;
    for(auto x: longest) {
        cout << x << " ";
    }
    return 0;
}