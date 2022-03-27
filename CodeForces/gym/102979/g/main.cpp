#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <cstring>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 305;

int n;

int q[N][N];
int q_lp[N][N], q_rp[N][N];

std::vector<std::pair<int, int64_t>> a[N];

void build(std::vector<std::pair<int, int64_t>> &a)
{
  std::sort(a.begin(), a.end());
  std::vector<std::pair<int, int64_t>> b;
  for (const auto &[ax, ay] : a)
  {
    while (b.size() >= 2)
    {
      const auto [bpx, bpy] = *(b.end() - 2);
      const auto [bx, by]   = *(b.end() - 1);
      if ((__int128_t)(by - bpy) * (ax - bx) >
          (__int128_t)(ay - by) * (bx - bpx))
        break;
      b.pop_back();
    }
    b.emplace_back(ax, ay);
  }
  a = std::move(b);
}

std::vector<std::pair<int, int64_t>> plots[N];

int64_t query(const std::vector<std::pair<int, int64_t>> &p, int64_t x)
{
  size_t l = 0;
  size_t r = p.size() - 1;
  while (l < r)
  {
    size_t  m  = l + (r - l) / 2;
    int64_t va = p[m].first * x + p[m].second;
    int64_t vb = p[m + 1].first * x + p[m + 1].second;
    if (va > vb)
      r = m;
    else
      l = m + 1;
  }
  return p[l].first * x + p[l].second;
}

int64_t dp[N][N];

int main()
{
  n = sc.next_int();
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j <= n; j++)
    {
      q[i][j]        = sc.next_int();
      q_lp[i][j]     = q_lp[i][j - 1] + q[i][j];
      q_rp[i + 1][j] = q_rp[i][j] + q[i][j];
    }
  for (int i = 0; i < n; i++)
  {
    int k = sc.next_int();
    plots[i].reserve(k);
    for (int j = 0; j < k; j++)
    {
      int     v = sc.next_int();
      int64_t c = sc.next_long();
      plots[i].emplace_back(v, -c);
    }
    build(plots[i]);
  }

  memset(dp, 0xcf, sizeof(dp));
  for (int i = 0; i <= n; i++)
    dp[i][i] = 0;
  for (int l = n - 1; l >= 0; l--)
    for (int r = l + 1; r <= n; r++)
    {
      int64_t cross_cnt = 0;
      for (int m = l; m < r; m++)
      {
        cross_cnt += q_lp[m][r] - q_lp[m][m];
        cross_cnt -= q_rp[m][m] - q_rp[l][m];
        check_max(dp[l][r],
                  dp[l][m] + dp[m + 1][r] + query(plots[m], cross_cnt));
        // see(l,
        //     r,
        //     m,
        //     cross_cnt,
        //     dp[l][r],
        //     dp[l][m],
        //     dp[m + 1][r],
        //     query(plots[m], cross_cnt));
      }
    }

  std::cout << dp[0][n] << std::endl;

  return 0;
}
