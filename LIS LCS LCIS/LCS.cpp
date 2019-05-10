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

/*
 * space O(2*N)
 */
int cur[5001];
int pre[5001];

int LCS(vector<int> &A, vector<int> &B)
{
    int n = A.size();
    int m = B.size();
    REP(i, n+1) {
        REP(j, m+1) {
            if(i*j == 0) {
                cur[j] = 0;
            }else {
                if(A[i-1] == B[j-1]) {
                    cur[j] = pre[j-1] + 1;
                }else {
                    cur[j] = max(pre[j], cur[j-1]);
                }
            }
        }
        memcpy(pre, cur, sizeof pre);
    }
    return cur[m];
}




int len[100][100];
int nolen[100][100];

int dp(int n, int m, vector<int> &A, vector<int> &B)
{
    if(len[n][m] != 0) {
        return len[n][m];
    }
    if(n == 0 || m == 0) {
        return 0;
    }
    if(A[n-1] == B[m-1]) {
        len[n][m] = dp(n-1, m-1, A, B) + 1;
        return len[n][m];
    }else {
        len[n][m] = max(dp(n-1, m, A, B), dp(n, m-1, A, B));
        return len[n][m];
    }
}

int no_dp(vector<int> &A, vector<int> &B)
{
    int n = A.size();
    int m = B.size();
    REP(i, n+1) {
        REP(j, m+1) {
            if(i*j == 0) {
                nolen[i][j] = 0;
            }else {
                if(A[i-1] == B[j-1]) {
                    nolen[i][j] = nolen[i-1][j-1] + 1;
                }else {
                    nolen[i][j] = max(nolen[i-1][j], nolen[i][j-1]);
                }
            }
        }
    }
    return nolen[n][m];
}

vector<int> record_path_nodp(vector<int> &A, vector<int> &B)
{
    int n = A.size();
    int m = B.size();
    vector<int> path;
    vector<vector<int>> common_elem_indexa(n+1, vector<int>(m+1, -1));
    vector<vector<int>> common_elem_indexb(n+1, vector<int>(m+1, -1));
    REP(i, n+1) {
        REP(j, m+1) {
            if(i*j == 0) {
                nolen[i][j] = 0;
            }else {
                if(A[i-1] == B[j-1]) {
                    nolen[i][j] = nolen[i-1][j-1] + 1;
                    common_elem_indexa[i][j] = i-1;
                    common_elem_indexb[i][j] = j-1;
                }else {
                    nolen[i][j] = max(nolen[i-1][j], nolen[i][j-1]);
                    if(nolen[i][j] == nolen[i-1][j]) {
                        common_elem_indexa[i][j] = common_elem_indexa[i-1][j];
                        common_elem_indexb[i][j] = common_elem_indexb[i-1][j];
                    }else {
                        common_elem_indexa[i][j] = common_elem_indexa[i][j-1];
                        common_elem_indexb[i][j] = common_elem_indexb[i][j-1];
                    }
                }
            }
        }
    }
    int cura = common_elem_indexa[n][m];
    int curb = common_elem_indexb[n][m];
    while(cura >= 0 && curb >= 0) {
        path.push_back(A[cura]);
        int nexta = common_elem_indexa[cura][curb];
        int nextb = common_elem_indexb[cura][curb];
        cura = nexta;
        curb = nextb;
    }
    REP(i, path.size()) {
        cout << path[path.size()-1-i] << " ";
    }
    cout << endl;
    return path;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> A(n, 0);
    vector<int> B(m, 0);
    REP(i, n) {
        cin >> A[i];
    }
    REP(i, m) {
        cin >> B[i];
    }

    cout << dp(n, m, A, B) << endl;
    cout << no_dp(A, B) << endl;
    record_path_nodp(A, B);
}
