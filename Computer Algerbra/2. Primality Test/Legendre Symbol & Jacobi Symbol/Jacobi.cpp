#include "Jacobi.h"
#include "Legendre.h"
using namespace std;
int main()
{
    long long a, m;
    cin >> a >> m;
    cout << Jacobi::Jacobi_symbol(a, m) << endl;
}
