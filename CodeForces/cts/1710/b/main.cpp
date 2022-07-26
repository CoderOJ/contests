#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
// #include "/home/jack/cm/math_util.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <algorithm>
#include <cstdio>
#include <iterator>
#include <limits>
#include <numeric>
#include <set>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  using int64_t = long long;

  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    int     n = sc.next_int();
    int64_t m = sc.next_int();

    std::vector<int>                     ps;
    std::vector<std::pair<int, int64_t>> rains;

    for (int i = 0; i < n; i++)
    {
      int     p = sc.next_int();
      int64_t v = sc.next_int();
      ps.emplace_back(p);
      rains.emplace_back(p, v);
    }

    std::sort(ps.begin(), ps.end());
    ps.erase(std::unique(ps.begin(), ps.end()), ps.end());

    int pn = (int)ps.size();

    std::vector<std::vector<int64_t>> p_rains(pn);

    for (int i = 0; i < n; i++)
    {
      int xp
          = (int)(std::lower_bound(ps.begin(), ps.end(), rains[i].first) - ps.begin());
      p_rains[xp].push_back(rains[i].second);
    }

    std::vector<int64_t> act(pn);
    for (int i = 0; i < pn; i++)
      act[i] = std::accumulate(p_rains[i].begin(), p_rains[i].end(), 0ll);

    {
      std::multiset<int64_t> c_rem;

      int64_t c_sum   = 0;
      int     c_cnt   = 0;
      int     c_lastp = 0;

      for (int i = 0; i < pn; i++)
      {
        while (!c_rem.empty() && *c_rem.begin() <= ps[i])
        {
          c_sum -= *c_rem.begin() - c_lastp;
          c_cnt -= 1;
          c_rem.erase(c_rem.begin());
        }

        c_sum -= 1ll * (ps[i] - c_lastp) * c_cnt;
        c_lastp = ps[i];

        act[i] += c_sum;

        for (int64_t r: p_rains[i])
        {
          c_sum += r;
          c_cnt += 1;
          c_rem.emplace(ps[i] + r);
        }
      }
    }

    {
      std::multiset<int64_t> c_rem;

      int64_t c_sum   = 0;
      int     c_cnt   = 0;
      int     c_lastp = 0;

      for (int i = pn - 1; i >= 0; i--)
      {
        while (!c_rem.empty() && *c_rem.rbegin() >= ps[i])
        {
          c_sum -= c_lastp - *c_rem.rbegin();
          c_cnt -= 1;
          c_rem.erase(std::prev(c_rem.end()));
        }

        c_sum -= 1ll * (c_lastp - ps[i]) * c_cnt;
        c_lastp = ps[i];

        act[i] += c_sum;

        for (int64_t r: p_rains[i])
        {
          c_sum += r;
          c_cnt += 1;
          c_rem.emplace(ps[i] - r);
        }
      }
    }
    // see(act);

    for (int i = 0; i < pn; i++)
      act[i] -= m;

    std::vector<int64_t> min_sub(pn, 0);

    {
      int64_t max_asp = std::numeric_limits<int64_t>::min() / 2;
      for (int i = 0; i < pn; i++)
      {
        if (act[i] > 0)
          cm::check_max(max_asp, act[i] - ps[i]);
        cm::check_max(min_sub[i], max_asp + ps[i]);
      }
    }
    {
      int64_t max_aap = std::numeric_limits<int64_t>::min() / 2;
      for (int i = pn - 1; i >= 0; i--)
      {
        if (act[i] > 0)
          cm::check_max(max_aap, act[i] + ps[i]);
        cm::check_max(min_sub[i], max_aap - ps[i]);
      }
    }

    for (int i = 0; i < n; i++)
    {
      int xp
          = (int)(std::lower_bound(ps.begin(), ps.end(), rains[i].first) - ps.begin());
      putchar(rains[i].second >= min_sub[xp] ? '1' : '0');
    }
    puts("");
  }
  return 0;
}
