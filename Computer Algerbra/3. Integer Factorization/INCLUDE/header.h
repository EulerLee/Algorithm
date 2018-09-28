#include <bits/stdc++.h>

namespace HEAD {
    typedef long long ll;
    typedef long double ld;
    #define REP(i, n) for(ll i = 0; i < n; ++i)
    #define RANGE(i, x, n) for(ll i = x; i < n; ++i)

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

    inline ll gcd(ll a, ll b)
    {
        if(b == 0) return a;
        return gcd(b, a%b);
    }

    inline ll lcm(ll a, ll b)
    {
        return a*b/gcd(a, b);
    }
}
