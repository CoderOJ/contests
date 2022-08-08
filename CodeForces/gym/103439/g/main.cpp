#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
// #include "/home/jack/cm/math_util.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <algorithm>
#include <limits>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  int m = sc.next_int();

  std::vector<int> as(n);
  for (int i = 0; i < n; i++)
    as[i] = sc.next_int();
  as.insert(as.begin(), -1);
  as.insert(as.end(), std::numeric_limits<int>::max() / 2);
  n = (int)as.size();

  std::vector<int> bs(m);
  for (int i = 0; i < m; i++)
    bs[i] = sc.next_int();
  std::sort(bs.begin(), bs.end());

  std::vector<int> aw(n);
  for (int i = 0; i < n; i++)
  {
    int bc = (int)(std::lower_bound(bs.begin(), bs.end(), as[i]) - bs.begin());
    aw[i]  = bc + n - i;
  }

  int NINF = std::numeric_limits<int>::min() / 2;

  int              pmax_n = n + m + 5;
  std::vector<int> pmax(pmax_n, NINF);
  std::vector<int> pvis_pos;

  auto pmax_clear = [&] {
    for (int x: pvis_pos)
      pmax[x] = NINF;
    pvis_pos.clear();
  };

  auto pmax_mark = [&](int x) {
    if (pmax[x] == NINF)
      pvis_pos.push_back(x);
  };

  auto pre_update = [&](int p, int v) {
    p += 1;
    for (; p < pmax_n; p += p & -p)
    {
      pmax_mark(p);
      cm::check_max(pmax[p], v);
    }
  };

  auto pre_query = [&](int p) {
    p += 1;
    int v = std::numeric_limits<int>::min();
    for (; p > 0; p -= p & -p)
      cm::check_max(v, pmax[p]);
    return v;
  };

  std::vector<int> dp(n, NINF);
  dp[0] = 1;

  cm::y_combinate([&](auto &&self, int l, int r) -> void {
    if (r - l >= 2)
    {
      int m = l + (r - l) / 2;
      self(l, m);

      std::vector<int> ids(r - l);
      std::iota(ids.begin(), ids.end(), l);
      std::sort(ids.begin(), ids.end(), [&](int x, int y) {
        return as[x] < as[y];
      });

      pmax_clear();
      for (int i: ids)
      {
        if (i < m)
          pre_update(aw[i], dp[i]);
        else
          dp[i] = std::max(dp[i], pre_query(aw[i] + 1) + 1);
      }

      self(m, r);
    }
  })(0, n);

  int ans = dp[n - 1] < 0 ? -1 : n - dp[n - 1];
  std::cout << ans << std::endl;

  return 0;
}
