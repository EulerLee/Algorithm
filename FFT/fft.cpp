#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll mod = 65537;
ll N;  // 拓展后的n
ll g = 3;  // 原根

ll quick_pow(ll x, ll n)
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

void init(const vector<ll> &A)
{
    ll n = A.size();
    N = 1;
    while(N < n) N <<= 1;

}

inline ll rev(ll k)
{
    ll res = 0;
    for(ll i = 1; i < N; i <<= 1) {
        res <<= 1;
        res |= k&1;
        k >>= 1;
    }
    return res;
}

void bit_rev_cpy(const vector<ll> &src, vector<ll> &dst)
{
    ll n = src.size();
    dst.resize(n);
    for(ll k = 0; k < n; ++k) {
        cout << k << ":\t" << rev(k) << endl;
        dst[rev(k)] = src[k];
    }
}

vector<ll> FFT(const vector<ll> &_a, int rev_flg = 0)
{
    vector<ll> A;
    bit_rev_cpy(_a, A);
    //for(auto x: A) cout << x << " "; cout << endl;
    ll n = A.size();
    for(ll m = 2; m <= n; m <<= 1) {    // height-1 rounds
        ll wn = quick_pow(g, (mod-1)/m);
        //cout << "w" << m << ":\t" << wn << endl;
        if(rev_flg) {
            wn = quick_pow(wn, m-1);
        }
        for(ll k = 0; k < n; k += m) {
            ll w = 1;
            //ll n1 = quick_pow(m, mod-2);
            for(ll j = 0; j < m/2; ++j) {
                ll t = w*A[k+j+m/2]%mod;
                ll u = A[k+j];
                A[k+j] = (u+t)%mod;
                A[k+j+m/2] = (u-t+mod)%mod;
                w = w*wn%mod;
            }
        }
        //for(auto x: A) cout << x << " "; cout << endl;
    }
    ll n1 = quick_pow(n, mod-2);
    if(rev_flg) {
        for(auto &x: A) {
            x = x*n1%mod;
        }
    }
    return A;
}

ll honor(const vector<ll> &A, ll x)
{
    ll ans = 0;
    for(ll i = (ll)A.size()-1; i >= 0; --i) {
        ans = A[i] + x*ans%mod;
        ans %= mod;
    }
    return ans;
}

int main()
{
    vector<ll> A{0,5,3,7,7,2,1,6};
    init(A);
    auto B = FFT(A);
    for(auto x: B) cout << x << " "; cout << endl;
    ll x = 1;
    ll gn = quick_pow(g, (mod-1)/N);
    for(ll i = 0; i < 8; ++i) {
        cout << honor(A, x) << " ";
        x *= gn;
        x %= mod;
    }
    cout << endl;
    auto C = FFT(B, 1);
    for(auto x: C) cout << x << " "; cout << endl;

    /*vector<ll> D;
    int m;
    cin >> m;
    for(int i = 0; i < m; ++i) cin >> D[i];
    D = FFT(D, 1);
    for(auto x: D) cout << x << " "; cout << endl;*/
}
