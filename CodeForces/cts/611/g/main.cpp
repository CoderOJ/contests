#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int MOD = 1'000'000'007;

struct point_t
{
  long long x = 0, y = 0;
  point_t() = default;
  point_t(long long x, long long y) : x(x), y(y) {}
};

point_t operator+(const point_t &lhs, const point_t &rhs)
{
  return point_t(lhs.x + rhs.x, lhs.y + rhs.y);
}
point_t operator-(const point_t &lhs, const point_t &rhs)
{
  return point_t(lhs.x - rhs.x, lhs.y - rhs.y);
}
long long operator^(const point_t &lhs, const point_t &rhs)
{
  return lhs.x * rhs.y - lhs.y * rhs.x;
}

constexpr int N = 1'000'005;
point_t       p[N], q[N];
long long     f[N], g[N];
int           n, ans;

int main()
{
  n = sc.next_int();
  for (int i = 1; i <= n; i++)
  {
    p[i].x = sc.next_int();
    p[i].y = sc.next_int();
    q[i]   = q[i - 1] + p[i];
    q[i].x %= MOD;
    q[i].y %= MOD;
  }
  for (int i = 2; i <= n; i++)
  {
    f[i] = f[i - 1] + (p[i - 1] ^ p[i]);
    g[i] = (g[i - 1] + f[i]) % MOD;
  }
  f[n + 1] = f[n] + (p[n] ^ p[1]);
  for (int i = 3, j = 1; i <= n; i++)
  {
    while (j < i - 1 &&
           std::abs(f[n + 1]) < std::abs((f[i] - f[j]) + (p[i] ^ p[j])) * 2.0L)
      j++;
    ans = (ans + f[i] % MOD * (i - j - 1) - (g[i - 2] - g[j - 1]) +
           (p[i] ^ (q[i - 2] - q[j - 1]))) %
          MOD;
    ans = (ans + (f[n + 1] - f[i]) % MOD * (j - 1) + g[j - 1] -
           (p[i] ^ q[j - 1])) %
          MOD;
  }
  ans = (ans + MOD) * 2ll % MOD;
  ans = (ans + std::abs(f[n + 1]) % MOD * (n * (n - 3ll) / 2 % MOD)) % MOD;
  printf("%d\n", ans);
  return 0;
}
