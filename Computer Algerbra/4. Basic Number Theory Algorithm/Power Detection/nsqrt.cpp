#include <iostream>
#include <cmath>
using namespace std;
typedef long long ll;

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

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    ll N;
    cin >> N;
    cout << nsqrt(N) << endl;
}
