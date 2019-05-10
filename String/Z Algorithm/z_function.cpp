#include <bits/stdc++.h>
#define REP(i, n) for(int i = 0; i < n; ++i)
#define RANGE(i, x, n) for(int i = x; i < n; ++i)
using namespace std;
typedef long long ll;
typedef long double ld;

const int MAXN = 1e6+10;
int ZFun[MAXN];

void compute_ZFun(const string &s)
{
    int n = s.size();
    ZFun[0] = n;
    int L, R;
    L = R = 0;
    RANGE(i, 1, n) {
        if(i > R) {
            if(s[i] != s[0]) continue;
            ZFun[i] = 1;
            for(; i+ZFun[i] < n; ++ZFun[i]) {
                if(s[i+ZFun[i]] != s[ZFun[i]]) break;
            }
            L = i;
            R = i+ZFun[i]-1;
        }else {
            int k = i-L;
            if(ZFun[k] < R-i+1) {
                ZFun[i] = ZFun[k];
                continue;
            }else {
                ZFun[i] = R-i+1;
                for(; i+ZFun[i] < n; ++ZFun[i]) {
                    if(s[i+ZFun[i]] != s[ZFun[i]]) break;
                }
                L = i;
                R = i+ZFun[i]-1;
            }
        }
    }
}

int main()
{
    string s;
    cin >> s;
    compute_ZFun(s);
    RANGE(i, 1, s.size()) {
        cout << i << ":\t";
        REP(j, ZFun[i]) {
            cout << s[i+j];
        }
        cout << endl;
    }
}
