#pragma GCC optimize(0)
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("fast")
#pragma GCC target(avx)

#include <iostream>
#include <cstdio>
#include <map>
#include <set>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <cmath>
#include <cstring>
#include <bitset>
#include <sstream>
using namespace std;

#ifndef CUSTOM_MAIN
void init();
void solve();
int main() {
    try {
#ifdef MULTIPLE_TEST_CASES_WITH_T

        int T;
        scanf("%d", &T);
        while (T--) {
            init();
            solve();
        }

#else
#ifdef MULTIPLE_TEST_CASES_WITHOUT_T

        while (1) {
            try {
                init();
            } catch (bool t) {
                return 0;
            }
            solve();
        }

#else

        init();
        solve();

#endif
#endif

    } catch (...) {
        return 0;
    }
    return 0;
}
#endif

#ifdef ENABLE_LL
#define int long long
#endif

#ifdef ENABLE_LL
#define I "%lld"
#define II "%lld%lld"
#define III "%lld%lld%lld"
#define IIII "%lld%lld%lld%lld"
#define IN "%lld\n"
#define IIN "%lld%lld\n"
#define IIIN "%lld%lld%lld\n"
#define IIIIN "%lld%lld%lld%lld\n"
#else
#define I "%d"
#define II "%d%d"
#define III "%d%d%d"
#define IIII "%d%d%d%d"
#define IN "%d\n"
#define IIN "%d%d\n"
#define IIIN "%d%d%d\n"
#define IIIIN "%d%d%d%d\n"
#endif

#ifdef __LOCALE__
#define see(a) std::cout << #a << "=" << a << std::endl
#define ses(a) std::cout << #a << "=" << a << " "
#else
#define see(a)  // std::cout << #a << "=" << a << std::endl
#define ses(a)
#endif
#define repe(a, b) for (int a = 0; a < (int)b.size(); a++)
#define rep(i, n) for (int i = 0; i < n; i++)
#define repa(i, n) for (int i = 1; i <= n; i++)
#define repi(i, a, b) for (int i = a; i <= b; i++)
#define repb(i, a, b) for (int i = a; i >= b; i--)
#define L first
#define R second
template <class T>
inline bool checkMin(T& a, T b) {
    return (a > b ? a = b, 1 : 0);
}
template <class T>
inline bool checkMax(T& a, T b) {
    return (a < b ? a = b, 1 : 0);
}

const int MOD = (int)(1e9) + 7;
const int N = 150005;
int n, m, q;
struct Edge {
    int u, v, w;
};
Edge e[N];

struct pr {
    int L, R;
    bool operator<(const pr& b) const { return L < b.L; }
    pr() {}
    pr(int L, int R) : L(L), R(R) {}
};

namespace Data {
int A, B, C, P;
inline void init() { scanf(IIII, &A, &B, &C, &P); }
inline int rnd() { return A = (A * B + C) % P; }
}  // namespace Data

void init() {
    scanf(II, &n, &m);
    rep(i, m) {
        int u, v, w;
        scanf(III, &u, &v, &w);
        e[i] = { u, v, w };
    }
    sort(e, e + m, [](Edge x, Edge y) { return x.w < y.w; });
}

struct Dsu {
    int p[N];
    Dsu() { rep(i, N) p[i] = i; }
    int get(int u) { return u == p[u] ? u : p[u] = get(p[u]); }
    void merge(int u, int v) { p[get(v)] = get(u); }
    bool query(int u, int v) { return get(u) == get(v); }
};

vector<int> ke[N];
int w[N], fa[N];
pr euler[N * 2];
template <class T>
struct STable {
    static const int B = 19;
    T vr[N * 2][B];
    int lg[N * 2];

    void init(T* a, int n) {
        lg[1] = 0;
        repi(i, 2, 2 * N - 1) lg[i] = lg[i / 2] + 1;
        rep(i, n) vr[i][0] = a[i];
        rep(b, B - 1) {
            int l = (1 << b);
            repi(i, l, n) {
                if (i - l >= 0)
                    vr[i][b + 1] = min(vr[i][b], vr[i - l][b]);
            }
        }
    }

    T query(int l, int r) {
        if (l > r) l^=r^=l^=r;
        int len = (r - l) + 1;
        int b = lg[len];
        return min(vr[l + (1 << b) - 1][b], vr[r][b]);
    }
};

int eulerWei[N];
int eulerCnt = 0;
void dfs(int u, int dep = 0) {
    eulerWei[u] = eulerCnt;
    euler[eulerCnt++] = { dep, u };
    for (int v : ke[u]) {
        fa[v] = u;
        dfs(v, dep + 1);
        euler[eulerCnt++] = { dep, u };
    }
}

STable<pr> getMin;

void solve() {
    int r = n + 1;
    Dsu st;
    rep(i, m) {
        int u = e[i].u, v = e[i].v;
        int pu = st.get(u), pv = st.get(v);
        if (pu == pv)
            continue;
        st.merge(r, pu);
        st.merge(r, pv);
        ke[r].push_back(pu);
        ke[r].push_back(pv);
        w[r] = e[i].w;
        r++;
    }
    dfs(r - 1);
    getMin.init(euler, eulerCnt);
    see("init_pass");
    int q; scanf(I, &q);
    Data::init();
    int ans = 0;
    while (q--) {
        int u = Data::rnd() % n + 1;
        int v = Data::rnd() % n + 1;
        int id = getMin.query(eulerWei[u], eulerWei[v]).R;
        if (id <= n)
            continue;
        (ans += w[id]);
        if (ans >= MOD) ans -= MOD;
    }
    printf(IN, ans);
}
