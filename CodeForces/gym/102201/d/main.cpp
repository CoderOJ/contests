#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <algorithm>
#include <cstdint>
#include <limits>
#include <tuple>
#include <utility>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n  = sc.next_int();
  int sx = sc.next_int();
  int sy = sc.next_int();
  int tx = sc.next_int();
  int ty = sc.next_int();

  struct rec_t
  {
    int xl, xr;
    int yl, yr;

    std::vector<int64_t> c_but;
    std::vector<int64_t> c_top;
  };
  std::vector<rec_t> r(n);
  for (int i = 0; i < n; i++)
  {
    r[i].xl = sc.next_int();
    r[i].yl = sc.next_int();
    r[i].xr = sc.next_int();
    r[i].yr = sc.next_int();

    // puts("Polygon");
    // std::cout << r[i].xl << " " << r[i].yl << std::endl;
    // std::cout << r[i].xl << " " << r[i].yr << std::endl;
    // std::cout << r[i].xr << " " << r[i].yr << std::endl;
    // std::cout << r[i].xr << " " << r[i].yl << std::endl;
    // puts("...");
  }

  auto solve =
      [](int sx, int sy, int tx, int ty, std::vector<rec_t> r) -> int64_t {
    if (sx > tx)
    {
      std::swap(sx, tx);
      std::swap(sy, ty);
    }

    auto calc_c = [](int sx, int sy, std::vector<rec_t> &r) {
      using event_t = std::tuple<int, int, int, rec_t *>;
      std::vector<event_t> events;
      for (auto &p : r)
        if (sx <= p.xl)
          events.emplace_back(p.xl, p.yl, p.yr, &p);
      std::sort(events.begin(), events.end());

      std::map<int, int64_t> rays{{sy, 0}};
      for (const auto &[_, l, r, rp] : events)
      {
        auto it = rays.lower_bound(l);

        int64_t v_but = std::numeric_limits<int64_t>::max();
        int64_t v_top = std::numeric_limits<int64_t>::max();
        while (it != rays.end() && it->first <= r)
        {
          cm::check_min(v_but, it->second + (it->first - l));
          cm::check_min(v_top, it->second + (r - it->first));
          it = rays.erase(it);
        }

        if (v_but != std::numeric_limits<int64_t>::max())
        {
          rays.emplace(l, v_but);
          rp->c_but.push_back(v_but);
        }
        if (v_top != std::numeric_limits<int64_t>::max())
        {
          rays.emplace(r, v_top);
          rp->c_top.push_back(v_top);
        }
      }
    };

    calc_c(sx, sy, r);

    for (auto &p : r)
      std::tie(p.xl, p.xr) = std::make_pair(-p.xr, -p.xl);
    calc_c(-tx, ty, r);

    int64_t ans = std::numeric_limits<int64_t>::max();
    for (const auto &p : r)
    {
      if (p.c_but.size() == 2)
        cm::check_min(ans, (tx - sx) + p.c_but[0] + p.c_but[1]);
      if (p.c_top.size() == 2)
        cm::check_min(ans, (tx - sx) + p.c_top[0] + p.c_top[1]);
    }

    return ans;
  };

  int64_t ans0 = solve(sx, sy, tx, ty, r);

  std::swap(sx, sy);
  std::swap(tx, ty);
  for (auto &p : r)
  {
    std::swap(p.xl, p.yl);
    std::swap(p.xr, p.yr);
  }
  int64_t ans1 = solve(sx, sy, tx, ty, r);

  // see(ans0, ans1);

  int64_t ans = std::min(ans0, ans1);
  if (ans == std::numeric_limits<int64_t>::max())
    ans = std::abs(sx - tx) + std::abs(sy - ty);
  std::cout << ans << std::endl;

  return 0;
}
