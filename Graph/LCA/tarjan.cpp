#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6+10;
vector<int> E[MAXN];
vector<int> Q[MAXN];
int vis[MAXN];
int anc[MAXN];

int ran[MAXN];
int par[MAXN];
void init_ds(int n)
{
    for(int i = 0; i < n; ++i) {
        par[i] = i;
        ran[i] = 0;
    }
}
int find_ds(int x)
{
    if(x == par[x]) return x;
    return par[x] = find_ds(par[x]);
}
bool same_ds(int x, int y)
{
    return find_ds(x) == find_ds(y);
}
void comb_ds(int x, int y)
{
    x = find_ds(x);
    y = find_ds(y);
    if(x == y) return;
    if(ran[x] < ran[y]) {
        par[x] = y;
    }else {
        par[y] = x;
        if(ran[x] == ran[y]) {
            ran[x]++;
        }
    }
}

void DFS(int v = 0, int fa = -1)
{
    anc[find_ds(v)] = v;
    for(auto u: E[v]) {
        if(u != fa) {
            DFS(u, v);
            comb_ds(u, v);
            anc[find_ds(v)] = v;
        }
    }
    vis[v] = 1;
    for(auto u: Q[v]) {
        if(vis[u] == 1) {
            cout << v+1 << " " << u+1 << ":\t" << anc[find_ds(u)]+1 << endl;
        }
    }
}

int main()
{
    int n, q;
    cin >> n >> q;
    init_ds(n);
    for(int i = 0; i < n-1; ++i) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        E[x].push_back(y);
        E[y].push_back(x);
    }
    for(int i = 0; i < q; ++i) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        Q[x].push_back(y);
        Q[y].push_back(x);
    }
    DFS();
}
