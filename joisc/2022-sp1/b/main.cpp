#include <bits/stdc++.h>

int main()
{
  int n, m;
  scanf("%d%d", &n, &m);

  auto read_convex = [](int n) {
    std::vector<std::pair<int,int>> a;
    for (int i = 0; i < n; i++)
    {
      int x = i;
      int y; scanf("%d", &y);
      while (a.size() >= 2)
      {
        const auto &[px, py] = *(a.end() - 1);
        const auto &[ppx, ppy] = *(a.end() - 2);
        if (1ll * (py - ppy) * (x - px) < 1ll * (y - py) * (px - ppx))
          break;
        a.pop_back();
      }
      a.emplace_back(x, y);
    }
    return a;
  };

  auto a = read_convex(n);
  auto b = read_convex(m);

  auto a_it = a.begin();
  auto b_it = b.begin();
  int64_t ans = 0;
  while (a_it->first != n - 1 || b_it->first != m - 1)
  {
    auto next = [](auto a_it, auto b_it) {
      return 1ll * a_it->second * ((b_it + 1)->first - b_it->first);
    };
    auto slope = [](auto a_it, auto b_it) {
      return 1ll * ((a_it + 1)->second - a_it->second) * ((b_it + 1)->first - b_it->first);
    };
    if (a_it->first == n - 1)
    {
      ans += next(a_it, b_it);
      b_it++;
    }
    else if (b_it->first == m - 1)
    {
      ans += next(b_it, a_it);
      a_it++;
    }
    else
    {
      if (slope(b_it, a_it) < slope(a_it, b_it))
      {
        ans += next(a_it, b_it);
        b_it++;
      }
      else
      {
        ans += next(b_it, a_it);
        a_it++;
      }
    }
  }

  std::cout << ans << std::endl;

  return 0;
}
