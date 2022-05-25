#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <cstring>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

const int N = 1000005;

char s[N], t[N];
int  n;

char op(char c, int x, int y)
{
  if (x == 1)
    c = '0';
  if (x == 2)
    c = '1';
  if (y == 1)
    c = c == '0' ? '1' : '0';
  return c;
}

int dp[N][3][2];

int main()
{
  n = sc.next_int();
  sc.next_token(s);
  sc.next_token(t);

  memset(dp, 0x3f, sizeof(dp));
  dp[0][0][0] = 0;
  for (int i = 0; i < n; i++)
    for (int x = 0; x < 3; x++)
      for (int y = 0; y < 2; y++)
        if (op(s[i], x, y) == t[i])
        {
          for (int px = 0; px < 3; px++)
            for (int py = 0; py < 2; py++)
              check_min(dp[i + 1][x][y], dp[i][px][py] + (x != px && x) + (y != py && y));
        }

  int ans = 0x3f3f3f3f;
  for (int x = 0; x < 3; x++)
    for (int y = 0; y < 2; y++)
      check_min(ans, dp[n][x][y]);

  std::cout << ans << std::endl;

  return 0;
}
