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
  int n = sc.next_int() - 1;

  auto vs = [&] {
    std::vector<int> a{sc.next_int()};
    while (a.back() > 0)
      a.push_back(a.back() / 2);
    return a;
  }();
  int m = static_cast<int>(vs.size());

  auto ps = [&] {
    int last = sc.next_int();

    std::vector<int> a;
    for (int i = 0; i < n; i++)
    {
      int cur = sc.next_int();
      a.push_back(cur - last);
      last = cur;
    }

    return a;
  }();

  auto get_prev = [n](const auto &v, int thr) {
    std::vector<int> a(n + 1);
    a[0] = 0;
    for (int i = 0; i < n; i++)
      a[i + 1] = (v[i] <= thr) ? a[i] : i + 1;
    return a;
  };
  auto get_next = [n](const auto &v, int thr) {
    std::vector<int> a(n + 1);
    a[n] = n;
    for (int i = n - 1; i >= 0; i--)
      a[i] = (v[i] <= thr) ? a[i + 1] : i;
    return a;
  };

  auto prevs = [&] {
    std::vector<std::vector<int>> a;
    a.reserve(vs.size());
    for (int thr: vs)
      a.emplace_back(get_prev(ps, thr));
    return a;
  }();
  auto nexts = [&] {
    std::vector<std::vector<int>> a;
    a.reserve(vs.size());
    for (int thr: vs)
      a.emplace_back(get_next(ps, thr));
    return a;
  }();
  // see(prevs);
  // see(nexts);

  auto front_reaches = [&] {
    std::vector<int> a(1 << m, -1);
    for (int i = 0; i < (1 << m); i++)
      for (int j = 0; j < m; j++)
        if (!(i & (1 << j)))
          cm::check_max(a[i | (1 << j)], nexts[j][std::min(n, a[i] + 1)]);
    return a;
  }();
  auto back_reaches = [&] {
    std::vector<int> a(1 << m, n + 1);
    for (int i = 0; i < (1 << m); i++)
      for (int j = 0; j < m; j++)
        if (!(i & (1 << j)))
          cm::check_min(a[i | (1 << j)], prevs[j][std::max(0, a[i] - 1)]);
    return a;
  }();
  // see(front_reaches);
  // see(back_reaches);

  auto ans = [&] {
    int top_cnt = [&] {
      int r = 0;
      for (int p = 0; p <= n; p = nexts[0][p] + 1)
        r += 1;
      return r;
    }();

    if (top_cnt > (int)vs.size())
      return std::vector<bool>(n + 1, false);
    else
    {
      std::vector<bool> ans(n + 1);
      for (int p = 0; p <= n; p = nexts[0][p] + 1)
      {
        int  pl = p - 1, pr = nexts[0][p] + 1;
        bool cur = [&] {
          int fm = (1 << m) - 2;
          for (int i = 0; i < (1 << m); i += 2)
            if (front_reaches[i] >= pl && back_reaches[fm ^ i] <= pr)
              return true;
          return false;
        }();
        for (int i = p; i <= nexts[0][p]; i++)
          ans[i] = cur;
      }
      return ans;
    }
  }();

  for (bool a: ans)
    puts(a ? "Possible" : "Impossible");

  return 0;
}
