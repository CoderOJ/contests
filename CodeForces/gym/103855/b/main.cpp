#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
// #include "/home/jack/cm/math_util.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <cstdint>
#include <random>
#include <sys/types.h>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

const int N = 400005;

int      n, x[N], y[N], st[N], top;
uint64_t d[N];

std::vector<std::pair<int, int>> res;

int p_next(int x)
{
  return x % (2 * n) + 1;
}

void add_edge(int u, int v)
{
  if (p_next(u) != v && p_next(v) != u && u != v)
    res.emplace_back(u, v);
}

int main()
{
  std::mt19937_64 rng(18100301);

  n = sc.next_int();
  for (int i = 1; i <= n; ++i)
  {
    x[i]    = sc.next_int();
    y[i]    = sc.next_int();
    d[x[i]] = d[y[i]] = rng();
  }

  uint64_t                cur = 0;
  std::map<uint64_t, int> mp;
  mp[0] = 0;

  int ans = n * 2;
  for (int i = 1; i <= n * 2; ++i)
  {
    cur ^= d[i];
    auto it = mp.find(cur);
    if (it != mp.end())
    {
      int j = it->second;
      ans -= 1;

      while (st[top] > j)
        add_edge(i, st[top--]);

      mp.erase(it);
      st[++top] = j + 1;
    }
    st[++top] = i;
    mp[cur]   = i;
  }

  for (int i = 3; i <= top; ++i)
    add_edge(1, st[i]);
  printf("%d\n", ans);
  for (const auto &it: res)
    printf("%d %d\n", it.first, it.second);

  return 0;
}
