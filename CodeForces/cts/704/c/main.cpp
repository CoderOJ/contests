#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <cstring>
#include <utility>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int MOD = 1'000'000'007;

int iaddmodl(int x, int y)
{
  return x + y >= MOD ? x + y - MOD : x + y;
}

constexpr int N = 100'005;

struct edge_t
{
  int v;
  int p, q;
  int i;

  edge_t() = default;
  edge_t(int v, int p, int q, int i) : v(v), p(p), q(q), i(i) {}
};

int  n, m, ans[2], deg[N], sgn[N];
int  f[2][2][2], g[2][2][2];
bool vis[N];

std::vector<edge_t> e[N];

void update(int res0, int res1)
{
  int ans0 = ans[0], ans1 = ans[1];
  ans[0] = (1ll * ans0 * res0 + 1ll * ans1 * res1) % MOD;
  ans[1] = (1ll * ans0 * res1 + 1ll * ans1 * res0) % MOD;
}

void solve(int s)
{
  int res[2] = {0, 0};
  memset(f, 0, sizeof(f));
  for (int x = 0; x < 2; x++)
    f[sgn[s] == -1 || deg[s] == 1 ? 0 : sgn[s] ^ x][x][x] = 1;

  for (int u = s, v, w = -1;; u = v)
  {
    memcpy(g, f, sizeof(g));
    memset(f, 0, sizeof(f));
    vis[u]   = true;
    edge_t e = (edge_t){0, 0, 0, -1};
    for (auto i : ::e[u])
    {
      if (i.i != w)
      {
        e = i;
        break;
      }
    }

    v = e.v;
    w = e.i;

    if (w == -1)
    {
      for (int z = 0; z < 2; z++)
        for (int x0 = 0; x0 < 2; x0++)
          for (int y = 0; y < 2; y++)
          {
            int zz  = z ^ (sgn[u] == -1 ? 0 : sgn[u] ^ y);
            res[zz] = iaddmodl(res[zz], g[z][x0][y]);
          }
      break;
    }
    if (v == s)
    {
      for (int z = 0; z < 2; z++)
        for (int x0 = 0; x0 < 2; x0++)
          for (int y = 0; y < 2; y++)
          {
            int zz  = z ^ ((y ^ e.p) | (x0 ^ e.q));
            res[zz] = iaddmodl(res[zz], g[z][x0][y]);
          }
      break;
    }
    for (int z = 0; z < 2; z++)
      for (int x0 = 0; x0 < 2; x0++)
        for (int y = 0; y < 2; y++)
          for (int x = 0; x < 2; x++)
          {
            int zz       = z ^ ((y ^ e.p) | (x ^ e.q));
            f[zz][x0][x] = iaddmodl(f[zz][x0][x], g[z][x0][y]);
          }
  }
  update(res[0], res[1]);
}

std::pair<int, int> parse_var(int x)
{
  return std::make_pair(x < 0, std::abs(x));
}

int main()
{
  m = sc.next_int();
  n = sc.next_int();

  ans[0] = 1;
  for (int u = 1; u <= n; u++)
    sgn[u] = -1;

  for (int i = 0; i < m; i++)
  {
    int k = sc.next_int();
    if (k == 1)
    {
      const auto [p, u] = parse_var(sc.next_int());
      deg[u]++;
      if (sgn[u] == -1)
      {
        sgn[u] = p;
      }
      else
      {
        vis[u] = true;
        if (sgn[u] == p)
          update(2, 0);
        else
          update(0, 2);
      }
    }
    else
    {
      const auto [p, u] = parse_var(sc.next_int());
      const auto [q, v] = parse_var(sc.next_int());
      deg[u]++;
      deg[v]++;
      e[u].emplace_back(v, p, q, i);
      e[v].emplace_back(u, q, p, i);
    }
  }

  for (int u = 1; u <= n; u++)
    if (!vis[u] && (deg[u] == 1 || sgn[u] != -1))
      solve(u);

  for (int u = 1; u <= n; u++)
    if (!vis[u])
      solve(u);

  printf("%d\n", ans[1]);

  return 0;
}
