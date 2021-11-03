#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <cstdio>
#include <functional>
#include <tuple>
#include <vector>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  int m = sc.next_int();
  std::vector<std::tuple<int, int, int>> es;
  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    int w = sc.next_int();
    es.emplace_back(w, u, v);
  }

  std::vector<int> p(n);
  for (int i = 0; i < n; i++)
    p[i] = i;
  std::function<int(int)> get = [&](int u) {
    return u == p[u] ? u : p[u] = get(p[u]);
  };

  int cnt = 0;
  long long ans = 0;
  std::sort(es.begin(), es.end());
  for (const auto &[w, u, v] : es)
    if (get(u) != get(v))
    {
      p[get(u)] = get(v);
      ans += w;
      cnt++;
    }

  if (cnt < n - 1)
    std::puts("IMPOSSIBLE");
  else
    std::cout << ans << std::endl;

  return 0;
}
