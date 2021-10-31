#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <functional>

int main()
{
  int n, m; 
  std::cin >> n >> m;
  std::vector<std::string> a(n);
  for (int i = 0; i < n; i++)
    std::cin >> a[i];

  std::vector<std::vector<int>> col(n, std::vector<int>(m));
  std::function<void(int,int,int)> flood_fill = [&](int x, int y, int c) {
    if (x < 0 || x >= n || y < 0 || y >= m)
      return;
    if (col[x][y])
      return;
    if (a[x][y] == '#')
      return;
    col[x][y] = c;
    flood_fill(x - 1, y, c);
    flood_fill(x + 1, y, c);
    flood_fill(x, y - 1, c);
    flood_fill(x, y + 1, c);
  };

  int ans = 0;
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      if (a[i][j] != '#' && !col[i][j])
        flood_fill(i, j, ++ans);

  std::cout << ans << std::endl;

  return 0;
}

