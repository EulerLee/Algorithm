#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
using namespace std;
typedef long long ll;
typedef long double ld;
#define REP(i, n) for(ll i = 0; i < n; ++i)
#define RANGE(i, x, n) for(ll i = x; i < n; ++i)

ll prime[7] = {2, 3, 5, 7, 11, 13, 17};

ll quick_pow(ll x, ll n, ll mod)
{
    ll ans = 1;
    while(n) {
        if(n&1) {
            ans *= x;
            ans = ans%mod;
        }
        x *= x;
        x = x%mod;
        n >>= 1;
    }
    return ans;
}

bool RM(ll n, ll a, ll d, ll s)
{
    ll cure = quick_pow(a, d, n);
    //cout << "k = 1" << ":\n\t" << cure % n << endl;
    if(cure % n == 1) {
        return true;
    }
    ll k = 1;
    while(k <= s) {
        //cout << "k = " << k << ":\n\t" << cure % n << endl;
        if(cure % n == n-1) {
            return true;
        }
        ++k;
        cure *= cure;
        cure %= n;
    }
    return false;
}

bool Rabin_Miller(ll n)
{
    if(n < 2) {
        return false;
    }
    REP(i, 7) {
        if(n == prime[i]) {
            return true;
        }
    }
    ll d, s;
    ll l = 1, r = 50;
    ll mid = (l+r)>>1;
    while(r-l > 1) {
        ll pm = quick_pow(2, mid, 1e14);
        if((n-1)%pm == 0) {
            l = mid;
        }else {
            r = mid;
        }
        mid = (l+r)>>1;
    }
    s = l;
    d = (n-1)>>s;

    //cout << s << " " << d << endl;
    //cout << s*quick_pow(2,d) << endl;

    bool ans = true;
    REP(i, 7) {
        //cout << prime[i] << ":\n";
        ans &= RM(n, prime[i], d, s);
    }
    return ans;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll N;
    cin >> N;
    bool ans = Rabin_Miller(N);
    if(ans) {
        cout << "Yes" << endl;
    }else {
        cout << "No" << endl;
    }
}
