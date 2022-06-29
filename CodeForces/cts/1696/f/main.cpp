#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <bitset>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    using mask_t = std::bitset<128>;

    int n = sc.next_int();

    std::vector<std::vector<mask_t>> a(n, std::vector<mask_t>(n));
    for (int i = 0; i < n; i++)
      for (int j = i + 1; j < n; j++)
      {
        mask_t cur;
        for (int k = 0; k < n; k++)
        {
          char c = sc.next_char();
          if (c == '1')
            cur.set(k);
        }
        a[i][j] = cur;
        a[j][i] = cur;
      }

    auto get_mask = [&](const std::vector<int> &f) {
      std::vector<std::vector<int>> dis(
          n, std::vector<int>(n, std::numeric_limits<int>::max() / 2));
      for (int u = 0; u < n; u++)
      {
        dis[u][u] = 0;
        if (f[u] != -1)
        {
          dis[u][f[u]] = 1;
          dis[f[u]][u] = 1;
        }
      }
      for (int r = 0; r < n; r++)
        for (int u = 0; u < n; u++)
          for (int v = 0; v < n; v++)
            cm::check_min(dis[u][v], dis[u][r] + dis[r][v]);

      std::vector<std::vector<mask_t>> res(n, std::vector<mask_t>(n));
      for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
        {
          mask_t cur;
          for (int k = 0; k < n; k++)
            if (dis[i][k] == dis[j][k])
              cur.set(k);
          res[i][j] = cur;
          res[j][i] = cur;
        }

      return res;
    };

    auto valid_tree = [&](const std::vector<int> &f) {
      return std::count(f.begin(), f.end(), -1) == 1 && get_mask(f) == a;
    };

    auto get_tree = [&](int r, int u) {
      std::vector<bool> vis(n, false);
      vis[r] = true;
      vis[u] = true;

      std::vector<int> f(n);
      f[r] = -1;
      f[u] = r;

      std::queue<int> que;
      que.emplace(u);

      for (int up = 0; up < n; up++)
        if (!vis[up] && a[u][up].test(r))
        {
          f[up]   = r;
          vis[up] = true;
          que.emplace(up);
        }

      while (!que.empty())
      {
        int u = que.front();
        que.pop();
        for (int us = 0; us < n; us++)
          if (!vis[us] && a[f[u]][us].test(u))
          {
            f[us]   = u;
            vis[us] = true;
            que.emplace(us);
          }
      }

      return f;
    };

    std::vector<int> ans;
    for (int u = 1; u < n; u++)
    {
      auto cur = get_tree(0, u);
      // see(0, u);
      // see(cur);
      // see(get_mask(cur));
      if (valid_tree(cur))
      {
        ans = cur;
        break;
      }
    }

    if (ans.empty())
    {
      puts("No");
    }
    else
    {
      puts("Yes");
      for (int u = 0; u < n; u++)
        if (ans[u] != -1)
          std::cout << ans[u] + 1 << ' ' << u + 1 << '\n';
    }
  }
  return 0;
}
