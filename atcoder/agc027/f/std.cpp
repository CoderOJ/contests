#include <bits/stdc++.h>
using namespace std;
int read();
void chmin(int &x, int y) { x > y ? x = y : x; }

int n;
queue<int> q;
int vis[102];
struct Graph {
    int hd[102], nx[202], to[202], deg[202], cnt;
    void init() {
        cnt = 0;
        for (int i = 1; i <= n; ++i) hd[i] = deg[i] = 0;
    }
    void add(int f, int t) {
        nx[++cnt] = hd[f], hd[f] = cnt, ++deg[to[cnt] = t];
    }
    int fa[102];
    void getfa(int u) {
        for (int i = hd[u], v; i; i = nx[i])
            if ((v = to[i]) != fa[u]) fa[v] = u, getfa(v);
    }
    int topo() {
        int rt = 0;
        for (int i = 1; i <= n; ++i)
            if (vis[i] && !deg[i]) ++rt, q.push(i);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int i = hd[u], v; i; i = nx[i])
                if (!(--deg[v = to[i]])) ++rt, q.push(v);
        }
        return rt;
    }
} A, B, G;

int res;
int work() {
    int rt = 0;
    for (int i = 1; i <= n; ++i) rt += (vis[i] = A.fa[i] != B.fa[i]);
    if (rt >= res) return n + 1;
    G.init();
    for (int i = 1; i <= n; ++i) {
        if (!vis[i]) {
            if (vis[A.fa[i]]) return n + 1;
            continue;
        }
        if (vis[A.fa[i]]) G.add(i, A.fa[i]);
        if (vis[B.fa[i]]) G.add(B.fa[i], i);
    }
    return G.topo() == rt ? rt : n + 1;
}

int main() {
    int T = read();
    while (T--) {
        res = (n = read()) + 1, A.init(), B.init();
        for (int i = 1, u, v; i < n; ++i)
            u = read(), v = read(), A.add(u, v), A.add(v, u);
        for (int i = 1, u, v; i < n; ++i)
            u = read(), v = read(), B.add(u, v), B.add(v, u);
        for (int i = 1; i <= n; ++i) {
            A.fa[i] = B.fa[i] = 0, A.getfa(i), B.getfa(i), chmin(res, work());
            if (A.deg[i] == 1)
                for (int j = 1; j <= n; ++j)
                    if (i != j) {
                        A.fa[j] = i, A.getfa(j), B.getfa(i);
                        A.fa[i] = B.fa[i] = 0, chmin(res, work() + 1);
                    }
        }
        printf("%d\n", res > n ? -1 : res);
    }
    return 0;
}
const int _SIZE = 1 << 22;
char ibuf[_SIZE], *iS = ibuf, *iT = ibuf;
#define gc                                                         \
    (iS == iT ? iT = ((iS = ibuf) + fread(ibuf, 1, _SIZE, stdin)), \
     (iS == iT ? EOF : *iS++) : *iS++)
int read() {
    int x = 0, f = 1;
    char c = gc;
    while (!isdigit(c)) f = (c == '-') ? -1 : f, c = gc;
    while (isdigit(c)) x = x * 10 + c - '0', c = gc;
    return x * f;
}

