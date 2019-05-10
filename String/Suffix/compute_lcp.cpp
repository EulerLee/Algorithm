#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < n; ++i)
#define RANGE(i, x, n) for(int i = x; i < n; ++i)
using namespace std;
typedef long long ll;
typedef long double ld;

const int MAXN = 1e6;
int n, k;
int ran[MAXN+1];
int tmp[MAXN+1];

// cmp <ran[i], ran[i+k]> with <ran[j], ran[j+k]>
// return S[i, 2k] < S[j, 2k]
bool compare_SA(int i, int j)
{
    if(ran[i] != ran[j]) return ran[i] < ran[j];
    else {
        // cannot both be -1
        int ri = i+k <= n? ran[i+k] : -1;
        int rj = j+k <= n? ran[j+k] : -1;
        return ri < rj;
    }
}

void construct_SA(const string &s, vector<int> &SA)
{
    n = s.size();
    SA.resize(n+1);
    for(int i = 0; i <= n; ++i) {
        SA[i] = i;
        ran[i] = i<n? (int)s[i] : -1;
    }

    for(k = 1; k <= n; k*=2) {
        sort(SA.begin(), SA.end(), compare_SA); // almost right

        tmp[SA[0]] = 0;
        for(int i = 1; i <= n; ++i) {
            // judge if equal
            tmp[SA[i]] = tmp[SA[i-1]] + (compare_SA(SA[i-1], SA[i])? 1 : 0);
        }
        for(int i = 0; i <= n; ++i) {
            ran[i] = tmp[i];
        }
    }
}

void construct_LCP(const string &s, vector<int> &SA, vector<int> &LCP)
{
    n = s.size();
    LCP.assign(n, 0);

    REP(i, n+1) {
        ran[SA[i]] = i;
    }

    LCP[SA[0]] = 0;
    int h = 0;

    // h[i] >= h[i-1] - 1
    REP(i, n) {
        int j = SA[ran[i]-1];
        if(h>0) --h;
        for(; i+h<=n && j+h<=n; ++h) {
            if(s[i+h] != s[j+h]) break;
        }
        LCP[ran[i]-1] = h;
    }
}

int main()
{
    string s;
    cin >> s;
    n = s.size();
    vector<int> SA;
    construct_SA(s, SA);
    vector<int> LCP;
    construct_LCP(s, SA, LCP);

    REP(i, n) {
        cout << s.substr(SA[i]) << endl << s.substr(SA[i+1]) << endl;
        cout << LCP[i] << endl;
    }
}
