#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
typedef long long ll;

ll nsqrt(ll N)
{
        if(N == 0) return 0;
    ll x = N;
    ll y = floor((floor(N/x) + x)/2);
    while(y < x) {
        x = y;
        y = floor((floor(N/x) + x)/2);
    }
    return x;
}

void init_Qn(vector<ll> &Qn)
{
        int n = Qn.size();
        for(int i = 0; i < n; ++i) {
                Qn[i*i % n] = 1;
        }
}

bool square_detection(ll N)
{
        vector<ll> Q64(64, 0);
        vector<ll> Q63(63, 0);
        vector<ll> Q65(65, 0);
        vector<ll> Q11(11, 0);
        init_Qn(Q64);
        init_Qn(Q63);
        init_Qn(Q65);
        init_Qn(Q11);
        if(Q64[N%64] == 0) return false;
        ll r = N % 63*65*11;
        //if(Q63[N%63] == 0 || Q65[N%65] == 0 || Q11[N%11] == 0) return false;
        if(Q63[r%63] == 0) return false;
        //N %= 65*11;
        if(Q65[r%65] == 0) return false;
        r %= 11;
        if(Q11[r] == 0) return false;
        return nsqrt(N)*nsqrt(N) == N;
}

int main()
{
        ll N;
        cin >> N;
        cout << boolalpha << square_detection(N) << endl;
}
