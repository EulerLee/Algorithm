#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll quick_pow(ll x, ll n, ll mod)
{
    ll ans = 1;
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

ll compute_primitive_root(ll p)
{
    if(p == 1) return 1;
    vector<ll> pd;
    ll phi = p-1;
    for(ll i = 2; i*i <= phi; ++i) {
        if(phi%i == 0) {
            pd.push_back(i);
            while(phi%i == 0) {
                phi /= i;
            }
        }
    }
    if(phi != 1) pd.push_back(phi);

    //for(auto q: pd) cout << q << " "; cout << endl;

    phi = p-1;
    for(ll i = 2; i < p; ++i) {
        int flg = 1;
        for(auto q: pd) {
            if(quick_pow(i, phi/q, p) == 1) {
                flg = 0;
                break;
            }
        }
        if(flg == 1) return i;
    }
    return -1;
}


int main()
{
    ll p = 998244353ll;
    ll g = compute_primitive_root(p);
    cout << g << endl;
    unordered_set<ll> S;
    ll x = g;
    for(ll i = 0; i < p-1; ++i) {
        if(S.find(x) == S.end()) {
            S.insert(x);
        }else {
            cout << "WRONG!" << endl;
            cout << x << endl;
            return 0;
        }
        x *= g;
        x %= p;
    }
    cout << "OK" << endl;
}
