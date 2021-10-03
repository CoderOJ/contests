#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <numeric>
#include <limits>

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 405;
int a[N][N], b[N][N], n, m;

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    n = sc.next_int();
    m = sc.next_int();
    for (int i = 0; i < n; i++)
      for (int j = 0; j < m; j++)
        a[i][j] = b[i][j] = sc.next_char() - '0';
    for (int i = 1; i < n; i++)
      for (int j = 0; j < m; j++)
        b[i][j] += b[i-1][j];

    int ans = std::numeric_limits<int>::max();
    for (int i = 0; i < n; i++)
      for (int j = i + 4; j < n; j++)
      {
        int c[N], d = std::numeric_limits<int>::min();
        c[0] = 0;
        for (int k = 0; k < m; k++)
        {
          see(i, j, k, c[k], d);
          if (k >= 3)
          {
            see(c[k-2], (j-i-1) - (b[j-1][k-3] - b[i][k-3]));
            check_max(d, c[k-2] - (j-i-1) + (b[j-1][k-3] - b[i][k-3]));
            check_min(ans, c[k] - d + (j-i-1) - (b[j-1][k] - b[i][k]));
          }
          c[k + 1] = c[k] + (a[i][k]==0) + (a[j][k]==0) + (b[j-1][k] - b[i][k]);
          see(a[i][k] == 0, a[j][k] == 0, b[j-1][k] - b[i][k]);
        }
      }
    std::cout << ans << std::endl;
  }
  return 0;
}

