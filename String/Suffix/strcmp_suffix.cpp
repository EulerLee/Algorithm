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
    for(int i = 0; i <= n; ++i) {
        SA[i] = i;
        ran[i] = i<n? s[i] : -1;
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

bool contain_SA(const string &S, const string &P, vector<int> &SA)
{
    int l = 0, r = S.size();
    int m = (l+r)>>1;
    while(r-l > 1) {
        if(S.compare(SA[m], P.size(), P) < 0) {
            //S[SA[m], P.size()] < P
            l = m;
        }else {
            r = m;
        }
        m = (l+r)>>1;
    }
    return S.compare(SA[r], P.size(), P) == 0;
}

int find_SA(const string &S, const string &P, vector<int> &SA)
{
    int l = 0, r = S.size();
    int m = (l+r)>>1;
    while(r-l > 1) {
        if(S.compare(SA[m], P.size(), P) < 0) {
            //S[SA[m], P.size()] < P
            l = m;
        }else {
            r = m;
        }
        m = (l+r)>>1;
    }
    if(S.compare(SA[r], P.size(), P) == 0) return SA[r];
    else return -1;
}

int main()
{
    string s, p;
    cin >> s >> p;
    n = s.size();
    vector<int> SA(n+1);
    construct_SA(s, SA);
    cout << boolalpha << contain_SA(s, p, SA) << endl;
    cout << find_SA(s, p, SA) << endl;
}
