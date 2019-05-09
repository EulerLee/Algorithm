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

inline ll func(ll x, ll mod)
{
    return (x*x+1)%mod;
}

ll rho(ll N, ll f(ll, ll), ll x0)   // use Floyd, can be improved by using Brent-Algorithm
{
    ll xi = x0;
    ll x2i = f(x0, N);
    ll Q = 1;
    RANGE(i, 1, 20000) {
        Q *= (x2i-xi);
        Q %= N;
        Q = (Q+N)%N;
        cout << i << ":\t" << xi << " " << x2i << " " << Q << endl;
        ll res = gcd(Q, N);
        if(res != N && res != 1) return res;
        xi = f(xi, N);
        x2i = f(f(x2i, N), N);
    }
    return 0;
}

int main()
{
    int N = 8051;
    ll x0 = 1;
    //cin >> N >> x0;
    cout << rho(N, func, x0) << endl;
}
