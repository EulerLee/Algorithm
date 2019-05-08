#include <iostream>
#include <cmath>
using namespace std;
typedef long long ll;

ll ext_gcd(ll a, ll b, ll &u, ll &v)
{
        ll d = a;
        if(b != 0) {
                d = ext_gcd(b, a%b, v, u);
                v -= a/b*u;
        }else {
                u = 1;
                v = 0;
        }
        return d;
}

int main()
{
        ll a, b;
        cin >> a >> b;
        cout << ext_gcd(a, b) << endl;
}
