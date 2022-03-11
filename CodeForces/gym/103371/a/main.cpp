#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

#define int long long

constexpr int N = 1005;

char trash[N * 20];

int a[N][N];
int dx[N], dy[N];
int sx[N], sy[N];
int n;

int32_t main()
{
  n = sc.next_int();
  for (int j = 0; j < n; j++)
    a[0][j] = sc.next_long();
  for (int i = 1; i < n; i++)
  {
    a[i][0] = sc.next_long();
    sc.next_line(trash);
  }

  for (int i = 1; i < n; i++)
    dx[i] = a[i][0] - a[i - 1][0];
  for (int i = 1; i < n; i++)
    dy[i] = a[0][i] - a[0][i - 1];

  for (int i = 1; i < n - 1; i++)
    sx[i] = (dx[i + 1] - dx[i]) / 2;
  for (int i = 1; i < n - 1; i++)
    sy[i] = (dy[i + 1] - dy[i]) / 2;

  int x2_add_y2 = a[0][0];
  for (int i = 0; i < n; i++)
  {
    x2_add_y2 -= i * sx[i];
    x2_add_y2 -= i * sy[i];
  }
  x2_add_y2 /= (n - 1);

  int x2_add_y1 = a[0][n - 1];
  for (int i = 0; i < n; i++)
  {
    x2_add_y1 -= i * sx[i];
    x2_add_y1 -= (n - i - 1) * sy[i];
  }
  x2_add_y1 /= (n - 1);

  int x1_add_y2 = a[n - 1][0];
  for (int i = 0; i < n; i++)
  {
    x1_add_y2 -= (n - i - 1) * sx[i];
    x1_add_y2 -= i * sy[i];
  }
  x1_add_y2 /= (n - 1);

  int x1_add_y1 = x1_add_y2 + x2_add_y1 - x2_add_y2;

  int x1_sub_x2 = x1_add_y1 - x2_add_y1;
  int y1_sub_y2 = x1_add_y1 - x1_add_y2;

  int x1_add_x2_sub_y1_sub_y2 = 0;
  for (int i = 1; i < n - 1; i++)
  {
    x1_add_x2_sub_y1_sub_y2 -= sx[i];
    x1_add_x2_sub_y1_sub_y2 += sy[i];
  }

  int x1_sub_y2 = (x1_sub_x2 + y1_sub_y2 + x1_add_x2_sub_y1_sub_y2) / 2;

  int x1 = (x1_add_y2 + x1_sub_y2) / 2;
  int y1 = x1_add_y1 - x1;
  int x2 = x2_add_y1 - y1;
  int y2 = x2_add_y2 - x2;

  sx[0]     = x1;
  sx[n - 1] = x2;
  sy[0]     = y1;
  sy[n - 1] = y2;

  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
    {
      int w = std::min(sx[i], sy[j]);
      sx[i] -= w;
      sy[j] -= w;
      printf("%lld%c", w, " \n"[j == n - 1]);
    }

  return 0;
}
