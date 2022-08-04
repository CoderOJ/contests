#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
// #include "/home/jack/cm/math_util.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <algorithm>
#include <cstdint>
#include <limits>
#include <utility>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    int n = sc.next_int();
    int k = sc.next_int();

    std::vector<std::pair<int, int>> ps;
    for (int i = 0; i < n; i++)
    {
      int x = sc.next_int();
      int y = sc.next_int();
      ps.emplace_back(x, y);
    }

    auto dis = [&](int x, int y) {
      int dx = ps[x].first - ps[y].first;
      int dy = ps[x].second - ps[y].second;
      return (int64_t)dx * dx + (int64_t)dy * dy;
    };

    std::vector<int>     keys{0};
    std::vector<int64_t> mdis(n);
    for (int i = 0; i < n; i++)
      mdis[i] = dis(0, i);
    while ((int)keys.size() < k)
    {
      int vkey
          = (int)(std::max_element(mdis.begin(), mdis.end()) - mdis.begin());
      keys.push_back(vkey);

      for (int i = 0; i < n; i++)
        cm::check_min(mdis[i], dis(vkey, i));
    }

    std::vector<int> col;
    for (int i = 0; i < n; i++)
    {
      int64_t cmin_v = std::numeric_limits<int64_t>::max();
      int     cmin_i = -1;
      for (int ki = 0; ki < k; ki++)
        if (cm::check_min(cmin_v, dis(i, keys[ki])))
          cmin_i = ki;
      col.push_back(cmin_i);
    }

    for (int i = 0; i < n; i++)
      printf("%d ", col[i] + 1);
    puts("");
  }
  return 0;
}
