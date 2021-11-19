#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  std::vector<std::vector<std::vector<std::vector<double>>>> v2p(
      8, std::vector<std::vector<std::vector<double>>>(8));

  int k = sc.next_int();

  for (int x = 0; x < 8; x++)
    for (int y = 0; y < 8; y++)
    {
      std::vector<std::vector<double>> prob(8, std::vector<double>(8, 0));
      prob[x][y] = 1;
      for (int r = 0; r < k; r++)
      {
        std::vector<std::vector<double>> cur(8, std::vector<double>(8, 0));
        for (int i = 0; i < 8; i++)
          for (int j = 0; j < 8; j++)
          {
            int cnt = 0;
            for (const auto &[dx, dy] : std::vector<std::pair<int, int>>(
                     {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}))
              if (i + dx >= 0 && i + dx < 8 && j + dy >= 0 && j + dy < 8)
                cnt++;
            for (const auto &[dx, dy] : std::vector<std::pair<int, int>>(
                     {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}))
              if (i + dx >= 0 && i + dx < 8 && j + dy >= 0 && j + dy < 8)
                cur[i + dx][j + dy] += prob[i][j] / cnt;
          }
        prob = std::move(cur);
      }
      v2p[x][y] = std::move(prob);
    }

  double ans = 0;
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
    {
      double cur = 1;
      for (int x = 0; x < 8; x++)
        for (int y = 0; y < 8; y++)
          cur *= (1 - v2p[x][y][i][j]);
      ans += cur;
    }

  printf("%.6lf\n", ans);

  return 0;
}
