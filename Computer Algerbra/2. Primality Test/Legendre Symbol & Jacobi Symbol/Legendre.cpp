#include "Legendre.h"
using namespace std;

int main()
{
    long long a, p;
    cin >> a >> p;
    cout << Legendre::Legendre_symbol(a, p) << endl;
}
