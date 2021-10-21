#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <iomanip>
using namespace std;

struct Gaussian_Elimination {
    double a[20][20], b[20];
    int n;
    int rank;
    int possible;
    void execute();
    bool check_possible();
    int get_rank();
    void print_ans();
    void print();
};

void Gaussian_Elimination::print()
{
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            cout << a[i][j] << " ";
        }
        cout << b[i] << endl;
    }
}

void Gaussian_Elimination::execute()
{
    for(int i = 0; i < n; ++i) {
        // 找到 xi 的系数不为 0 的行, 换到第 i 行
        for(int j = i; j < n; ++j) {
            if(fabs(a[j][i]) > 1e-8) {
                for(int k = 0; k < n; ++k) {
                    swap(a[i][k], a[j][k]);
                }
                swap(b[i], b[j]);
                break;
            }
        }
        // 消去其他行中的 xi
        for(int j = 0; j < n; ++j) {
            if(i == j) continue;
            double rate = a[j][i] / a[i][i];
            for(int k = i; k < n; ++k) {
                a[j][k] -= a[i][k] * rate;
            }
            b[j] -= b[i] * rate;
        }
    }
}

bool Gaussian_Elimination::check_possible()
{
    for(int i = 0; i < n; ++i) {
        if(a[i][i] == 0 && b[i] != 0) return false;
    }
    return true;
}

int Gaussian_Elimination::get_rank()
{
    int rank = n;
    for(int i = 0; i < n; ++i) {
        if(a[i][i] == 0) --rank;
    }
    return rank;
}

void Gaussian_Elimination::print_ans()
{
    for(int i = 0; i < n; ++i) {
        cout << fixed << setprecision(3) << b[i] / a[i][i] << " ";
    }
    cout << endl;
}

int main()
{
    Gaussian_Elimination GE;
    int n;
    cin >> n;
    GE.n = n;
    for(int i = 0; i < n; ++i) {
        for(int j = 0; j < n; ++j) {
            cin >> GE.a[i][j];
        }
        cin >> GE.b[i];
    }

    // GE.print();
    GE.execute();
    cout << boolalpha << GE.check_possible() << endl;
    cout << GE.get_rank() << endl;
    GE.print_ans();
}