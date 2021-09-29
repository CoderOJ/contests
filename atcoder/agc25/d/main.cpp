#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 605;

int n, d1, d2;
int col[3][N][N], cnt[2][2];

void solve(int d, int id)
{
  int k = 0;
  while (d % 4 == 0)
  {
    d /= 4;
    k += 1;
  }

  if (d % 4 == 3)
    return;
  k = 1 << k;

  if (d % 4 == 1)
  {
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
        col[id][i][j] = ((i - 1) / k + (j - 1) / k) & 1;
  }
  else
  {
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++)
        col[id][i][j] = ((i - 1) / k) & 1;
  }
}

int main()
{
  n = sc.next_int();
  d1 = sc.next_int();
  d2 = sc.next_int();
  n <<= 1;
  solve(d1, 1);
  solve(d2, 2);

  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      cnt[col[1][i][j]][col[2][i][j]] += 1;

  int x, y;
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++)
      if (cnt[i][j] >= n * n / 4)
        x = i, y = j;

  int tot = 0;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      if (col[1][i][j] == x && col[2][i][j] == y)
      {
        printf("%d %d\n", i - 1, j - 1);
        tot += 1;
        if (tot >= n * n / 4)
          return 0;
      }
  return 0;
}
