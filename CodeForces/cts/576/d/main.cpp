#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <queue>
#include <algorithm>
#include <bitset>

cm::scanner<cm::optimal_reader> sc(stdin);

#define long long long
constexpr int N = 150;
constexpr long inf = 1e18;
using vec_t = std::bitset<N>;

struct matrix_t
{
  vec_t a[N];

  vec_t operator* (const vec_t &rhs) const 
  {
    vec_t res;
    for (int i = 0; i < N; i++)
      res[i] = (a[i] & rhs).any();
    return res;
  }

  matrix_t operator* (const matrix_t &rhs) const 
  {
    matrix_t res;
    for (int i = 0; i < N; i++)
      for (int j = 0; j < N; j++)
        if (a[i][j])
          res.a[i] |= rhs.a[j];
    return res;
  }
};

vec_t pow(matrix_t a, long b, vec_t r)
{
  for (; b; b >>= 1)
  {
    if (b & 1)
      r = a * r;
    a = a * a;
  }
  return r;
}

struct edge_t
{
  int u, v, w;
  edge_t() =default;
  edge_t(int u, int v, int w) : u(u), v(v), w(w) {}
};

int main()
{
  int n = sc.next_int();
  int m = sc.next_int();
  std::vector<edge_t> e;
  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    int w = sc.next_int();
    e.emplace_back(u, v, w);
  }
  std::sort(e.begin(), e.end(), [](auto x, auto y) { return x.w < y.w; });

  vec_t vis;
  vis[0] = true;
  matrix_t trans;
  std::vector<long> dis(n, inf);
  long ans = inf, last_time = 0;

  for (const auto [u,v,w] : e)
  {
    if (w >= ans) break;
    vis = pow(trans, w - last_time, vis);
    trans.a[v][u] = true;
    last_time = w;

    std::queue<int> que;
    for (int u = 0; u < n; u++)
      if (vis[u]) que.push(u), dis[u] = 0;
      else dis[u] = inf;

    while (!que.empty())
    {
      int u = que.front(); que.pop();
      for (int v = 0; v < n; v++)
        if (trans.a[v][u] && check_min(dis[v], dis[u] + 1))
          que.push(v);
    }

    check_min(ans, last_time + dis[n - 1]);
  }

  if (ans == inf)
    puts("Impossible");
  else
    printf("%lld\n", ans);

  return 0;
}

