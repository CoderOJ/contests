#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
// #include "/home/jack/cm/math_util.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();

  std::vector<std::vector<int>> e(n);
  for (int i = 0; i < n - 1; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    e[u].push_back(v);
    e[v].push_back(u);
  }

  auto sg = cm::y_combinate([&](auto &&self, int u, int f) -> int {
    int a = 0;
    for (int v: e[u])
      if (v != f)
        a ^= self(v, u) + 1;
    return a;
  })(0, 0);

  puts(sg == 0 ? "Bob" : "Alice");

  return 0;
}
