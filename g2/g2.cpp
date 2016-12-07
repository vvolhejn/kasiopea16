// this code continues the series of "code in which immigration is used as a way to segue to robocop" found irregularly peppered throughout the historical record
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <set>
#include <map>
#include <queue>
#include <stack>
#include <cstring>
#include <cassert>
#include <unordered_set>
using namespace std;
#define rep(i,a,n) for (int i=a;i<(n);i++)
#define per(i,a,n) for (int i=(n)-1;i>=(a);i--)
template<typename T> ostream& operator<<(ostream& s, vector<T> t) {rep(i, 0, t.size()) s << (i ? " " : "") << t[i]; return s;}
template<typename T> istream& operator>>(istream& s, vector<T> &t) {rep(i, 0, t.size()) s >> t[i]; return s;}
typedef long long ll;
#define x first
#define y second
typedef pair<int, int> pt;
const double EPS = 1e-9;
const int N = 666;
double a[N][N], b[N][N];
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int h, w;

int root[N * N];
int value[N * N];
int getRoot(int x) {return (root[x] == x) ? x : (root[x] = getRoot(root[x]));}
void merge(int x, int y) {
    x = getRoot(x), y = getRoot(y);
    if (x == y) return;
    value[y] += value[x];
    root[x] = y;
}

int toID(int x, int y) {
    return x * N + y;
}

bool inBounds(int i, int j) {
    return i >= 0 && j >= 0 && i < h && j < w;
}

struct edge {
    int u, v;
    double t = 0;
    bool always = false, never = false, seen = false;
    edge(pt p1, pt p2) {
        u = toID(p1.x, p1.y);
        v = toID(p2.x, p2.y);
        double a1 = a[p1.x][p1.y],
               b1 = b[p1.x][p1.y],
               a2 = a[p2.x][p2.y],
               b2 = b[p2.x][p2.y];
        if (b1 == b2) {
            if (a1 == a2) always = true;
            else never = true;
        } else {
            t = (a2 - a1) / (b1 - b2);
            if (t < 0) never = true;
        }
    }
};

vector<int> g[N * N];

void solve() {
    rep(i, 0, N * N) g[i].clear(), root[i] = i, value[i] = 1;
    cin >> h >> w;
    rep(i, 0, h) rep(j, 0, w) cin >> a[i][j];
    rep(i, 0, h) rep(j, 0, w) cin >> b[i][j];
    
    vector<edge> e;
    
    rep(i, 0, h) rep(j, 0, w) rep(dir, 0, 2) {
        int ni = i + dx[dir];
        int nj = j + dy[dir];
        if (!inBounds(ni, nj)) continue;
        edge ce({i, j}, {ni, nj});
        if (ce.never) continue;
        if (ce.always) merge(toID(i, j), toID(ni, nj));
    }
    
    rep(i, 0, h) rep(j, 0, w) rep(dir, 0, 2) {
        int ni = i + dx[dir];
        int nj = j + dy[dir];
        //cout << i << " " << j << " | " << ni << " " << nj << endl;
        if (!inBounds(ni, nj)) continue;
        edge ce({i, j}, {ni, nj});
        if (ce.never || ce.always) continue;
        else {
            ce.u = getRoot(toID(i, j));
            ce.v = getRoot(toID(ni, nj));
            g[getRoot(toID(i, j))].push_back(e.size());
            g[getRoot(toID(ni, nj))].push_back(e.size());
            e.push_back(ce);
        }
    }
    int res = 0;
    rep(i, 0, h) rep(j, 0, w) res = max(res, value[toID(i, j)]);
    
    /*rep(i, 0, h) rep(j, 0, w) {
        if (getRoot(toID(i, j)) == toID(i, j))
            cout << value[toID(i, j)] << endl;
    }*/
    
    rep(i, 0, e.size()) {
        if (e[i].seen) continue;
        queue<int> q({i});
        e[i].seen = true;
        unordered_set<int> visited;
        double ct = e[i].t;
        while (!q.empty()) {
            int cur = q.front(); q.pop();
            for (int x : {e[cur].u, e[cur].v}) {
                if (visited.count(x)) continue;
                visited.insert(x);
                for (auto ne : g[x]) {
                    if (e[ne].seen) continue;
                    if (fabs(e[ne].t - ct) > EPS) continue;
                    e[ne].seen = true;
                    q.push(ne);
                }
            }
        }
        int cur = 0;
        for (auto x : visited) cur += value[x];
        // for (auto x : visited)cout << x << " "; cout << endl;
        res = max(res, cur);
    }
    cout << res << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    int q;
    cin >> q;
    while (q--) {
        solve();
    }
}


