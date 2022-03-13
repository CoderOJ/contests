#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <cstring>
#include <queue>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

std::vector<int> trans[2][6] = {
    {
        {0, 1, 2},
        {1},
        {3},
        {3},
        {5},
        {5},
    },
    {
        {0, 1, 2},
        {4},
        {2},
        {5},
        {4},
        {5},
    },
};

constexpr int move[][3] = {{1, 0, 0}, {-1, 0, 0}, {0, 1, 1}, {0, -1, 1}};

constexpr int N = 1005;

char map[N][N];
int  sx, sy;
int  tx, ty;
int  n;

int dis[N][N][6];

int main()
{
  n = sc.next_int();
  for (int i = 0; i < n; i++)
  {
    sc.next_token(map[i]);
    for (int j = 0; j < n; j++)
    {
      if (map[i][j] == 'P')
        sx = i, sy = j;
      else if (map[i][j] == 'K')
        tx = i, ty = j;
    }
  }

  memset(dis, 0x3f, sizeof(dis));
  std::queue<std::tuple<int, int, int>> que;
  dis[sx][sy][0] = 0;
  que.emplace(sx, sy, 0);

  while (!que.empty())
  {
    const auto [ux, uy, ut] = que.front();
    que.pop();
    for (const auto &[dx, dy, dc] : move)
    {
      int vx = ux + dx;
      int vy = uy + dy;
      if (vx >= 0 && vx < n && vy >= 0 && vy < n && map[vx][vy] != 'X')
        for (int vt : trans[dc][ut])
          if (map[vx][vy] != '#' || (1 <= vt && vt <= 4))
          {
            if (check_min(dis[vx][vy][vt], dis[ux][uy][ut] + 1))
              que.emplace(vx, vy, vt);
          }
    }
  }

  int ans = *std::min_element(dis[tx][ty], dis[tx][ty] + 6);
  if (ans < 0x3f3f3f3f)
    std::cout << ans << std::endl;
  else
    std::cout << "NIE" << std::endl;

  return 0;
}
