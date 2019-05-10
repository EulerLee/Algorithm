#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < n; ++i)
#define RANGE(i, x, n) for(int i = x; i < n; ++i)
using namespace std;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

const int MAXN = 1e5;
int n;
vector<int> E[MAXN];
vector<int> rE[MAXN];
vector<int> vs;
int vis[MAXN];
int scc[MAXN];  // 顶点所属的强联通分量标号

void DFS1(int v)
{
    if(vis[v]) return;
    vis[v] = 1;
    for(auto u: E[v]) {
        if(!vis[u]) DFS1(u);
    }
    vs.push_back(v);
}

void DFS2(int v, int k)
{
    if(vis[v]) return;
    vis[v] = 1;
    scc[v] = k;
    for(auto u: rE[v]) {
        if(!vis[u]) DFS2(u, k);
    }
}

int find_scc()
{
    memset(vis, 0, sizeof vis);
    REP(i, n) {
        if(!vis[i]) DFS1(i);
    }
    //for(auto x: vs) cout << x+1 << " "; cout << endl;
    memset(vis, 0, sizeof vis);
    int k = 0;
    for(int i = n-1; i >= 0; --i) {
        if(!vis[vs[i]]) DFS2(vs[i], k++);
    }
    return k;
}

// for print
bool compare_scc(int i, int j)
{
    return scc[i] < scc[j];
}

int main()
{
    cin >> n;
    int m;
    cin >> m;
    REP(i, m) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        E[x].push_back(y);
        rE[y].push_back(x);
    }
    cout << find_scc() << endl;
    sort(vs.begin(), vs.end(), compare_scc);
    int k = 0;
    cout << "0:\t";
    for(auto x: vs) {
        if(scc[x] > k) {
            ++k;
            cout << endl << k << ":\t" << x+1 << " ";
        }else {
            cout << x+1 << " ";
        }
    }
    cout << endl;
}
