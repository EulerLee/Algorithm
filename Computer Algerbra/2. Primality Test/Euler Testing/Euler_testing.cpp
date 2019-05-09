#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdlib>
using namespace std;



long long gcd(long long a, long long b)
{
    if(b == 0) return a;
    return gcd(b, a%b);
}

long long quick_pow(long long x, long long n, long long MOD = 1<<18)
{
    long long ans = 1;
    x %= MOD;
    while(n) {
        if(n&1) {
            ans *= x;
            ans %= MOD;
        }
        x *= x;
        x %= MOD;
        n >>= 1;
    }
    return ans;
}

long long find2index(long long a, long long &b)
{
    long long l, m, h;
    l = 0;
    h = 50;
    m = (l + h)/2;
    while(h - l > 1) {
        b = quick_pow(2, m);
        if(a%b == 0) {
            l = m;
        }else {
            h = m;
        }
        m = (l + h)/2;
    }
    return m;
}

long long Jacobi(long long a, long long N)
{
    if(a%N == 0) return 0;
    if(a == 1) return 1;
    if(a == N-1) return (((N-1)/2) % 2 == 0 ? 1 : -1);
    long long b, t;
    t = find2index(a, b);
    long long N_2;
    if(t%2 == 0) {
        N_2 = 1;
    }else {
        if(N%8 == 1 || N%8 == 7) {
            N_2 = 1;
        }else {
            N_2 = -1;
        }
    }
    if(b%4 == 3 && N%4 == 3) {
        return N_2*(-1)*Jacobi(N%a, a);
    }else {
        return N_2*Jacobi(N%a, a);
    }
}

bool euler_testing_based(long long N, long long a)
{
    if(N%2 == 0 || gcd(N, a) != 1) {
        return false;
    }
    long long tmp = quick_pow(a, (N-1)/2, N);
    if(tmp == 1 || tmp == N-1) {
        return false;
    }else if(tmp != Jacobi(a, N)) return false;
    else return true;
}

int main()
{
    long long N, a;
    cin >> N >> a;
    cout << boolalpha << euler_testing_based(N, a) << endl;
}
