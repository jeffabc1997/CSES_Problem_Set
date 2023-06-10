#include <iostream>
#include <vector>
#include <stack>

using namespace std;
/* DFS to get Topological Sort Order. */
/* Another way is to use in-degree. */

bool dfs(vector<vector<int>>& adj, stack<int>& order, vector<int>& visited, int root) {

    visited[root-1] = 1;
    for(int v: adj[root-1]) {
        if(visited[v-1] == 1) { // a cycle is detected, return false so we get "impossible"
            return false;
        }
        if((visited[v-1] == 0) && (!dfs(adj, order, visited, v))) {
                return false;
        }
    } 
    visited[root-1] = 2;
    order.push(root);
    return true;
}
int main() {

    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    
    for(int i = 0, a, b; i < m; i++){
        cin >> a >> b;
        adj[a-1].push_back(b);
    }
    stack<int> order;
    vector<int> visited(n, false);
    for(int i = 1; i <= n; i++) {
        if((visited[i-1] == 0) && (!dfs(adj, order, visited, i))) {
            cout << "IMPOSSIBLE" << endl;
            return 0;
        }
    }

    while(!order.empty()) { // reverse the order to get topological sort order
        cout << order.top() << " ";
        order.pop();
    }
    return 0;
}