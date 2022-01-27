#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <set>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

const long double eps  = 1e-12L;
const long double eeps = 1e-7L;
const long double inf  = 1e18;

constexpr int N = 200005;
constexpr int V = 10'000'005;

long double _;

struct segment_t
{
  long double s, t, l, c;
  int         i;

  segment_t() = default;
  segment_t(long double s, long double t, long double l, long double c, int i) :
      s(s), t(t), l(l), c(c), i(i)
  {
  }
  segment_t(
      long double s, long double t, long double l, long double c, size_t i) :
      s(s), t(t), l(l), c(c), i(static_cast<int>(i))
  {
  }

  [[nodiscard]] long double r() const
  {
    return l + (_ - s) * c;
  }
};

bool operator<(const segment_t &i, const segment_t &j)
{
  return std::abs(i.r() - j.r()) < eps ? i.i < j.i : i.r() < j.r();
}

long double ans;

int n, m;
int ft[N], dep[N], size[N];
int hs[N], top[N], tms, dfn[N], opt[V];

std::vector<std::pair<long double, int>> b;

std::vector<int>       e[N];
std::vector<segment_t> a;
std::set<segment_t>    f;

void dfs1(int u, int fa)
{
  ft[u]   = fa;
  dep[u]  = dep[fa] + 1;
  size[u] = 1;
  for (auto v : e[u])
  {
    if (v == fa)
      continue;
    dfs1(v, u);
    size[u] += size[v];
    if (size[hs[u]] < size[v])
      hs[u] = v;
  }
}
void dfs2(int u, int tp)
{
  top[u] = tp;
  dfn[u] = ++tms;
  if (hs[u] > 0)
    dfs2(hs[u], tp);
  for (auto v : e[u])
  {
    if (v == ft[u] || v == hs[u])
      continue;
    tms++;
    dfs2(v, v);
  }
}

int find_lca(int u, int v)
{
  while (top[u] != top[v])
  {
    if (dep[top[u]] > dep[top[v]])
      u = ft[top[u]];
    else
      v = ft[top[v]];
  }
  return dep[u] < dep[v] ? u : v;
}

int distance(int u, int v)
{
  return dep[u] + dep[v] - dep[find_lca(u, v)] * 2;
}

void update(segment_t i, segment_t j)
{
  if (i.i == -1 || j.i == -1)
  {
    return;
  }
  long double d = j.r() - i.r();
  long double c = i.c - j.c;
  if (std::abs(c) < eps)
  {
    if (std::abs(d) < eps)
    {
      ans = std::min(ans, _);
    }
    return;
  }
  long double t = _ + d / c;
  if (t < i.s - eps || t < j.s - eps)
  {
    return;
  }
  if (t > i.t + eps || t > j.t + eps)
  {
    return;
  }
  ans = std::min(ans, t);
}

int main()
{
  n = sc.next_int();
  m = sc.next_int();
  for (int i = 1; i < n; i++)
  {
    int u = sc.next_int();
    int v = sc.next_int();
    e[u].push_back(v);
    e[v].push_back(u);
  }

  dfs1(1, 0);
  dfs2(1, 1);

  for (int i = 0; i < m; i++)
  {
    long double s = sc.next_int(), c = sc.next_int(), t, _s, _t;
    int         u = sc.next_int(), v = sc.next_int(), _u, _v;

    t = s + distance(u, v) / c;
    while (top[u] != top[v])
    {
      _u = ft[top[u]];
      _v = ft[top[v]];
      if (dep[_u] > dep[_v])
      {
        _s = s + (dep[u] - dep[_u]) / c;
        a.push_back((segment_t){s, _s, dfn[u] + 0.0L, -c, a.size()});
        u = _u;
        s = _s;
      }
      else
      {
        _t = t - (dep[v] - dep[_v]) / c;
        a.push_back((segment_t){_t, t, dfn[top[v]] - 1.0L, c, a.size()});
        v = _v;
        t = _t;
      }
    }
    if (dep[u] > dep[v])
      a.push_back((segment_t){s, t, dfn[u] + 0.0L, -c, a.size()});
    else
      a.push_back((segment_t){s, t, dfn[u] + 0.0L, c, a.size()});
  }

  ans = inf;
  f.insert((segment_t){0.0L, 0.0L, -inf, 0.0L, -1});
  f.insert((segment_t){0.0L, 0.0L, +inf, 0.0L, -1});
  for (int i = 0; i < (int)a.size(); i++)
  {
    a[i].t += eps * 9;
    b.emplace_back(a[i].s, i);
    b.emplace_back(a[i].t, i);
  }

  std::sort(b.begin(), b.end());
  for (auto p : b)
  {
    int i = p.second;
    _     = p.first;
    opt[i]++;
    if (_ > ans - eeps)
    {
      printf("%.6f\n", (double)ans);
      return 0;
    }
    if (opt[i] == 1)
    {
      auto it = f.insert(a[i]).first;
      auto l  = it;
      update(a[i], *(--l));
      auto r = it;
      update(a[i], *(++r));
    }
    else
    {
      auto r = f.erase(f.lower_bound(a[i]));
      auto l = r;
      update(*(--l), *r);
    }
  }

  if (ans > inf / 2)
  {
    puts("-1");
    return 0;
  }

  printf("%.6f\n", static_cast<double>(ans));

  return 0;
}
