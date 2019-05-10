#include <bits/stdc++.h>
#define DIRECTIONAL

#define REP(i, n) for(int i = 0; i < n; ++i)
#define RANGE(i, x, n) for(int i = x; i < n; ++i)
using namespace std;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;

const int MAXN = 1e5+10;
vector<int> adj[MAXN];
int n, m;
map<pair<int, int>, int> cntedge;
#ifdef DIRECTIONAL
int dout[MAXN];
int din[MAXN];
#endif

void input()
{
    cin >> n >> m;
    REP(i, m) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        adj[x].push_back(y);
#ifndef DIRECTIONAL
        adj[y].push_back(x);
        cntedge[make_pair(min(x, y), max(x, y))]++;
#else
        dout[x]++;
        din[y]++;
        cntedge[make_pair(x, y)]++;
#endif
        cout << x << " " << y << endl;
    }
}

int sta_sig[MAXN];
vector<int> path;

void DFS(int v)
{
    for(int i = sta_sig[v]; i < adj[v].size(); i = sta_sig[v]+1) {
        int u = adj[v][i];
#ifndef DIRECTIONAL
        if(cntedge[make_pair(min(u, v), max(u, v))] > 0) {
            cntedge[make_pair(min(u, v), max(u, v))]--;
            DFS(u);
        }
        else {
            sta_sig[v] = i;
        }
#else
        if(cntedge[make_pair(v, u)] > 0) {
            cntedge[make_pair(v, u)]--;
            DFS(u);
        }
        else {
            sta_sig[v] = i;
        }
#endif
    }
    path.push_back(v+1);
}

bool find_eulerpath()
{
    // check
    int sta, las;
    sta = las = -1;
#ifdef DIRECTIONAL
    REP(i, n) {
        cout << i+1 << ":\t" << din[i] << " " << dout[i] << endl;
        if(din[i] != dout[i]) {
            if(din[i] == dout[i]+1 && las == -1) {
                las = i;
            }else if(din[i] == dout[i]-1 && sta == -1) {
                sta = i;
            }else {
                return false;
            }
        }
    }
#else
    REP(i, n) {
        cout << adj[i].size() << endl;
        if((int)adj[i].size()%2 != 0) {
            if(sta == -1) {
                sta = i;
            }else if(las == -1) {
                las = i;
            }else {
                return false;
            }
        }
    }
#endif
    if(sta != -1 && las == -1) return false;
    if(sta == -1 && las != -1) return false;


    cout << sta << " " << las << endl;
    if(sta == -1) sta = 0;
    DFS(sta);

// print path
#ifdef DIRECTIONAL
    for(int i = (int)path.size()-1; i >= 0; --i) cout << path[i] << " "; cout << endl;
#else
    for(auto x: path) cout << x << " "; cout << endl;
#endif
    return true;
}

int main()
{
    input();
    if(!find_eulerpath()) cout << -1 << endl;
}
