#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <cstdint>
#include <iostream>
#include <queue>
#include <set>
#include <tuple>
#include <utility>
#include <vector>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

CONSTRAINT(N, 100005, 105)

int n, m;

int p[N];
int get(int u)
{
  if (p[u] == u)
    return u;
  else
    return p[u] = get(p[u]);
}

std::set<int>                 e_in[N];
std::set<std::pair<int, int>> e_out[N];

int     cnt[N];
int64_t d_sum = 0;

void add_edge(int u, int v)
{
  int pu = get(u);
  int pv = get(v);
  if (pu == pv || e_in[pv].count(u))
    return;

  auto rev_it = e_out[pv].lower_bound({pu, 0});
  if (rev_it == e_out[pv].end() || rev_it->first != pu)
  {
    d_sum += cnt[pv];
    e_in[pv].insert(u);
    e_out[pu].emplace(pv, u);
  }
  else
  {
    if (e_in[pu].size() + e_out[pu].size() < e_in[pv].size() + e_out[pv].size())
    {
      std::swap(u, v);
      std::swap(pu, pv);
    }

    std::vector<std::pair<int, int>> de;

    for (int d : e_in[pv])
    {
      int pd = get(d);
      e_out[pd].erase({pv, d});
      d_sum -= cnt[pv];
      if (pd != pu)
        de.emplace_back(d, pu);
    }
    e_in[pv].clear();

    for (const auto &[d, ov] : e_out[pv])
    {
      e_in[d].erase(ov);
      d_sum -= cnt[d];
      if (d != pu)
        de.emplace_back(ov, d);
    }
    e_out[pv].clear();

    d_sum += 2 * static_cast<int64_t>(cnt[pu]) * cnt[pv];
    d_sum += static_cast<int64_t>(e_in[pu].size()) * cnt[pv];
    cnt[pu] = cnt[pu] + cnt[pv];
    p[pv]   = pu;

    for (auto &p : de)
      std::apply(add_edge, p);
  }
}

int main()
{
  n = sc.next_int();
  m = sc.next_int();

  for (int i = 1; i <= n; i++)
  {
    p[i]   = i;
    cnt[i] = 1;
  }

  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int();
    int v = sc.next_int();
    add_edge(u, v);
    std::cout << d_sum << std::endl;
  }

  return 0;
}
