#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct cmp { 
    bool operator()(pair<int, long long int> a, pair<int, long long int> b) {
        // the smallest one is on top
        return a.second > b.second;
    }
};

vector<long long int> dijkstra(vector<vector<pair<int, int>>>& adj) {
    int n = adj.size();

    priority_queue<pair<int, long long int>, vector<pair<int, long long int>>, cmp> nodes;
    vector<long long int> dis(n, 200000000000001);
    vector<bool> visited(n, false);
    
    dis[0] = 0;
    nodes.push(make_pair(1, 0)); // { node name, distance }
    pair<int, long long int> nearNode;
    int u, count = n;

    while(count > 0) {
        nearNode = nodes.top();       
        nodes.pop();
        u = nearNode.first;
        // cout << count << endl;
        /* essential to wrap all operations in this if statement */
        if(visited[u-1] == false) {  // check if u is already an output
            visited[u-1] = true; 
            count--; // to count how many vertices we output

            long long int weight;
            for(int i = 0, v; i < adj[u-1].size(); i++) {
                v = adj[u-1][i].first;
                weight = adj[u-1][i].second;
                /* Relax */
                if((visited[v-1] == false) && (dis[v-1] > dis[u-1] + weight)) {
                    dis[v-1] = dis[u-1] + weight;
                    // cout << u << " " << v << ", cost: " << weight << endl;
                    nodes.push({v, dis[v-1]});
                
                }
            }
        }       
    }
    return dis;
}

int main() {

    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n);
    vector<bool> visited(n, false);
    for(int i = 0, a, b, cost; i < m; i++) {
        cin >> a >> b >> cost;
        adj[a-1].push_back(make_pair(b, cost));
    }

    vector<long long int> ans;
    ans = dijkstra(adj);
    for(long long int a: ans) {
        cout << a << " ";
    }
    return 0;
}