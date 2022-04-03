#include <bits/stdc++.h>

const int MOD = 998244353;
const int N = 5005;
int x[N], y[N], n, m;

int binom(int n, int m)
{
  static auto binom = []{
    std::array<std::array<int, N>, N> binom;
    for (int i = 0; i < N; i++)
    {
      binom[i][0] = 1;
      for (int j = 1; j <= i; j++)
        binom[i][j] = (binom[i - 1][j - 1] + binom[i - 1][j]) % MOD;
    }
    return binom;
  }();

  if (m < 0 || m > n) return 0;
  else return binom[n][m];
}

int solve(const std::vector<std::pair<int, int>> &limits)
{
  static int p[N];
  std::fill(p, p + n + 1, 0x3f3f3f3f);
  for (const auto &[k, v] : limits)
  {
    if (p[k] != 0x3f3f3f3f && p[k] != v)
      return 0;
    p[k] = v;
  }
  int last_pos = 0, last_sum = 0;
  int ans = 1;
  for (int i = 0; i <= n; i++)
    if (p[i] != 0x3f3f3f3f)
    {
      int cur_pos = i;
      int cur_sum = p[i];
      ans = 1ll * ans * binom(cur_pos - last_pos, cur_sum - last_sum) % MOD;
      last_pos = cur_pos;
      last_sum = cur_sum;
    }
  return ans;
}

void rmain()
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++)
    scanf("%d%d", &x[i], &y[i]);

  int max_same = 0;
  for (int i = 0; i < m; i++)
    if (x[i] == y[i])
      max_same = std::max(max_same, x[i]);

  int64_t ans = 0;
  for (int s = 0; s <= n; s++)
  {
    std::vector<std::pair<int, int>> limits{{n, s}};
    for (int i = 0; i < m; i++)
    {
      if (x[i] > y[i]) limits.emplace_back(x[i], y[i]);
      else if (x[i] < y[i]) limits.emplace_back(n - y[i], s - x[i]);
    }
    limits.emplace_back(max_same, max_same);
    int64_t ans10 = solve(limits);
    limits.pop_back();
    limits.emplace_back(n - max_same, s - max_same);
    int64_t ans01 = solve(limits);
    limits.pop_back();
    limits.emplace_back(max_same, max_same);
    limits.emplace_back(n - max_same, s - max_same);
    int64_t ans11 = solve(limits);
    ans += 0ll + ans10 + ans01- ans11;
  }
  ans = (ans % MOD + MOD) % MOD;
  printf("%" SCNi64 "\n", ans);
}

int main()
{
  int t;
  scanf("%d", &t);
  for (int i = 0; i < t; i++)
    rmain();
  return 0;
}
