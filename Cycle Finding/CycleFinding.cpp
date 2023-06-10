#include <iostream>
#include <vector>
#include <stack>

#define loi long long int
using namespace std;

const loi inf = 1e15;

bool relax(vector<loi>& dis, int u, pair<int, loi>& v, vector<int>& parent) {
    int vNode = v.first;
    int vCost = v.second;
    if(dis[vNode-1] > dis[u-1] + vCost) {
        dis[vNode-1] = dis[u-1] + vCost;
        parent[vNode-1] = u;
        return true;
    }
    return false;
}
/* Bellman-Ford Algorithm */
void bell(vector<vector<pair<int, loi>>>& adj, vector<loi>& dis, vector<int>& parent) {
    int n = adj.size();
    
    for(int i = 0; i < n-1; i++) { // relax n - 1 times
        for(int j = 0; j < n; j++) {
            vector<pair<int, loi>> neighbors = adj[j];
            for(pair<int, loi>& v: neighbors) {
                relax(dis, j+1, v, parent);
            } 
        }
    }
}

void checkNegative(vector<vector<pair<int, loi>>>& adj, vector<loi>& dis, vector<int>& parent) {
    int n = adj.size();
    
    int negHead = 0;
    for(int j = 0; j < n; j++) { // nth relax
        vector<pair<int, loi>> neighbors = adj[j];
        for(pair<int, loi>& v: neighbors) {
            if(relax(dis, j+1, v, parent)) {
                cout << "YES" << endl;
                negHead = j+1;
                j = n;
                break;
            }
        } 
    }
    if(negHead == 0) {
        cout << "NO" << endl;
        return;
    }
    stack<int> cycleOrder; // will reverse for the format
    vector<bool> visited(n, false);
    /* negHead may not be in the negative cycle or there's a smaller negative cycle when we trace back */
    cycleOrder.push(negHead);
    visited[negHead-1] = true; 
    int last = parent[negHead-1];
    while(visited[last-1] != true) { // when true, it means there's a negative cycle start from "last"
        cycleOrder.push(last);
        visited[last-1] = true;
        last = parent[last-1];
    }
    
    cout << last << " ";
    while(cycleOrder.top() != last) {
        cout << cycleOrder.top() << " ";
        cycleOrder.pop();
    }
    cout << last << endl;
}

int main() {
    int n, m;
    cin >> n >> m; // node, edge
    vector<vector<pair<int, loi>>> adj(n);

    for(int i = 0, a, b, cost; i < m; i++) {
        cin >> a >> b >> cost; 
        adj[a-1].push_back(make_pair(b, cost));
    }
    vector<loi> dis(n, inf);
    vector<int> parent(n);
    for(int i = 0; i < n; i++) {
        parent[i] = i + 1;
    }
    dis[0] = 0;
    bell(adj, dis, parent);
    // for(int i = 0; i < n; i++) {
    //     cout << (i+1) << ", distance: " << dis[i] << endl;
    // }
    checkNegative(adj, dis, parent);

    return 0;
}