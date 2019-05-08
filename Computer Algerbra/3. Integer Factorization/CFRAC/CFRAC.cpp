#pragma comment(linker, "/stack:247474112")
#pragma GCC optimize("Ofast")

#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
using namespace std;

ll gcd(ll a, ll b)
{
    if(b == 0) return a;
    return gcd(b, a%b);
}

ll quickpow(ll x, ll n, ll mod = 1e9+7)
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

ll nsqrt(ll N)
{
    ll x = N;
    ll y = floor((floor(N/x) + x)/2);
    while(y < x) {
        x = y;
        y = floor((floor(N/x) + x)/2);
    }
    return x;
}

vector<ll> gett(ll P, ll Q, ll N, vector<ll> &FB)
{
    ll t = (P*P-N*Q*Q)%N;   // t != 0 for N if not square
    if(abs(t) >= N/2) {
        if(t>0) t-=N;
        else t+=N;
    }
    vector<ll> ans(1);
    if(t < 0) {
        ans[0] = 1;
        t = -t;
    }
    for(int i = 1; i < FB.size(); ++i) {
        ll tmp = 0;
        while(t%FB[i] == 0) {
            t /= FB[i];
            ++tmp;
        }
        ans.push_back(tmp);
    }
    if(t != 1) {
        ans.clear();
    }

    return ans;
}

ll CFRAC(ll N, vector<ll> &FB)
{
    int i = 0;
    ll a = nsqrt(N);
    ld rem = sqrt((ld)N)-a;
    ll P = a;
    ll Q = 1;
    ll ppre, qpre;
    vector<vector<ll>> X;
    vector<ll> chosenP;
    //while(i<10) {
    while(X.size() <= FB.size()*2) {
        ll t = (P*P-N*Q*Q)%N;
        if(abs(t) >= N/2) {
            if(t>0) t-=N;
            else t+=N;
        }
        cout << i << ":\t" << a << "\t" << P << "\t" << Q << "\t" << t;
        vector<ll> tmp = gett(P, Q, N, FB);
        if(tmp.size() > 0) {
            X.push_back(tmp);
            chosenP.push_back(P);
            cout << "\tchose " << P%N;
        }
        cout << endl;
        ++i;
        rem = 1.0/rem;
        a = floor(rem);
        rem = rem-a;
        if(i == 1) {
            ppre = P;
            qpre = Q;
            P = nsqrt(N)*a+1;
            Q = a;
            P%=N;
            Q%=N;
        }else {
            ll np = a*P+ppre;
            np%=N;
            ll nq = a*Q+qpre;
            nq%=N;
            ppre = P;
            qpre = Q;
            P = np;
            Q = nq;
        }
    }

    cout << "vector is:" << endl;
    int cnt = 0;
    for(auto vx: X) {
        cout << cnt << ":\t";
        for(auto x: vx) {
            cout << x << " ";
        }
        cout << endl;
        ++cnt;
    }


    bool flag = false;
    while(!flag) {
        vector<int> chosen;
        int num_chosen;
        cout << "The number of chosen vectors: ";
        cin >> num_chosen;
        cout << endl;
        cout << "chose index(from 0): ";
        for(int i = 0; i < num_chosen; ++i) {
            int tmp;
            cin >> tmp;
            chosen.push_back(tmp);
        }
        ll x = 1;
        ll y = 1;
        vector<ll> vy(FB.size());
        for(auto e: chosen) {
            x = x*chosenP[e]%N;
            for(int i = 0; i < FB.size(); ++i) {
                vy[i] += X[e][i];
            }
        }
        for(int i = 0; i < FB.size(); ++i) {
            vy[i] >>= 1;
            y = y*quickpow(FB[i], vy[i], N)%N;
        }
        cout << "x, y: " << x << " " << y << endl;
        if((x+y)%N == 0 || (x-y)%N == 0) continue;
        flag = true;
        cout << "gcd(N, x-y) is " << gcd(N, x-y) << endl;
        cout << "gcd(N, x+y) is " << gcd(N, x+y) << endl;

    }

    return 0;
}

int main()
{
    ll N, K;
    cin >> N >> K;
    vector<ll> FB(K);
    for(int i = 0; i < K; ++i) {
        cin >> FB[i];
    }
    CFRAC(N, FB);
}
