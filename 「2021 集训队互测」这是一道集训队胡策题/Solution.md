```cpp
#include <bits/stdc++.h>
using namespace std;
#define open(x) freopen(x ".in", "r", stdin);freopen(x ".out", "w", stdout);
#define pb emplace_back

int clo = 0;
const int p = 998244353;
const int MAXN = 1e5 + 5;
int dfn[MAXN];
int low[MAXN];
int scc[MAXN];
int instk[MAXN];
int cnt = 0;
vector<int> a[MAXN], e[MAXN];
stack<int> stk;
queue<int> q;
int pw[MAXN], d[MAXN];
int n;

inline void dfs(int x) {
    dfn[x] = low[x] = ++clo;
    stk.push(x);
    instk[x] = 1;

    for (auto v : a[x]) {
        if (!dfn[v]) {
            dfs(v);
            low[x] = min(low[x], low[v]);
        } else if (instk[v]) {
            low[x] = min(low[x], dfn[v]);
        }
    }

    if (low[x] == dfn[x]) {
        ++cnt;

        while (stk.top() != x) {
            int t = stk.top();
            stk.pop();
            scc[t] = cnt;
            instk[t] = 0;
        }

        stk.pop();
        scc[x] = cnt;
        instk[x] = 0;
    }

    return;
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    char c;

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> c;

            if (c == '1')
                a[i].pb(j + n);
            else
                a[j + n].pb(i);
        }
    }

    for (int i = 1 ; i <= 2 * n ; ++i) {
        if (!dfn[i]) {
            dfs(i);
        }
    }

    for (int i = 1; i <= 2 * n; ++i) {
        for (auto v : a[i]) {
            if (scc[i] != scc[v]) {
                e[scc[i]].pb(scc[v]);
                d[scc[v]]++;
            }
        }
    }

    for (int i = 1; i <= cnt; ++i) {
        if (!d[i])
            q.push(i);
    }

    int ans = 1;
    pw[0] = 1;

    for (int i = 1; i <= 2 * n; ++i)
        pw[i] = pw[i - 1] * 2 % p;

    while (!q.empty()) {
        int t = q.front();
        q.pop();
        ans = (ans + pw[q.size()] % p) % p;

        for (auto v : e[t]) {
            --d[v];

            if (!d[v])
                q.push(v);
        }
    }

    cout << ans;
    return 0;
}
```
