#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/base.h"

#include "/home/jack/code/creats/body.h"

#include <bits/stdc++.h>

constexpr int mod = 1000000000 + 7;
int Add(int a, int b) { a += b; return a >= mod ? a - mod : a; }
int Sub(int a, int b) { a -= b; return a < 0 ? a + mod : a; }
int Mul(int a, int b) { return (long long)a * b % mod; }
void add(int& a, int b) { a += b; (a >= mod) && (a -= mod); }
void sub(int& a, int b) { a -= b; (a < 0) && (a += mod); }
void mul(int& a, int b) { a = (long long)a * b % mod; }
int qpow(int a, int b) { int ans = 1; while (b) { if (b & 1) ans = (long long)ans * a % mod; a = (long long)a * a % mod; b >>= 1; } return ans; }

constexpr int N = 200005, mod1 = 1019260817 , mod2 = 19260817, Base = 233;
int n, m;
int gcd(int a, int b) { return b ? gcd(b, a % b) : a; }

std::vector<int> G[N];
int fa[N], dfn[N], dep[N], dfs_clock = 0;
int cycle[N], on_cyc[N], cyc_num = 0;
std::pair<int,int> Pow[N], str[N], H[N];
int sta[N], M[N];
std::pair<int,int>
operator*(std::pair<int,int> a, int b)
{
  return std::make_pair(a.first * b % mod, a.second * b % mod);
}
std::pair<int,int>
operator<<(std::pair<int,int> a, int b)
{
  return std::make_pair((long long)a.first * Pow[b].first % mod1,
                        (long long)a.second * Pow[b].second % mod2);
}
std::pair<int,int>
operator+(std::pair<int,int> a, int b)
{
  return std::make_pair((a.first + b) % mod1, (a.second + b) % mod2);
}
std::pair<int,int>
operator+(std::pair<int,int> a, std::pair<int,int> b)
{
  return std::make_pair((a.first + b.first) % mod1,
                        (a.second + b.second) % mod2);
}
int csp[N], dp[N], inv[N], f[N], siz[N];
void add_edge(int x, int y) { G[x].push_back(y); }

bool cmp(int x, int y) { return dep[x] == dep[y] ? H[x] < H[y] : dep[x] < dep[y]; }

void
dfs(int x, int f)
{
  dep[x] = dep[f] + 1;
  siz[x] = 1;
  for (int i = 0; i < static_cast<int>(G[x].size()); ++i) {
    int to = G[x][i]; if (on_cyc[to]) continue;
    dfs(to, x); siz[x] += siz[to]; }
  sort(G[x].begin(), G[x].end(), cmp);
  int tot = 0;
  H[x] = std::make_pair(dep[x], dep[x]);
  for (int i = 0; i < static_cast<int>(G[x].size()); ++i) {
    int to = G[x][i]; if (on_cyc[to]) continue;
    H[x] = (H[x] << siz[to]) + H[to];
    sta[++tot] = to; }
  dp[x] = m;
  for (int i = 1, j; i <= tot;) {
    j = i;
    while (j < tot && H[sta[j + 1]] == H[sta[i]]) ++j;
    int cnt = j - i + 1, num = dp[sta[i]];
    for (int i = 0; i < cnt; ++i) mul(dp[x], Add(num, i));
    for (int i = 1; i <= cnt; ++i) mul(dp[x], inv[i]);
    i = j + 1; } }

int
get_rep()
{
  for (int i = 0; i < cyc_num; ++i) str[i] = H[cycle[i + 1]];
  int i = 1, j = 0;
  for (; i < cyc_num; ++i) {
    while (j && str[i] != str[j]) j = csp[j - 1];
    if (str[i] == str[j]) ++j, csp[i] = j; }
  int len = cyc_num - csp[cyc_num - 1];
  if (csp[cyc_num - 1] == cyc_num) return cyc_num;
  if (cyc_num % len == 0) return len;
  else return cyc_num;
}

int
Burnside(int n, int m)
{
  M[0] = 1;
  for (int i = 1; i <= n; ++i) M[i] = Mul(M[i - 1], m);
  int ans = 0;
  for (int k = 0; k < n; ++k) { int d = gcd(n, k); add(ans, M[d]); }
  return Mul(ans, inv[n]);
}

void
preInit()
{}

void
init()
{
  n = sc.nl(); m = sc.nl();
  Pow[0] = std::make_pair(1, 1);
  for (int i = 1; i <= n; ++i)
    Pow[i] = Pow[i - 1] * Base;
  inv[0] = inv[1] = 1;
  for (int i = 2; i <= n; ++i)
    inv[i] = Mul(inv[mod % i], mod - mod / i);
  for (int i = 1; i <= n; ++i) { add_edge(f[i] = sc.nl(), i); }
  int now = 1;
  for (int i = 1; i <= n; ++i)
    now = f[now];
  int tmp = now;
  while (true) {
    on_cyc[tmp] = 1;
    cycle[++cyc_num] = tmp;
    tmp = f[tmp];
    if (tmp == now) break; }
}

void
solve()
{
  for (int i = 1; i <= cyc_num; ++i)
    dfs(cycle[i], 0);
  int len = get_rep(), total = 1;
  for (int i = 1; i <= len; ++i)
    mul(total, dp[cycle[i]]);
  int ans = Burnside(cyc_num / len, total);
  printf("%d\n", ans);
}
