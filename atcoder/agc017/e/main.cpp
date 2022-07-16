#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
// #include "/home/jack/cm/math_util.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <algorithm>
#include <utility>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  int h = sc.next_int();

  auto id = [&](int x) {
    return x + h;
  };

  std::vector<std::vector<int>> e(h + h + 1);
  std::vector<int>              deg_in(h + h + 1);
  std::vector<int>              deg_out(h + h + 1);

  for (int i = 0; i < n; i++)
  {
    int lb = sc.next_int();
    int rb = sc.next_int();
    int la = sc.next_int();
    int ra = sc.next_int();

    int lu = la == 0 ? lb : -la;
    int ru = ra == 0 ? rb : -ra;
    int u  = id(lu);
    int v  = id(-ru);

    e[u].push_back(v);
    e[v].push_back(u);
    deg_out[u] += 1;
    deg_in[v] += 1;
  }

  auto us = [&] {
    std::vector<std::vector<int>> a;

    std::vector<bool> vis(h + h + 1, false);
    for (int u = 0; u <= h + h; u++)
      if (!vis[u])
      {
        std::vector<int> cur;
        cm::y_combinate([&](auto &&self, int u) -> void {
          vis[u] = true;
          cur.push_back(u);
          for (int v: e[u])
            if (!vis[v])
              self(v);
        })(u);
        a.emplace_back(std::move(cur));
      }

    return a;
  }();

  auto is_ok_io = [&] {
    for (int i = 0; i <= h; i++)
      if (deg_in[i] < deg_out[i])
        return false;
    for (int i = h; i <= h * 2; i++)
      if (deg_in[i] > deg_out[i])
        return false;
    return true;
  }();

  if (is_ok_io
      && std::all_of(us.begin(), us.end(), [&](const std::vector<int> &us) {
           if (std::all_of(us.begin(), us.end(), [&](int u) {
                 return e[u].empty();
               }))
             return true;
           else
             return std::any_of(us.begin(), us.end(), [&](int u) {
               return deg_in[u] != deg_out[u];
             });
         }))
    puts("YES");
  else
    puts("NO");

  return 0;
}
