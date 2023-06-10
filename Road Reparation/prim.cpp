#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct cmp { 
    bool operator()(pair<int, int> a, pair<int, int> b) {
        // the smallest one is on top
        return a.second > b.second;
    }
};

long long int prim(vector<vector<pair<int, int>>>& adj, vector<bool>& visited) {

    priority_queue<pair<int, int>, vector<pair<int, int>>, cmp> pq; 
    
    visited[0] = true;
    for(auto edge: adj[0]) {
        pq.push(edge);
    }

    pair<int, int> edge;
    int node;
    long long int cost, ttl_cost = 0;
    while(!pq.empty()) { // choose the smallest edge and the node that we didn't relax
        edge = pq.top();
        pq.pop();
        node = edge.first;
        cost = edge.second;
        // cout << "Node: " << node << endl;
        if(visited[node-1] == false) {
            visited[node-1] = true;
            ttl_cost += cost;
            for(auto new_edge: adj[node-1]) {
                if(visited[new_edge.first-1] == false) { // haven't been included yet, so we push no matter what the edge weight is
                    // cout << node << ", " << new_edge.first << "; Cost: " << new_edge.second << endl;
                    pq.push(new_edge);
                }
                
            }
        }
    }

    return ttl_cost;
}

int main() {

    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n);
    vector<bool> visited(n, false);
    for(int i = 0, a, b, cost; i < m; i++) {
        cin >> a >> b >> cost;
        adj[a-1].push_back(make_pair(b, cost));
        adj[b-1].push_back(make_pair(a, cost));
    }
    long long int ans = prim(adj, visited);
    for(int node: visited) {
        if(node == false) {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    }
    cout << ans << endl;
    return 0;
}