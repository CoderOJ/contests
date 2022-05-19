#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

std::pair<int, int> get_pos(int n, int k)
{
  if (k == n * n - 1)
    return {n / 2, n / 2};

  int c = 0, l = n - 1;
  while (k >= l * 4)
  {
    k -= l * 4;
    c += 1;
    l -= 2;
  }
  if (k < l)
    return {c, c + k};
  else if (k < 2 * l)
    return {c + (k - l), n - 1 - c};
  else if (k < 3 * l)
    return {n - 1 - c, n - c - 1 - (k - 2 * l)};
  else
    return {n - c - 1 - (k - 3 * l), c};
}

int get_val(int n, int x, int y)
{
  int b   = std::min({x, y, n - 1 - x, n - 1 - y});
  int ans = (n - 1 + n - (b - 1) * 2 - 1) * b * 2;

  n -= b * 2;
  x -= b;
  y -= b;

  if (x == 0)
    return ans + y;
  else if (y == n - 1)
    return ans + (n - 1) + x;
  else if (x == n - 1)
    return ans + (n - 1) * 2 + (n - 1 - y);
  else
    return ans + (n - 1) * 3 + (n - 1 - x);
}

int main()
{
  // {
  //   int n = 11;
  //   for (int i = 0; i < n; i++)
  //   {
  //     for (int j = 0; j < n; j++)
  //     {
  //       printf("%4d", get_val(n, i, j));
  //       cm_assert(get_pos(n, get_val(n, i, j)) == std::make_pair(i, j));
  //     }
  //     puts("");
  //   }
  //   return 0;
  // }

  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    int n = sc.next_int();
    int k = sc.next_int();

    printf("Case #%d: ", i + 1);

    if (k % 2 == 1)
    {
      puts("IMPOSSIBLE");
    }
    else if (k < n - 1)
    {
      puts("IMPOSSIBLE");
    }
    else
    {
      const int gx = n / 2, gy = n / 2;
      int       el = 0, er = n * n - 1;
      while (el < er)
      {
        const int em           = el + (er - el + 1) / 2;
        const auto &[epx, epy] = get_pos(n, em);
        const int ed           = em + std::abs(epx - gx) + std::abs(epy - gy);
        if (ed > k)
          er = em - 1;
        else
          el = em;
      }

      auto [px, py] = get_pos(n, el);
      std::vector<int> path{el};

      while (px != gx || py != gy)
      {
        int vx = px < gx ? px + 1 : px - 1;
        int vy = py < gy ? py + 1 : py - 1;
        if (px == gx)
        {
          std::tie(px, py) = {px, vy};
          path.push_back(get_val(n, px, py));
        }
        else if (py == gy)
        {
          std::tie(px, py) = {vx, py};
          path.push_back(get_val(n, px, py));
        }
        else
        {
          int vvx = get_val(n, vx, py);
          int vvy = get_val(n, px, vy);
          if (vvx > path.back())
          {
            std::tie(px, py) = {vx, py};
            path.push_back(vvx);
          }
          else
          {
            std::tie(px, py) = {px, vy};
            path.push_back(vvy);
          }
        }
      }

      std::vector<std::pair<int, int>> ans;
      for (size_t i = 0; i + 1 < path.size(); i++)
      {
        int x = path[i], y = path[i + 1];
        if (y > x + 1)
          ans.emplace_back(x, y);
      }

      printf("%zu\n", ans.size());
      for (const auto &[x, y] : ans)
        printf("%d %d\n", x + 1, y + 1);
    }
  }
  return 0;
}
