// this code continues the series of "code in which immigration is used as a way to segue to robocop" found irregularly peppered throughout the historical record
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#define rep(i,a,n) for(int i=a;i<(n);i++)
#define per(i,a,n) for(int i=(n)-1;i>=(a);i--)
typedef long long ll;
#define x first
#define y second
const double EPS = 1e-9;
#define N 100
double a[N][N], b[N][N];
bool seen[N][N];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
double times[N * N]; int tn = 0;
int sti[N * N], stj[N * N]; int stn = 0; // dfs

int h, w;

bool inBounds(int i, int j) {
    return i >= 0 && j >= 0 && i < h && j < w;
}

bool canGo(int i, int j, int ni, int nj, double t) {
    if (!inBounds(ni, nj)) return false;
    if (seen[ni][nj]) return false;
    if (b[i][j] == b[ni][nj]) return a[i][j] == a[ni][nj];
    double t1 = (a[ni][nj] - a[i][j]) / (b[i][j]  - b[ni][nj]);
    return fabs(t1 - t) <= EPS;
}

void solve() {
    scanf("%d%d", &h, &w);
    rep(i, 0, h) rep(j, 0, w) scanf("%lf", &a[i][j]);
    rep(i, 0, h) rep(j, 0, w) scanf("%lf", &b[i][j]);
    tn = 0;
    times[tn++] = 0;
    rep(i, 0, h) rep(j, 0, w) rep(dir, 0, 2) {
        int ni = i + dx[dir];
        int nj = j + dy[dir];
        if (!inBounds(ni, nj)) continue;
        if (b[i][j] != b[ni][nj]) {
            times[tn++] = (a[ni][nj] - a[i][j]) / (b[i][j] - b[ni][nj]);
        }
    }
    int res = 0;
    rep(t, 0, tn) {
        if (times[t] < 0) continue;
        memset(seen, 0, sizeof(seen));
        rep(si, 0, h) rep(sj, 0, w) {
            if (seen[si][sj]) continue;
            seen[si][sj] = true;
            int cnt = 0;
            stn = 1;
            sti[0] = si; stj[0] = sj;
            
            while (stn) {
                cnt++;
                int i = sti[stn - 1];
                int j = stj[stn - 1];
                stn--;
                rep(dir, 0, 4) {
                    int ni = i + dx[dir];
                    int nj = j + dy[dir];
                    if (canGo(i, j, ni, nj, times[t])) {
                        seen[ni][nj] = true;
                        sti[stn] = ni;
                        stj[stn] = nj;
                        stn++;
                    }
                }
            }
            res = cnt > res ? cnt : res;
        }
    }
    printf("%d\n", res);
}

int main() {
    int q;
    scanf("%d", &q);
    while (q--) solve();
}


