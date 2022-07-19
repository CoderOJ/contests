#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
// #include "/home/jack/cm/math_util.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <algorithm>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();

  auto es = [&] {
    int m = sc.next_int();

    std::vector<std ::pair<int, int>> es;
    for (int i = 0; i < m; i++)
    {
      int u = sc.next_int() - 1;
      int v = sc.next_int() - 1;
      es.emplace_back(u, v);
    }
    std::reverse(es.begin(), es.end());

    return es;
  }();

  using state_t = std::bitset<400>;

  std::vector<state_t> st(n);
  for (int u = 0; u < n; u++)
    st[u] = [&](int u) {
      state_t a;
      a.set(u);

      for (const auto &[u, v]: es)
      {
        bool tu = a.test(u), tv = a.test(v);
        if (tu && tv)
        {
          a.set();
          return a;
        }
        else if (tu || tv)
        {
          a.set(u);
          a.set(v);
        }
      }

      return a;
    }(u);

  int ans = 0;
  for (int u = 0; u < n; u++)
    for (int v = u + 1; v < n; v++)
      if ((st[u] & st[v]).none())
        ans += 1;

  std::cout << ans << std::endl;

  return 0;
}
