#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#define PII pair<int, int>
#define STA(a, b) min(a, b), max(a, b)
using namespace std;

const int MAXN = 1e5+10;
vector<int> G[MAXN];
int n, m;
int vis[MAXN];
int cut[MAXN];
vector<PII> bridge;
int dep[MAXN];
int ancestor_depth[MAXN];

void DFS(int v = 0, int par = -1, int depth = 0)
{
    if(vis[v] != 0) return;
    vis[v] = 1;
    dep[v] = depth;
    ancestor_depth[v] = depth;
    int tot = 0;
    for(auto u: G[v]) {
        if(u != par) {
            if(vis[u] == 0) {
                ++tot;
                DFS(u, v, depth+1);
                ancestor_depth[v] = min(ancestor_depth[v], ancestor_depth[u]);
                if(ancestor_depth[u] > depth) bridge.emplace_back(STA(u, v));
                if(v == 0 && tot > 1) cut[v] = 1;
                if(v != 0 && (ancestor_depth[v] >= depth)) cut[v] = 1;
            }else if(vis[u] == 1) {
                ancestor_depth[v] = min(ancestor_depth[v], dep[u]);
            }
        }
    }
    vis[v] = 2;
    if(v == 0 && tot > 1) cut[v] = 1;
    
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m;
    for(int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    DFS();
    for(int i = 0; i < n; ++i) {
        if(cut[i]) cout << i+1 << endl;
    }
}
