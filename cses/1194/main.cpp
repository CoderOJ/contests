#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int(), m = sc.next_int();
  std::vector<std::vector<char>> a(n, std::vector<char>(m));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      a[i][j] = sc.next_char();

  std::vector<std::vector<bool>> forbid(n, std::vector<bool>(m, false));
  std::vector<std::vector<std::tuple<int, int, char>>> pre(
      n, std::vector<std::tuple<int, int, char>>(m, {-1, -1, 'a'}));
  std::vector<std::pair<int, int>> mons, yous;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (a[i][j] == 'M')
      {
        mons.emplace_back(i, j);
        forbid[i][j] = true;
      }
      else if (a[i][j] == 'A')
      {
        pre[i][j] = {-2, -2, 'a'};
        yous.emplace_back(i, j);
      }

  constexpr int move[][3] = {
      {0, 1, 'R'}, {1, 0, 'D'}, {0, -1, 'L'}, {-1, 0, 'U'}};

  while (!yous.empty())
  {
    see(mons);
    see(yous);
    std::vector<std::pair<int, int>> new_mons;
    for (const auto &[mx, my] : mons)
      for (const auto &[dx, dy, dc] : move)
      {
        int cx = mx + dx, cy = my + dy;
        if (cx < 0 || cx >= n || cy < 0 || cy >= m)
          continue;
        if (a[cx][cy] == '#')
          continue;
        if (forbid[cx][cy])
          continue;
        forbid[cx][cy] = true;
        new_mons.emplace_back(cx, cy);
      }

    std::vector<std::pair<int, int>> new_yous;
    for (const auto &[mx, my] : yous)
      for (const auto &[dx, dy, dc] : move)
      {
        int cx = mx + dx, cy = my + dy;
        if (cx < 0 || cx >= n || cy < 0 || cy >= m)
          continue;
        if (a[cx][cy] == '#' || forbid[cx][cy])
          continue;
        if (pre[cx][cy] != std::make_tuple(-1, -1, 'a'))
          continue;
        pre[cx][cy] = std::make_tuple(mx, my, dc);
        new_yous.emplace_back(cx, cy);
      }

    mons = std::move(new_mons);
    yous = std::move(new_yous);
  }

  std::vector<std::pair<int, int>> exits;
  for (int i = 0; i < n; i++)
  {
    if (a[i][0] != '#')
      exits.emplace_back(i, 0);
    if (a[i][m - 1] != '#')
      exits.emplace_back(i, m - 1);
  }
  for (int j = 0; j < m; j++)
  {
    if (a[0][j] != '#')
      exits.emplace_back(0, j);
    if (a[n - 1][j] != '#')
      exits.emplace_back(n - 1, j);
  }

  for (auto [x, y] : exits)
    if (pre[x][y] != std::make_tuple(-1, -1, 'a'))
    {
      puts("YES");
      std::string ans;
      while (pre[x][y] != std::make_tuple(-2, -2, 'a'))
      {
        see(x, y, pre[x][y]);
        const auto [px, py, pc] = pre[x][y];
        ans += pc;
        x = px, y = py;
      }
      std::reverse(ans.begin(), ans.end());
      std::cout << ans.length() << std::endl << ans << std::endl;
      return 0;
    }

  puts("NO");

  return 0;
}
