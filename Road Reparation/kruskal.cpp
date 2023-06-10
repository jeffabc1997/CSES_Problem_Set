#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;


bool comp(vector<int> a, vector<int> b) {
    // non-decreasing order
    if((a.size() == b.size()) && (a.size() == 3)) {
        return a[2] < b[2];
    }
    else {
        cout << "No Valid Edge" << endl;
        return a.size() < b.size();
    }
}

int findSet(vector<vector<int>>& disjoint, int child) {
    if(disjoint[1][child-1] == child) {
        return child;
    }

    disjoint[1][child-1] = findSet(disjoint, disjoint[1][child-1]);
    return disjoint[1][child-1];
}

bool unionSet(vector<vector<int>>& disjoint, int a, int b) {
    a = findSet(disjoint, a);
    b = findSet(disjoint, b);
    if(a == b) { // in same group
        return false;
    }
    if(disjoint[0][a-1] >= disjoint[0][b-1]) {
        disjoint[0][a-1] += disjoint[0][b-1]; // rank summation
        disjoint[1][b-1] = a; // change parent to "a"
    } else {
        disjoint[0][b-1] += disjoint[0][a-1]; // rank summation
        disjoint[1][a-1] = b; // change parent to "b"
    }
    return true;
}

long long int kruskal(vector<vector<int>>& edges, vector<vector<int>>& disjoint) {
    vector<int> edge;
    int a, b, n = disjoint[0].size() - 1;
    int m = n;
    long long int cost, ttl_cost = 0;
    for(int i = 0; i < edges.size(); i++) {
        edge = edges[i];
        a = edge[0];
        b = edge[1];
        cost = edge[2];
        if(unionSet(disjoint, a, b)) {
            ttl_cost += cost;
            m--;
            if(m == 0) {
                break;
            }
            // cout << a << ", " << b << ", "<< cost << endl;
        }
    }
    // cout << "M: " << m << endl;
    if(m != 0) {
        // cout << "N: " << n << endl;
        return -1;
    }
    return ttl_cost;
}
/* Slower than Prim's algo in CSES */
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> edges(m);
    vector<bool> visited(n, false);
    for(int i = 0, a, b, cost; i < m; i++) {
        cin >> a >> b >> cost;
        edges[i] = {a, b, cost};
    }
    sort(edges.begin(), edges.end(), comp);
    vector<vector<int>> disjoint(2, vector<int>(n, 1)); // rank, parent
    for(int i = 0; i < n; i++) {
        disjoint[1][i] = i + 1; // initialize parent to themselves
    }
    long long int ans = kruskal(edges, disjoint);
    if(ans < 0) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }
    cout << ans << endl;
    return 0;
}