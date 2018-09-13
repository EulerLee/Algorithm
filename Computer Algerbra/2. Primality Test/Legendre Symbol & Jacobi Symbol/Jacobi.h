#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unordered_set>

namespace Jacobi {    
    using namespace std;
    typedef long long ll;
    #define REP(i, n) for(ll i = 0; i < n; ++i)
    #define RANGE(i, x, n) for(ll i = x; i < n; ++i)

    ll quick_pow(ll x, ll n, ll mod = 0xffffffff)
    {
        ll ans = 1;
        x %= mod;
        while(n) {
            if(n&1) {
                ans *= x;
                ans %= mod;
            }
            x *= x;
            x %= mod;
            n >>= 1;
        }
        return ans;
    }

    ll findt(ll a, ll &b)
    {
        ll l, h, m;
        l = 0;
        h = 51;
        m = (l + h)/2;
        while(h - l > 1) {
            b = quick_pow(2, m);
            if(a % b == 0) {
                l = m;
            }else {
                h = m;
            }
            m = (l+h)/2;
        }
        b = a / quick_pow(2, l);
        return l;
    }

    int Jacobi_symbol(ll a, ll m)
    {
        a %= m;
        if(a == 0) return 0;
        if(a == 1) return 1;
        if(a == -1 || a == m-1) return ((m-1)/2 % 2 == 0 ? 1 : -1);
        if(a == 2) return ((m*m-1)/8 % 2 == 0 ? 1 : -1);
        if(a % 2 == 0) {
            ll t, b;
            t = findt(a, b);
            if(t%2 == 0) {
                return Jacobi_symbol(b, m);
            }else {
                return Jacobi_symbol(2, m) * Jacobi_symbol(b, m);
            }
        }
        return ((m-1)*(a-1)/4%2 == 0 ? 1 : -1) * Jacobi_symbol(m%a, a);
    }
}
