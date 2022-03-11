#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <cstring>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

#define int long long

constexpr int N   = 60;
constexpr int M   = 1005;
constexpr int INF = 0x1f1f1f1f1f1f1f1f;

int n, k, p;
int c[N], w[N], ratio[N];

int min_c[N];

void calc_min_c()
{
  int cur = p;
  for (int i = n - 1; i >= 0; i--)
  {
    min_c[i] = cur / c[i];
    cur %= c[i];
  }
  if (cur != 0)
  {
    puts("-1");
    exit(0);
  }
}

int mem[N][M][M];

int solve(int p, int cur, int require)
{
  see(p, cur, require);
  if (cur > require)
    return INF;
  if (p == -1)
    return require == 0 ? 0 : INF;

  if (mem[p][cur][require] != -1)
    return mem[p][cur][require];

  int ans = INF;
  check_min(
      ans,
      solve(p - 1, cur * ratio[p] + (p - 1 >= 0 ? min_c[p - 1] : 0), require));
  if (cur > 0 && require > 0)
    check_min(ans, solve(p, cur - 1, require - 1) + w[p]);

  mem[p][cur][require] = ans;
  return ans;
}

int32_t main()
{
  n = sc.next_int();
  k = sc.next_int();
  p = sc.next_long();
  for (int i = 0; i < n; i++)
  {
    c[i] = sc.next_long();
    w[i] = sc.next_long();
  }
  for (int i = 1; i < n; i++)
    ratio[i] = c[i] / c[i - 1];
  calc_min_c();

  memset(mem, -1, sizeof(mem));
  int ans_min = solve(n - 1, min_c[n - 1], k);
  for (int i = 0; i < n; i++)
    w[i] = -w[i];
  memset(mem, -1, sizeof(mem));
  int ans_max = -solve(n - 1, min_c[n - 1], k);

  if (ans_min == INF)
    std::cout << -1 << std::endl;
  else
    std::cout << ans_min << " " << ans_max << std::endl;

  return 0;
}
