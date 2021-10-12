#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int MOD = 1000000007;
constexpr int N = 200005;
int n, m, k;
int a[N];
int cnt[N], mval[N];
int f[N][2];

int power(int a, int k)
{
  int ans = 1;
  while (k)
  {
    if (k & 1)
      ans = 1ll * ans * a % MOD;
    a = 1ll * a * a % MOD;
    k >>= 1;
  }
  return ans;
}

int solve()
{
  n = sc.next_int();
  m = sc.next_int();
  k = sc.next_int();
  for (int i = 1; i <= n + m; i++)
    a[i] = sc.next_int();
  for (int i = 1; i <= n + m - 1; i++)
    cnt[i] = std::min(std::min(i, n + m - i), std::min(n, m)), mval[i] = 1;
  while (k--)
  {
    int x = sc.next_int();
    int y = sc.next_int();
    int h = sc.next_int();
    ;
    cnt[x + y - 1]--;
    mval[x + y - 1] = std::max(mval[x + y - 1], h);
  }

  f[0][0] = 1;
  f[0][1] = MOD - 1;
  for (int i = 1; i <= n + m - 1; i++)
  {
    f[i][0] = f[i][1] = 0;
    for (int d1 = 0; d1 <= 1; d1++)
      for (int d2 = 0; d2 <= 1; d2++)
      {
        int H = std::min(a[i] - d1, a[i + 1] - d2);
        if (H < mval[i])
          continue;
        f[i][d2] = (f[i][d2] + 1LL * f[i - 1][d1] * power(H, cnt[i])) % MOD;
      }
    f[i][1] = (MOD - f[i][1]) % MOD;
  }
  return (f[n + m - 1][0] + f[n + m - 1][1]) % MOD;
}

int main()
{
  int T = sc.next_int();
  for (int t = 1; t <= T; t++)
    printf("Case #%d: %d\n", t, solve());
}
