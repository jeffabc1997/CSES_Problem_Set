#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

/* bfs */
void bfs(vector<vector<int>>& adj, vector<int>& dis, vector<bool>& visited) {
    queue<int> nextVisit;
    dis[0] = 0; // initialize, start from vertex 1
    nextVisit.push(1);
    int node; // the node that we're checking its adjacent nodes
    while(!nextVisit.empty()) {
        node = nextVisit.front();
        // cout << node << " ";
        nextVisit.pop();
        for(int neighbor: adj[node-1]) { // check every adjacent node that's not visited
            if(!visited[neighbor-1]) {
                nextVisit.push(neighbor);
                visited[neighbor-1] = true; // very important step
            }
            if(dis[neighbor-1] > dis[node-1] + 1) { // Relax
                dis[neighbor-1] = dis[node-1] + 1;
            }
        }
    }
}

stack<int> trace(vector<vector<int>>& adj, vector<int>& dis){
    int n = adj.size();
    stack<int> path;
    path.push(n);
    /* Start from the last node */
    for(int i = dis[n-1]-1, node = n; i >= 0; i--) {  
        for(int j = 0, neighbor; j < adj[node-1].size(); j++) {
            neighbor = adj[node-1][j]; // node's neighbor
            if(dis[neighbor-1] == i) { // the nearest one from the starting point
                node = neighbor;              
                break;
            }
        }
        path.push(node);
    }
    return path;
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<int> dis(n, 200000);
    vector<bool> visited(n, false);


    for(int i = 0, a, b; i < m; i++) {
        cin >> a >> b;
        adj[a-1].push_back(b); // minus 1 because the nodes are 1, ..., n
        adj[b-1].push_back(a);
    }

    bfs(adj, dis, visited);
    if(dis[n-1] == 200000) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }
    // for(auto x: dis) {
    //     cout << x << " ";
    // }
    cout << (dis[n-1]+1) << endl; // add 1 because the answer should be how many computers we need
    stack<int> ans = trace(adj, dis);
    while(!ans.empty()) {
        cout << ans.top() << " ";
        ans.pop();
    }
    return 0;
}