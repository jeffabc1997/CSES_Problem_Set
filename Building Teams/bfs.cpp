#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/* BFS approach */
bool bfs(vector<vector<int>>& adj, vector<int>& team, vector<bool>& visited, int source) {

    queue<int> will_visit;

    will_visit.push(source);
    team[source-1] = 1;
    visited[source-1] = true;
    int node;
    while(!will_visit.empty()) {
        node = will_visit.front();
        
        will_visit.pop();
        for(int v: adj[node-1]) {
            if(team[v-1] == team[node-1]) { // same team -> wrong
                return false;
            }
            if(visited[v-1] == false) { // push unvisited node
                will_visit.push(v);
                visited[v-1] = true; // set true, so will not be pushed into queue again
            }
            team[v-1] = team[node-1] % 2 + 1; // set team
        }
    }

    return true;
}
int main() {
    
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);
    vector<int> team(n, 0);
    vector<bool> visited(n, false);
    for(int i = 0, a, b; i < m; i++) {
        cin >> a >> b;
        adj[a-1].push_back(b);
        adj[b-1].push_back(a);
    }
    bool status = true;
    /* BFS each connected component to assign team */
    for(int i = 0; i < n; i++) {
        if(visited[i] == false) {
            status = bfs(adj, team , visited, i+1);
        }
        if(status == false) {
            cout << "IMPOSSIBLE" << endl;
            break;
        }
    }
    if(status) {
        for(int x: team) {
            cout << x << " ";
        }
    }
    return 0;
}