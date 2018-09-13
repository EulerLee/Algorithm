#include <iostream>
#include <unordered_set>
#include <set>
#include <vector>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <random>
#include "Jacobi.h"
using namespace std;
typedef long long ll;
#define REP(i, n) for(ll i = 0; i < n; ++i)
#define RANGE(i, x, n) for(ll i = x; i < n; ++i)
ll repeat_time = 100;

// return true stand for N may be a prime number, otherwise N is composite number
bool Solovay_Strassen_testing(ll N, ll a)
{
    if(Jacobi::gcd(N, a) != 1) return false;
    //cout << "a = " << a << ":\t" << Jacobi::Jacobi_symbol(a, N) << " " << Jacobi::quick_pow(a, (N-1)/2, N) << endl;
    return (Jacobi::Jacobi_symbol(a, N) + N)%N == Jacobi::quick_pow(a, (N-1)/2, N);
}

bool Solovay_Strassen(ll N)
{
    if(N == 2) return true;
    if(N%2 == 0 || N < 3) return false;
    bool res = true;
    std::random_device rd;  // 将用于为随机数引擎获得种子
    std::mt19937 gen(rd()); // 以播种标准 mersenne_twister_engine
    std::uniform_int_distribution<ll> dis(2, N-1);

    REP(i, repeat_time) {
        res = res&&Solovay_Strassen_testing(N, dis(gen));
    }
    return res;
}

int main()
{
    /*ll N;
    cin >> N;
    cout << boolalpha << Solovay_Strassen(N) << endl;*/
    RANGE(i, 3, 10000) {
        cout << boolalpha << i << " " << Solovay_Strassen(i) << endl;
    }
}
