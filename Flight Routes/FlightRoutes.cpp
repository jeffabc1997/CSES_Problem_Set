#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const long long int inf = 3e15;
struct cmp { 
    bool operator()(pair<int, long long int> a, pair<int, long long int> b) {
        // the smallest one is on top
        return a.second > b.second;
    }
};
vector<long long int> relax(vector<vector<pair<int, int>>>& adj, int k) {
    int n = adj.size();
    /* contain the vertex we're going to relax and keep the smallest distance on top */
    /* 可以證明{ u, dis[u] }出現在priority_queue裡面的組合一定是到u點的距離前K小的 */
    priority_queue<pair<int, long long int>, vector<pair<int, long long int>>, cmp> will_visit;
    vector<int> relaxTime(n, 0); // record how many times a node starts its relax process 
    
    priority_queue<long long int> Kdist; // save k smallest path to destination
    for(int i = 0; i < k; i++) {
        Kdist.push(inf); // initialize to INF
    }
    will_visit.push({1, 0}); // source node and distance 0

    int node, neighbor;
    long long int cost, moreCost;
    while(!will_visit.empty()) {
        node = will_visit.top().first;
        cost = will_visit.top().second;
        will_visit.pop();
        if(relaxTime[node-1] >= k) {
            continue;
        } else {
            relaxTime[node-1]++;
        }

        for(int i = 0; i < adj[node-1].size(); i++) {
            
            neighbor = adj[node-1][i].first;
            moreCost = adj[node-1][i].second;
            will_visit.push({neighbor, cost + moreCost});            
            if(neighbor == n){

                Kdist.push(cost + moreCost);
                if(Kdist.size() > k) {
                    Kdist.pop();
                }
            }
        }
    }
    vector<long long int> ans(k, 0); // return vector
    for(int i = k - 1; i >= 0; i--) { 
        ans[i] = Kdist.top();
        Kdist.pop();
    }
    return ans;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<pair<int, int>>> adj(n);

    for(int i = 0, a, b, cost; i < m; i++) {
        cin >> a >> b >> cost;
        adj[a-1].push_back(make_pair(b, cost));
    }

    vector<long long int> ans = relax(adj, k);
    for(auto x: ans) {
        cout << x << " ";
    }
    return 0;     
}
