/*
mod为素数且大于n，并且fact[n]可以打表时，求组合数的算法
此时，由于 n < mod 且mod为素数，故comb_mod必然不为0
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll MOD = 1e9+7;
const ll MAXN = 3e5+7;
int fact[MAXN];

ll ext_gcd(ll a, ll b, ll &u, ll &v)
{
        ll d = a;
        if(b != 0) {
                d = ext_gcd(b, a%b, v, u);
                v -= a/b*u;
                u %= MOD;
                v %= MOD;
        }else {
                u = 1;
                v = 0;
        }
        return d;
}

void init_fact()
{
    fact[0] = 1;
    for(ll i = 1; i < MAXN; ++i) {
        fact[i] = (1ll*fact[i-1]*i) % MOD;
    }
}

int mod_reverse(int a, ll m)
{
    a %= m;
    ll x, y;
    ext_gcd(a, m, x, y);
    return (1ll*m + x % m) % m;
}

int comb_mod(int n, int k)
{
    if(n < 0 || k < 0 || n < k) return 0;
    return 1ll*fact[n]*mod_reverse(1ll*fact[k]*fact[n-k]%MOD, MOD)%MOD;
}

int main()
{
    int n, k;
    cin >> n >> k;
    init_fact();
    //cout << fact[n] << endl << fact[k] << endl << fact[n-k] << endl << mod_reverse(1ll*fact[k]*fact[n-k]%MOD, MOD) << endl;
    cout << comb_mod(n, k) << endl;
}
