#include <iostream>
#include <cmath>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unordered_set>

namespace Legendre {
    long long quick_pow(long long x, long long n, long long mod)
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

    int Legendre_symbol(long long a, long long p)
    {
        if(a%p == 0) return 0;
        int res = quick_pow(a, (p-1)/2, p);
        if(res != 1 && res == p-1) return -1;
        return res;
    }
}
