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
    vector<int> preindex(n+1, -1);
    vector<int> index(n+1, -1);

    int len = 1;
    index[len] = 0;
    me[len] = A[0];
    int pre_index = 0;
    RANGE(i, 1, n) {
        if(A[i] > me[len]) {
            me[++len] = A[i];
            index[len] = i;
            preindex[i] = index[len-1];
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
            index[l] = i;
            preindex[i] = index[l-1];
        }
    }
    cout << len << endl;
    int curindex = index[len];
    vector<int> ans;
    while(curindex != -1) {
        ans.push_back(A[curindex]);
        curindex = preindex[curindex];
    }
    for(int i = ans.size()-1; i >=0; --i) {
        cout << ans[i] << " ";
    }
    cout << endl;
}
