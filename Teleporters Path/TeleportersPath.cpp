#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/* Hierholzer's algorithm */
/* Find Euler Path in Directed Graph */
bool euler_exist(vector<vector<int>>& adj, vector<int>& inDeg, vector<int>& outDeg) {
    
    int n = inDeg.size();
    /* source and destination must have odd degrees */
    if(!(((inDeg[0] + outDeg[0]) % 2 == 1) && (outDeg[0] > inDeg[0]))) {
        return false;
    } 
    if(!(((inDeg[0] + outDeg[0]) % 2 == 1) && (outDeg[n-1] < inDeg[n-1]))) {
        return false;
    }
    /* other node must have even degrees */
    for(int i = 1; i < n - 1; i++) {
        if((inDeg[i] + outDeg[i]) % 2 == 1) {
            return false;
        }
    }
    return true;
}

void dfs_hierholzer(vector<vector<int>>& adj, vector<int>& ans, vector<int>& adjPos, int source, int& edge_count) {
    
    int i = adjPos[source-1], dest;
    while(i < adj[source-1].size()) { // out of range means all outward edges are visited

        dest = adj[source-1][i];

        adjPos[source-1] += 1; 
        edge_count -= 1; // check how many edge that we didn't visit

        dfs_hierholzer(adj, ans, adjPos, dest, edge_count); // recursive
        
        i = adjPos[source-1]; // to track where to start in adjacency list
    }

    ans.push_back(source); // out-degree = 0 means finished, then be an output
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    vector<int> outDeg(n, 0);
    vector<int> inDeg(n, 0);
    vector<int> ans;
    vector<int> adjPos(n, 0);
    for(int i = 0, source, dest; i < m; i++) {
        cin >> source >> dest;
        adj[source-1].push_back(dest);
        outDeg[source-1] += 1;
        inDeg[dest-1] += 1;
    }
    if(!euler_exist(adj, inDeg, outDeg)) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }
    dfs_hierholzer(adj, ans, adjPos, 1, m);
    if(m > 0) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }
    std::reverse(ans.begin(), ans.end());
    for(int x: ans) {
        cout << x << " ";
    }
    return 0;
}