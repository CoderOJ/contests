#include "/home/jack/cm/debug"
#include "/home/jack/cm/intm"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <functional>
#include <set>
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);
FILE *                          out = stdout;

constexpr int MOD = 998244353;
constexpr int N   = 100005;
using int_t       = cm::intm<MOD>;

int n, m;

namespace brute
{
int                                    n, m;
std::vector<std::tuple<int, int, int>> es;

int_t ans = 0;

void dfs(std::vector<int> &&p, int eid, int chosen, int_t cur)
{
  std::function<int(int)> get = [&](int u) {
    return u == p[u] ? u : p[u] = get(p[u]);
  };

  if (eid == m)
  {
    ans += cur;
  }
  else
  {
    int u = std::get<0>(es[eid]);
    int v = std::get<1>(es[eid]);
    int w = std::get<2>(es[eid]);
    if (chosen + (m - eid - 1) >= n - 1)
    {
      auto cp = p;
      dfs(std::move(cp), eid + 1, chosen, cur * w);
    }
    if (get(u) != get(v))
    {
      p[get(u)] = get(v);
      dfs(std::move(p), eid + 1, chosen + 1, cur);
    }
    else
    {
      if (chosen + (m - eid - 1) >= n - 1)
      {
        dfs(std::move(p), eid + 1, chosen, cur);
      }
    }
  }
}

int_t main(std::vector<std::tuple<int, int, int>> &&_es)
{
  es = std::move(_es);
  m  = static_cast<int>(es.size());

  std::vector<int> us;
  for (const auto &e : es)
  {
    us.push_back(std::get<0>(e));
    us.push_back(std::get<1>(e));
  }
  std::sort(us.begin(), us.end());
  us.erase(std::unique(us.begin(), us.end()), us.end());
  n = static_cast<int>(us.size());
  for (auto &e : es)
  {
    std::get<0>(e) = static_cast<int>(
        std::lower_bound(us.begin(), us.end(), std::get<0>(e)) - us.begin());
    std::get<1>(e) = static_cast<int>(
        std::lower_bound(us.begin(), us.end(), std::get<1>(e)) - us.begin());
  }

  std::vector<int> p(n);
  for (int i = 0; i < n; i++)
    p[i] = i;
  dfs(std::move(p), 0, 0, 1);
  return ans;
}
} // namespace brute

std::multiset<std::pair<int, int>> e[N];
std::set<std::pair<int, int>>      d2u;
int                                deg[N];

int main()
{
  n = sc.next_int();
  m = n - 1 + sc.next_int();
  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    if (u == v)
      continue;
    e[u].emplace(v, 1);
    e[v].emplace(u, 1);
    deg[u]++;
    deg[v]++;
  }
  for (int i = 0; i < n; i++)
    d2u.emplace(deg[i], i);

  int_t ans = 1;

  while (!d2u.empty() && d2u.begin()->first < 3)
  {
    int d = d2u.begin()->first;
    int u = d2u.begin()->second;
    d2u.erase(d2u.begin());

    if (d == 0)
    {
      break;
    }
    else if (d == 1)
    {
      int v = e[u].begin()->first;
      int w = e[u].begin()->second;
      e[u].clear();
      e[v].erase({u, w});
      d2u.erase({deg[v], v});
      deg[v]--;
      d2u.insert({deg[v], v});
    }
    else
    {
      int v1 = e[u].begin()->first;
      int w1 = e[u].begin()->second;
      int v2 = e[u].rbegin()->first;
      int w2 = e[u].rbegin()->second;
      if (v1 != v2)
      {
        e[u].clear();
        e[v1].erase(e[v1].find({u, w1}));
        e[v2].erase(e[v2].find({u, w2}));
        e[v1].insert({v2, w1 + w2});
        e[v2].insert({v1, w1 + w2});
      }
      else
      {
        int v = v1;
        e[u].clear();
        e[v].erase(e[v1].find({u, w1}));
        e[v].erase(e[v1].find({u, w2}));
        d2u.erase({deg[v], v});
        deg[v] -= 2;
        d2u.insert({deg[v], v});
        ans *= (w1 + w2 + 1);
      }
    }
  }

  std::vector<std::tuple<int, int, int>> es;
  for (int i = 0; i < n; i++)
    for (const auto &e : e[i])
      if (e.first < i)
        es.emplace_back(e.first, i, e.second);
  see(es.size());
  see(es);

  // fprintf(out, "%d\n", static_cast<int>(ans));
  fprintf(out, "%d\n", static_cast<int>(ans * brute::main(std::move(es))));

  return 0;
}

