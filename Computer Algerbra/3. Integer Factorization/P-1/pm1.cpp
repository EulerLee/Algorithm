#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
#define REP(i, n) for(ll i = 0; i < n; ++i)
#define RANGE(i, x, n) for(ll i = x; i < n; ++i)
using namespace std;

ll quick_pow(ll x, ll n, ll mod = 0x3f3f3f3f) {
    ll ans = 1;
    x %= mod;
    while(n) {
        if((n&1)) {
            ans *= x;
            ans %= mod;
        }
        x *= x;
        x %= mod;
        n >>= 1;
    }
    return ans;
}

ll gcd(ll a, ll b)
{
    if(b == 0) return a;
    return gcd(b, a%b);
}

inline ll lcm(ll a, ll b)
{
    return a*b/gcd(a, b);
}

vector<int> FB{2};

int pm1(int N, int a, int B)
{
    vector<int> vis(840, 0);
    RANGE(i, 3, B+1) {
        if(vis[i] == 0) {
            FB.push_back(i);
            for(int k = 1; k*i <= B; ++k) {
                vis[k*i] = 1;
            }
        }
    }
    int cnt = 0;
    ll C = 1;
    RANGE(i, 1, 20000) {
        REP(j, FB.size()) {
            if(i%(j+1) == 0) {
                ++cnt;
                C *= 1ll*quick_pow(a, FB[j], N);
                C %= N;
                cout << cnt+1 << ":\t" << C << endl;
            }
            if(cnt%20 == 0) {
                int res = gcd(C-1, N);
                if(res > 1) {
                    return res;
                }
            }
        }
    }
    return 0;
}

int main()
{
    int N, a, B;
    //cin >> N >> a >> b;
    N = 53467;
    a = 3;
    B = 840;

    cout << pm1(N, a, B) << endl;
}
