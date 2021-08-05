#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#define setIO(x) freopen(x".in", "r", stdin), freopen(x".out", "w", stdout)
#define closefile fclose(stdin), fclose(stdout)
#define m_p make_pair
#define sz(x) (int)x.size()
#define see(x) cerr << x << " "
#define seeln(x) cerr << x << endl
#define out(x) cerr << #x << " = " << x << " "
#define outln(x) cerr << #x << " = " << x << endl
#define outarr(x, l, r) {cerr << #x"[" << l << " ~ " << r << "] = "; for (int _i = l; _i <= r; ++_i) cerr << x[_i] << " "; cerr << endl;}
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> Poly;
template <class T> bool checkmax(T &a, T b){return a < b ? a = b, 1 : 0;}
template <class T> bool checkmin(T &a, T b){return b < a ? a = b, 1 : 0;}
const int N = 100005, mod = 998244353;
void add(int &a, int b){a += b; (a >= mod) && (a -= mod);}
void sub(int &a, int b){a -= b; (a < 0) && (a += mod);}
void mul(int &a, int b){a = (ll)a * b % mod;}
int Add(int a, int b){a += b; return a >= mod ? a - mod : a;}
int Sub(int a, int b){a -= b; return a < 0 ? a + mod : a;}
int Mul(int a, int b){return (ll)a * b % mod;}
int qpow(int a, int b){int ans = 1; while (b) {if (b & 1) mul(ans, a); mul(a, a); b >>= 1;} return ans;}
int Inv(int x){return qpow(x, mod - 2);}
int fac[100005], ifac[100005], inv[100005];
int binom(int n, int m){return n < m ? 0 : Mul(fac[n], Mul(ifac[m], ifac[n - m]));}
void prepare(int n)
{
    fac[0] = 1; for (int i = 1; i <= n; ++i) fac[i] = Mul(fac[i - 1], i);
    inv[1] = 1; for (int i = 2; i <= n; ++i) inv[i] = Mul(inv[mod % i], mod - mod / i);
    ifac[0] = 1; for (int i = 1; i <= n; ++i) ifac[i] = Mul(ifac[i - 1], inv[i]);
}
 
int n;
vector<int> G[N];
void init()
{
    prepare(100000);
    scanf("%d", &n);
    for (int i = 1, u, v; i < n; ++i)
    {
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
}
 
namespace fft
{
    vector<int> w[23];
    int rev[1 << 19];
    void prepare(int n = 19)
    {
        for (int i = 1; i <= n; ++i)
        {
            w[i].resize(1 << i);
            w[i][0] = 1; w[i][1] = qpow(3, (mod - 1) >> i);
            for (int j = 2; j < (1 << i); ++j) w[i][j] = Mul(w[i][j - 1], w[i][1]);
        }
    }
 
    void init(int n)
    {
        for (int i = 0; i < n; ++i) rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
    }
 
    void dft(int *a, int n)
    {
        for (int i = 0; i < n; ++i) if (i < rev[i]) swap(a[i], a[rev[i]]);
        for (int mid = 1, rnd = 1; mid < n; mid <<= 1, ++rnd)
        {
            for (int i = 0; i < n; i += (mid << 1))
            {
                int *W = &w[rnd][0], *l = a + i, *r = a + i + mid;
                for (int j = 0; j < mid; ++j, ++W, ++l, ++r)
                {
                    int t = Mul(*W, *r);
                    *r = Sub(*l, t);
                    add(*l, t);
                }
            }
        }
    }
 
    void idft(int *a, int n)
    {
        dft(a, n); reverse(a + 1, a + n);
        int I = qpow(n, mod - 2);
        for (int i = 0; i < n; ++i) mul(a[i], I);
    }
}
using fft::dft;
using fft::idft;
int f[1 << 19], g[1 << 19];
 
int dep[N], buc[N], seq[N];
int Min, rt, mx;
int siz[N], vis[N];
int F[1 << 19], A[1 << 19];
void get_siz(int x, int f)
{
    siz[x] = 1;
    for (auto &to : G[x]) if (to != f && !vis[to])
    {
        get_siz(to, x);
        siz[x] += siz[to];
    }
}
 
void get_root(int x, int f, int all)
{
    siz[x] = 1;
    int mp = 0;
    for (auto &to : G[x]) if (to != f && !vis[to])
    {
        get_root(to, x, all);
        siz[x] += siz[to];
        checkmax(mp, siz[to]);
    }
    checkmax(mp, all - siz[x]);
    if (checkmin(Min, mp)) rt = x;
}
 
void dfs(int x, int f)
{
    dep[x] = dep[f] + 1;
    A[dep[x]]++;
    checkmax(mx, dep[x]);
    for (auto &to : G[x]) if (to != f && !vis[to]) dfs(to, x);
}
 
void calc(int x, int typ)
{
    mx = 0, dfs(x, 0);
    int l = 1;
    while (l <= mx + mx) l <<= 1;
    for (int i = mx + 1; i < l; ++i) A[i] = 0;
    fft::init(l);
    dft(A, l);
    for (int i = 0; i < l; ++i) A[i] = Mul(A[i], A[i]);
    idft(A, l);
    if (typ == 0)
    {
        for (int i = 0; i <= mx + mx; ++i) add(F[i], A[i]);
    }
    else
    {
        for (int i = 0; i <= mx + mx; ++i) sub(F[i + 2], A[i]);
    }
    for (int i = 0; i < l; ++i) A[i] = 0;
}
 
void divi(int x)
{
    vis[x] = 1;
    calc(x, 0);
    for (auto &to : G[x]) if (!vis[to]) calc(to, 1);
    for (auto &to : G[x]) if (!vis[to])
    {
        Min = n + 1, rt = 0, get_siz(to, x), get_root(to, x, siz[to]);
        divi(rt);
    }
}
 
void solve()
{
    fft::prepare();
    /*dep[0] = -1;
    for (int i = 1; i <= n; ++i)
    {
        dfs(i, 0);
        for (int j = 1; j <= n; ++j) buc[dep[j]]++;
    }*/
    dep[0] = -1;
    Min = n + 1, rt = 0, get_root(1, 0, n); divi(1);
    int l = 1;
    while (l <= n + n) l <<= 1;
    for (int i = 0; i < l; ++i) f[i] = g[i] = 0;
    for (int i = 0; i < n; ++i) f[i] = Mul(fac[i], F[n - 1 - i]);
    for (int i = 0; i < n; ++i) g[n - i] = ifac[i];
    fft::init(l);
    dft(f, l); dft(g, l);
    for (int i = 0; i < l; ++i) mul(f[i], g[i]);
    idft(f, l);
    /*for (int j = 0; j < n; ++j)
    {
        for (int k = 0; k <= j + n; ++k)
        {
            add(seq[j], Mul(f[k], g[j + n - k]));
        }
    }*/
    for (int i = 0; i < n; ++i) seq[i] = f[i + n];
    for (int i = 0; i < n; ++i) mul(seq[i], ifac[i]);
    for (int i = 0; i < n; ++i) mul(seq[i], Inv(binom(n - 1, i)));
    for (int i = 0; i < n; ++i) printf("%d%c", seq[i], " \n"[i == n - 1]);
}
 
int main()
{
    //setIO("treecut");
    init();
    solve();
    return 0;
}
