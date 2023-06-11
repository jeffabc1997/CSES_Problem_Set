#include <iostream>
#include <vector>

using namespace std;

int dfs(vector<vector<int>>& adj, vector<int>& visited, vector<int>&team, int root, int flag) {
    visited[root-1] = 1;
    team[root-1] = flag % 2 + 1;
    for(int child: adj[root-1]) {
        // visit an neighbor in same team -> impossible
        if((visited[child-1] == 1) && (team[child-1] == team[root-1])) {
            return -1;
        } else if(visited[child-1] == 0) {
            if(dfs(adj, visited, team, child, flag+1) == -1) {
                return -1;
            }
        }
    }
    visited[root-1] = 2;
    return 0;
}
int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n);
    vector<int> visited(n, 0);
    vector<int> team(n, 0);

    for(int i = 0, a, b; i < m; i++) {
        cin >> a >> b;
        adj[a-1].push_back(b);
        adj[b-1].push_back(a);
    }
    int status = 0;
    for(int i = 0; i < n; i++) {
        if(visited[i] == 0) {
            status = dfs(adj, visited, team, i+1, 1);
            if(status == -1) {
                cout << "IMPOSSIBLE" << endl;
                return 0;
            }
        }
    }

    for(int x: team) {
        cout << x << " ";
    }
    return 0;
}