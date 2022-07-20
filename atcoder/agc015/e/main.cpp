#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
#include "/home/jack/cm/intm.hpp"
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

  auto ps = [&] {
    struct info_t
    {
      int x;
      int v;
    };

    std::vector<info_t> a(n);
    for (int i = 0; i < n; i++)
    {
      a[i].x = sc.next_int();
      a[i].v = sc.next_int();
    }

    std::sort(a.begin(), a.end(), [&](auto x, auto y) {
      return x.v < y.v;
    });

    return a;
  }();

  auto inters = [&] {
    std::vector<std::pair<int, int>> a(n);

    std::vector<int> pre;
    for (int i = 0; i < n; i++)
    {
      if (pre.empty() || ps[pre.back()].x < ps[i].x)
        pre.push_back(i);
      a[i].first
          = *std::lower_bound(pre.begin(), pre.end(), i, [&](int a, int b) {
              return ps[a].x < ps[b].x;
            });
    }

    std::vector<int> suf;
    for (int i = n - 1; i >= 0; i--)
    {
      if (suf.empty() || ps[suf.back()].x > ps[i].x)
        suf.push_back(i);
      a[i].second = *std::lower_bound(
                        suf.begin(),
                        suf.end(),
                        i,
                        [&](int a, int b) {
                          return ps[a].x > ps[b].x;
                        })
                  + 1;
    }

    return a;
  }();

  see(inters);

  constexpr int MOD = 1'000'000'007;
  using int_t       = cm::intm<MOD>;

  auto ans = [&] {
    std::vector<int_t> a(n + 1);
    std::vector<int_t> pa(n + 2);

    a[0]  = 1;
    pa[0] = 0;
    pa[1] = a[0];

    std::sort(inters.begin(), inters.end(), [&](auto a, auto b) {
      return a.second != b.second ? a.second < b.second : a.first < b.first;
    });
    auto it = inters.begin();
    for (int i = 1; i <= n; i++)
    {
      a[i]      = 0;
      pa[i + 1] = pa[i] + a[i];
      while (it != inters.end() && it->second == i)
      {
        a[i] += pa[it->second + 1] - pa[it->first];
        pa[i + 1] = pa[i] + a[i];
        // see(*it, a, pa);
        it++;
      }
    }

    return a[n];
  }();

  std::cout << ans << std::endl;

  return 0;
}
