/*
基于Fermat小定理
任取整数 a, 如果 (a, N ) = 1 且 a^(N −1) !≡ 1 (mod N ), 则输出 N 为合数, 否则
输出 N 可能为素数.
*/
#include <iostream>
#include <cmath>
#include <cstring>
#include <string>
#include <cstdlib>
#include <vector>
#include <set>
using namespace std;

long long gcd(long long a, long long b)
{
    if(b == 0) return a;
    return gcd(b, a%b);
}

long long quick_pow(long long x, long long n, long long mod = 0xffffffff)
{
    long long ans = 1;
    x %= mod;
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

bool fermat_testing_based(long long N, long long a)
{
    if(gcd(N, a) != 1) {
        return false;
    }
    return gcd(quick_pow(a, N-1), N) == 1;
}

// 分别取基 a = 2 3 5 7
bool fermat_testing(long long N)
{
    bool res = true;
    set<long long> Base = {2, 3, 5, 7};
    if(Base.find(N) != Base.end()) return res;
    for(auto a: Base) {
        res = res && fermat_testing_based(N, a);
    }
    return res;
}

int main()
{
    long long N;
    cin >> N;
    cout << boolalpha << fermat_testing(N) << endl;
}
