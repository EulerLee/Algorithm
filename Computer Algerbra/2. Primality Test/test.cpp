#include <iostream>
#include <unordered_set>
#include <set>
#include <vector>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <random>
using namespace std;
typedef long long ll;
#define REP(i, n) for(ll i = 0; i < n; ++i)
#define RANGE(i, x, n) for(ll i = x; i < n; ++i)

bool primetest(ll N)
{
    RANGE(i, 2, floor(sqrt(N)) + 1) {
        if(N%i == 0) return false;
    }
    return true;
}

int main()
{
    RANGE(i, 3, 10000) {
        cout << boolalpha << i << " " << primetest(i) << endl;
    }
}
