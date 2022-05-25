#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <cinttypes>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

CONSTRAINT(N, 200005, 1005)

struct edge_t
{
  int v, w0, w1;
};

std::vector<edge_t> e[N];

int64_t ans[N];
int     n;

int64_t sum_r;
int64_t dup[N];
void    dfs0(int u, int f)
{
  for (const auto &[v, w0, w1] : e[u])
    if (v != f)
    {
      sum_r += w0;
      dup[v] = dup[u] + w1 - w0;
      dfs0(v, u);
    }
}

std::pair<int64_t, int> dfs1(int u, int f, std::pair<int64_t, int> &ans)
{
  std::pair<int64_t, int> cur{0, u};
  for (const auto &[v, w0, w1] : e[u])
    if (v != f)
    {
      auto vp = dfs1(v, u, ans);
      vp.first += w0;
      check_max(ans, {cur.first + vp.first - dup[u], cur.second});
      check_max(cur, vp);
    }
  return cur;
}

int64_t dfs2(int u, int f, std::vector<int64_t> &ans)
{
  std::vector<int64_t> vs{0};
  for (const auto &[v, w0, w1] : e[u])
    if (v != f)
      vs.push_back(dfs2(v, u, ans) + w0);
  std::sort(vs.begin(), vs.end());

  int64_t r = vs.back();
  vs.pop_back();
  ans.insert(ans.end(), vs.begin(), vs.end());

  return r;
}

int main()
{
  n = sc.next_int();
  for (int i = 0; i < n - 1; i++)
  {
    int u  = sc.next_int();
    int v  = sc.next_int();
    int w0 = sc.next_int();
    int w1 = sc.next_int();
    e[u].push_back({v, w0, w1});
    e[v].push_back({u, w1, w0});
  }

  dfs0(1, 0);
  ans[1] = [] {
    int64_t res = sum_r;
    for (int i = 1; i <= n; i++)
      check_min(res, sum_r + dup[i]);
    return res;
  }();

  int r = [] {
    std::pair<int64_t, int> rp{0, 0};
    dfs1(1, 0, rp);
    return rp.second;
  }();

  sum_r  = 0;
  dup[r] = 0;
  dfs0(r, 0);

  std::vector<int64_t> ds;

  int64_t ds0 = dfs2(r, 0, ds);
  std::sort(ds.begin(), ds.end());
  ans[2]      = sum_r - ds0;
  for (int i = 3; i <= n; i++)
  {
    ans[i] = ans[i - 1] - ds.back();
    ds.pop_back();
  }

  int q = sc.next_int();
  for (int i = 0; i < q; i++)
  {
    int k = sc.next_int();
    printf("%" SCNi64 "\n", ans[k]);
  }

  return 0;
}
