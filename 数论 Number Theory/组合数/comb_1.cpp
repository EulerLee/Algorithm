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
int rvs[MAXN];

int quickpow_mod(int x, int n)
{
    int res = 1;
    while(n) {
        if(n & 1) {
            res = 1ll*res*x % MOD;
        }
        x = 1ll*x*x%MOD;
        n >>= 1;
    }
    return res;
}

void init_fact()
{
    fact[0] = 1;
    for(ll i = 1; i < MAXN; ++i) {
        fact[i] = (1ll*fact[i-1]*i) % MOD;
    }
}

void init_rvs()
{
    rvs[MAXN-1] = quickpow_mod(fact[MAXN-1], MOD-2);
    for(int i = MAXN-1; i > 0; --i) {
        rvs[i-1] = 1ll*i*rvs[i] % MOD;
    }
}

/*
// 由于 [(MAXN-1)!]^(MOD-1) == 1 mod MOD
// Fermat 小定理
// fact[n] * rvs[k] * rvs[n-k] 即为所求
*/
int comb_mod(int n, int k)
{
    if(n < 0 || k < 0 || n < k) return 0;
    return (1ll*fact[n]*rvs[k] % MOD) * rvs[n-k] % MOD;
}

int main()
{
    int n, k;
    cin >> n >> k;

    // 先打表
    // init_fact()
    fact[0] = 1;
    for(int i = 1; i < MAXN; ++i) {
        fact[i] = (1ll*fact[i-1]*i) % MOD;
    }
    // 计算 [(MAXN-1)!]^(MOD-1) / (k!)
    // init_rvs()
    rvs[MAXN-1] = quickpow_mod(fact[MAXN-1], MOD-2);
    for(int i = MAXN-1; i > 0; --i) {
        rvs[i-1] = 1ll*i*rvs[i] % MOD;
    }

    cout << comb_mod(n, k) << endl;
}
