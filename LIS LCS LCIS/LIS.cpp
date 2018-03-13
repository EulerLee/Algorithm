/*
longest increasing subarray
dp[k] presents the min last element when the length of the increasing subarray is k
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;
typedef long long ll;
typedef long double ld;
#define REP(i, n) for(ll i = 0; i < n; ++i)
#define RANGE(i, x, n) for(ll i = x; i < n; ++i)



int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> A(n, 0);
    REP(i, n) {
        cin >> A[i];
    }

    vector<int> me(n+1, -1);
    int len = 1;
    me[len] = A[0];
    int pre_index = 0;
    RANGE(i, 1, n) {
        if(A[i] > me[len]) {
            me[++len] = A[i];
        }else {
            int l = 0;
            int r = len;
            int mid = (l+r)>>1;
            while(r-l > 1) {
                if(A[i] < me[mid]) {
                    l = mid;
                }else {
                    r = mid;
                }
                mid = (l+r)>>1;
            }
            me[l] = A[i];
        }
    }
    cout << len << endl;
}
