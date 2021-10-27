#include <stdio.h>

#define INF 0x3f3f3f3f
#define N 505
int a[N][N], n;
char s[N];

struct row_range_t
{
  int l, r;
};

struct row_range_t _rr[2][N][N], (*rr[N])[N];

struct row_range_t join_range(struct row_range_t lhs, struct row_range_t rhs)
{
  if (lhs.l > rhs.l)
    lhs.l = rhs.l;
  if (lhs.r < rhs.r)
    lhs.r = rhs.r;
  return lhs;
}

void init_rr()
{
  for (int i = n - 1; i >= 0; i--)
    for (int j = n - 1; j >= 0; j--)
    {
    }
}

int row_psum[N][N];

void init_row_psum(int i)
{
  for (int j = 0; j < n; j++)
    row_psum[i][j + 1] = row_psum[i][j] + a[i][j];
}

void test_erase(int x, int y)
{
  if (x >= n || y >= n)
    return;
  if (a[x][y] == 0)
    return;
  if (x > 0 && a[x - 1][y])
    return;
  if (y > 0 && a[x][y - 1])
    return;

  a[x][y] = 0;
  init_row_psum(x);
  test_erase(x + 1, y);
  test_erase(x, y + 1);
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
  {
    scanf("%s", s);
    for (int j = 0; j < n; j++)
      if (s[j] == '#')
        a[i][j] = 0;
      else
        a[i][j] = s[j] - '0';
  }

  for (int i = 0; i < n; i++)
    init_row_psum(i);

  for (int i = 0; i < n; i++)
    rr[i] = _rr[i % 2];

  long long ans = 0;
  for (int i = n - 1; i >= 0; i--)
    for (int j = n - 1; j >= 0; j--)
    {
      rr[i][j][i] = (struct row_range_t){.l = j, .r = j};
      if (a[i][j + 1])
        rr[i][j][i] = join_range(rr[i][j][i], rr[i][j + 1][i]);
      for (int k = i + 1; k < n; k++)
      {
        rr[i][j][k] = (struct row_range_t){.l = INF, .r = 0};
        if (a[i][j + 1])
          rr[i][j][k] = join_range(rr[i][j][k], rr[i][j + 1][k]);
        if (a[i + 1][j])
          rr[i][j][k] = join_range(rr[i][j][k], rr[i + 1][j][k]);
      }

      for (int k = i; k < n; k++)
      {
        if (rr[i][j][k].l > rr[i][j][k].r)
          break;
        ans += (row_psum[k][rr[i][j][k].r + 1] - row_psum[k][rr[i][j][k].l]) *
               a[i][j];
      }
      ans -= a[i][j] * a[i][j];
      test_erase(i, j);
    }
  printf("%lld\n", ans);

  return 0;
}
