#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
// #include "/home/jack/cm/math_util.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <map>
#include <set>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();

  auto read_list = [&] {
    std::vector<int> a(n + 1);

    uint32_t xor_sum = 0;
    for (int i = 0; i < n; i++)
    {
      a[i] = sc.next_int();
      xor_sum ^= a[i];
    }
    a[n] = xor_sum;

    return a;
  };

  auto la = read_list();
  auto lb = read_list();

  auto is_eqaul = [&](auto a, auto b) {
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    return a == b;
  };

  if (!is_eqaul(la, lb))
  {
    puts("-1");
  }
  else
  {
    auto e = [&] {
      std::map<uint32_t, std::vector<uint32_t>> a;
      for (int i = 0; i <= n; i++)
        if (la[i] != lb[i])
        {
          a[la[i]].push_back(lb[i]);
          a[lb[i]].push_back(la[i]);
        }
      return a;
    }();

    auto comp_cnt = [&] {
      std::set<uint32_t> vis;

      int a = 0;
      for (int i = 0; i <= n; i++)
        if (la[i] != lb[i] || i == n)
          if (!vis.count(la[i]))
          {
            a += 1;
            cm::y_combinate([&](auto &&self, int u) -> void {
              vis.insert(u);
              for (auto v: e[u])
                if (!vis.count(v))
                  self(v);
            })(la[i]);
          }

      return a;
    }();

    auto diff_cnt = [&] {
      int a = 0;
      for (int i = 0; i < n; i++)
        if (la[i] != lb[i])
          a += 1;
      return a;
    }();

    std::cout << diff_cnt + comp_cnt - 1 << std::endl;
  }

  return 0;
}
