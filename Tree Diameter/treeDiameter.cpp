#include <iostream>
#include <vector>
#include <queue>

using namespace std;

/* BFS twice can get the result. 
1st BFS: get the farthest node(leaf of BFS tree)
2nd BFS: get the farthest node(another leaf in the 1st's BFS tree)
Another way is to BFS once with DP. */
vector<int> bfs(vector<vector<int>>& adj, int root) {
    int n = adj.size();
    vector<bool> visited(n, false);
    vector<int> dis(n, 200001);
    queue<int> willVisit;
    visited[root-1] = true;
    dis[root-1] = 0;
    willVisit.push(root);
    
    while(!willVisit.empty()) {
        
        root = willVisit.front(); 
        // cout << root << " ";
        willVisit.pop();
        for(int v: adj[root-1]) {
            if(visited[v-1] == false) {
                willVisit.push(v);
                visited[v-1] = true;
            }
            if(dis[v-1] > dis[root-1] + 1) {
                dis[v-1] = dis[root-1] + 1;
            }
        }
    }
    int far_node = 1, far_dis = 0;
    for(int i = 0;i < n; i++) {
        if(dis[i] > far_dis) {
            far_dis = dis[i];
            far_node = i + 1;
        }
    }
    return {far_node, far_dis};
}

int main() {

    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for(int i = 0, a, b; i < n-1; i++){
        cin >> a >> b;
        adj[a-1].push_back(b);
        adj[b-1].push_back(a);
    }
    vector<int> info; // farthest node and farthest distance
    info = bfs(adj, 1); 
    // cout << endl << info[0] << ", " << info[1];
    info = bfs(adj, info[0]);
    // cout << endl << info[0] << ", " << info[1];
    cout << info[1];
    return 0;
}