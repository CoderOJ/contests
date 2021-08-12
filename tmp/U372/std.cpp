#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <vector>
#define setIO(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout)
#define closefile fclose(stdin), fclose(stdout)
#define m_p make_pair
#define sz(x) (int)x.size()
#define see(x) cerr << x << " "
#define seeln(x) cerr << x << endl
#define out(x) cerr << #x << " = " << x << " "
#define outln(x) cerr << #x << " = " << x << endl
#define outarr(x, l, r)                                                        \
  {                                                                            \
    cerr << #x "[" << l << " ~ " << r << "] = ";                               \
    for (int _i = l; _i <= r; ++_i)                                            \
      cerr << x[_i] << " ";                                                    \
    cerr << endl;                                                              \
  }
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
template<class T>
bool
checkmax(T& a, T b)
{
  return a < b ? a = b, 1 : 0;
}
template<class T>
bool
checkmin(T& a, T b)
{
  return b < a ? a = b, 1 : 0;
}
const int N = 25, mod = 998244353;
struct Z
{
  int x;
  Z(int x = 0)
    : x(x)
  {}
} C[N + 1][N + 1], ipw2[N + 1], inv[33];
typedef vector<Z> Poly;
Z
operator+(const Z a, const Z b)
{
  int o = a.x + b.x;
  return o >= mod ? o - mod : o;
}
Z
operator-(const Z a, const Z b)
{
  int o = a.x - b.x;
  return o < 0 ? o + mod : o;
}
Z
operator*(const Z a, const Z b)
{
  return (ll)a.x * b.x % mod;
}
Z&
operator+=(Z& a, const Z& b)
{
  return a = a + b;
}
Z&
operator-=(Z& a, const Z& b)
{
  return a = a - b;
}
Z&
operator*=(Z& a, const Z& b)
{
  return a = a * b;
}
Z
qpow(Z a, int b)
{
  Z ans = 1;
  while (b) {
    if (b & 1)
      ans = ans * a;
    a = a * a;
    b >>= 1;
  }
  return ans;
}
Z
operator/(const Z a, const Z b)
{
  return a * qpow(b, mod - 2);
}
Z&
operator/=(Z& a, const Z& b)
{
  return a = a / b;
}
ostream&
operator<<(ostream& out, Z& c)
{
  out << c.x;
  return out;
}

int n, m;
int adj[N];
char bit[1 << N];
bool mem[1 << N];
Poly g[N + 1];
map<int, Poly> f;
Poly
operator+(const Poly& a, const Poly& b)
{
  Poly c = a;
  if (sz(c) < sz(b))
    c.resize(sz(b));
  for (int i = 0; i < sz(b); ++i)
    c[i] += b[i];
  return c;
}

Poly
operator*(const Poly& a, const Poly& b)
{
  Poly c(sz(a) + sz(b) - 1);
  for (int i = 0; i < sz(a); ++i)
    for (int j = 0; j < sz(b); ++j)
      c[i + j] += a[i] * b[j];
  return c;
}

Poly
Integ(const Poly& a)
{
  Poly b(sz(a) + 1);
  for (int i = 0; i < sz(a); ++i)
    b[i + 1] = a[i] * inv[i + 1];
  return b;
}

Z
eval(const Poly& a, const Z& x)
{
  Z ans = 0;
  for (int i = sz(a) - 1; i >= 0; --i)
    ans = ans * x + a[i];
  return ans;
}

Poly
run(int S)
{
  if (f.count(S))
    return f[S];
  Poly ans;
  int msk = 0, vis[25] = { 0 };
  function<void(int)> dfs = [&](int u) {
    if (vis[u])
      return;
    msk |= (1 << u), vis[u] = 1;
    for (int i = 0; i < n; ++i)
      if ((adj[u] & S) >> i & 1)
        dfs(i);
  };
  vector<int> w;
  for (int i = 0; i < n; ++i)
    if (!vis[i] && (S >> i & 1))
      msk = 0, dfs(i), w.push_back(msk);
  if (sz(w) > 1) {
    ans = Poly(1, 1);
    for (int i = 0; i < sz(w); ++i)
      ans = ans * run(w[i]);
    return ans;
  } else {
    ans = Poly(1, ipw2[bit[S]]);
    for (int i = 0; i < n; ++i)
      if (S >> i & 1) {
        int T = S ^ (1 << i) ^ (S & adj[i]);
        int k = bit[S & adj[i]];
        Poly A = run(T);
        A = A * g[k];
        A = Integ(A);
        A[0] -= eval(A, inv[2]);
        ans = ans + A;
      }
  }
  // out(S); outarr(f[S], 0, sz(f[S]) - 1);
  return f[S] = ans;
}

void
init()
{
  scanf("%d%d", &n, &m);
  inv[1] = 1;
  for (int i = 2; i <= 30; ++i)
    inv[i] = inv[mod % i] * (mod - mod / i);
  ipw2[0] = 1;
  for (int i = 1; i <= N; ++i)
    ipw2[i] = ipw2[i - 1] * inv[2];
  for (int i = 0; i <= N; ++i) {
    C[i][0] = 1;
    for (int j = 1; j <= i; ++j)
      C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
  }
  for (int i = 0; i < (1 << n); ++i)
    bit[i] = bit[i >> 1] + (i & 1);
  for (int i = 0; i <= n; ++i) {
    g[i].resize(i + 1);
    for (int j = 0; j <= i; ++j)
      g[i][j] = (j & 1) ? mod - C[i][j] : C[i][j];
  }
  for (int i = 1, u, v; i <= m; ++i) {
    scanf("%d%d", &u, &v), --u, --v;
    adj[u] |= (1 << v), adj[v] |= (1 << u);
  }
}

void
solve()
{
  Poly F = run((1 << n) - 1);
  Z ans = 2;
  ans -= eval(F, 1) * inv[n + 1];
  Poly G = F;
  reverse(G.begin(), G.end());
  G = Integ(G);
  ans -= (eval(G, 2) - eval(G, 1));
  // outarr(F, 0, sz(F) - 1);
  printf("%d\n", ans.x);
}

int
main()
{
  init();
  solve();
  return 0;
}
