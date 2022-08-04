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
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    int n = sc.next_int();

    std::vector<int> as(n);
    for (int i = 0; i < n; i++)
      as[i] = sc.next_int();

    int m = *std::max_element(as.begin(), as.end()) + 1;

    auto [first_hop, next_hop] = [&] {
      std::vector<int> last(m, n);

      std::vector<std::vector<int>> a(n);
      for (int i = n - 1; i >= 0; i--)
      {
        a[i] = {last.begin(), last.begin() + as[i]};
        std::fill(last.begin(), last.begin() + as[i], i);
      }

      return std::make_pair(std::move(last), std::move(a));
    }();

    auto pre2_sum = [&] {
      std::vector<int> a(n + 2);

      a[n + 1] = 0;
      a[n]     = 0;
      for (int i = n - 1; i >= 0; i--)
        a[i] = as[i] + a[i + 2];

      return a;
    }();

    for (int thr = 1; thr < m; thr++)
    {
      int cb = 0;
      int cs = 0;

      auto trans_below = [&](int l, int r) {
        int il = l + cb;
        int ir = (r % 2 == il % 2) ? r : r + 1;
        cs += pre2_sum[il] - pre2_sum[ir];
        cb = ir - r;
      };

      auto trans_above = cm::y_combinate([&](auto &&self, int v) -> void {
        if (cb == 1)
        {
          cb = 0;
          self(v - thr);
        }
        else
        {
          int vq = (v - 1) / thr;
          cs += ((vq + 1) / 2) * thr;
          if (vq % 2 == 0)
          {
            cs += (v - 1) % thr + 1;
            cb = 1;
          }
          else
          {
            cb = 0;
          }
        }
      });

      int p = first_hop[thr];
      trans_below(0, p);
      for (; p != n; p = next_hop[p][thr])
      {
        // see(p);
        trans_above(as[p]);
        trans_below(p + 1, next_hop[p][thr]);
      }

      printf("%d\n", cs);
    }
  }
  return 0;
}
