#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <functional>
#include <queue>

int main()
{
  int n, m;
  std::cin >> n >> m;
  std::vector<std::string> a(n);
  for (int i = 0; i < n; i++)
    std::cin >> a[i];

  int st_x, st_y, ed_x, ed_y;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (a[i][j] == 'A')
        st_x = i, st_y = j;
      else if (a[i][j] == 'B')
        ed_x = i, ed_y = j;

  std::vector<std::vector<std::tuple<int, int, char>>> last(
      n, std::vector<std::tuple<int, int, char>>(m, {-1, -1, 'a'}));
  last[st_x][st_y] = {-2, -2, 'a'};
  std::queue<std::pair<int, int>> que;
  que.push(std::make_pair(st_x, st_y));
  while (!que.empty())
  {
    const auto [x, y] = que.front();
    see(x, y);
    que.pop();
    const int move[][3] = {
        {1, 0, 'D'}, {0, 1, 'R'}, {-1, 0, 'U'}, {0, -1, 'L'}};
    for (const auto [dx, dy, dc] : move)
    {
      int cx = x + dx, cy = y + dy;
      if (cx < 0 || cx >= n || cy < 0 || cy >= m)
        continue;
      if (a[cx][cy] == '#')
        continue;
      if (last[cx][cy] != std::make_tuple(-1, -1, 'a'))
        continue;
      last[cx][cy] = std::make_tuple(x, y, dc);
      que.emplace(cx, cy);
    }
  }

  if (last[ed_x][ed_y] == std::make_tuple(-1, -1, 'a'))
  {
    puts("NO");
    return 0;
  }

  std::string ans;
  int cx = ed_x, cy = ed_y;
  while (cx != st_x || cy != st_y)
  {
    const auto [px, py, pc] = last[cx][cy];
    ans += pc;
    cx = px, cy = py;
  }
  puts("YES");
  std::reverse(ans.begin(), ans.end());
  std::cout << ans.length() << std::endl << ans << std::endl;
  return 0;
}
