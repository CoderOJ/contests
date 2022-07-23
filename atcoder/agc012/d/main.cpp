#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
#include "/home/jack/cm/intm.hpp"
#include "/home/jack/cm/math_util.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <limits>
#include <numeric>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  int x = sc.next_int();
  int y = sc.next_int();

  auto bs = [&] {
    struct info_t
    {
      int  c, w;
      bool marked = false;
    };

    std::vector<info_t> a(n);
    for (int i = 0; i < n; i++)
    {
      a[i].c = sc.next_int() - 1;
      a[i].w = sc.next_int();
    }

    return a;
  }();

  auto mark_min = [](auto &&f) {
    return [&f](auto v) {
      int gmin_id = (int)std::distance(
          v.begin(), std::min_element(v.begin(), v.end(), f));
      v[gmin_id].marked = true;
      return v;
    };
  };

  auto get_cmin = [n](const auto &v) {
    std::vector<int> a(n, std::numeric_limits<int>::max() / 2);
    for (const auto c: v)
      if (c.marked)
        cm::check_min(a[c.c], c.w);
    return a;
  };

  auto get_dmin_getter = [](const auto &v) {
    struct dmin_getter_t
    {
      int min0 = std::numeric_limits<int>::max() / 2, id0 = -1;
      int min1 = std::numeric_limits<int>::max() / 2, id1 = -1;

      void check_min(int v, int i)
      {
        if (v <= min0)
        {
          min1 = min0, id1 = id0;
          min0 = v, id0 = i;
        }
        else if (v <= min1)
        {
          min1 = v, id1 = i;
        }
      }

      int get_min(int i)
      {
        return i != id0 ? min0 : min1;
      }
    };

    dmin_getter_t a;
    for (int i = 0; i < (int)v.size(); i++)
      a.check_min(v[i], i);
    return a;
  };

  auto spread_sc = [&](int thr) {
    return [&, thr](auto &&v) {
      auto cm = get_cmin(v);
      for (auto &c: v)
        if (c.w + cm[c.c] <= thr)
          c.marked = true;
      return v;
    };
  };

  auto spread_dc = [&](int thr) {
    return [&, thr](auto &&v) {
      auto cm = get_dmin_getter(get_cmin(v));
      for (auto &c: v)
        if (c.w + cm.get_min(c.c) <= thr)
          c.marked = true;
      return v;
    };
  };

  auto collect = [n](const auto &v) {
    std::vector<int> a(n);
    for (const auto &c: v)
      if (c.marked)
        a[c.c] += 1;
    return a;
  };

  auto multi_binom = [](const std::vector<int> &v) {
    constexpr int MOD = 1'000'000'007;
    using int_t       = cm::intm<MOD>;
    using mu          = cm::math_util<int_t>;

    int   sum = std::accumulate(v.begin(), v.end(), 0);
    int_t ans = mu::fac.get(sum);
    for (int c: v)
      ans *= mu::ifac.get(c);
    return ans;
  };

  auto ans = cm::transfer(
      bs,

      mark_min([](auto x, auto y) {
        return x.w < y.w;
      }),
      spread_dc(y),
      spread_sc(x),
      spread_dc(y),
      collect,
      multi_binom

  );

  std::cout << ans << std::endl;

  return 0;
}
