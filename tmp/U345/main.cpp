#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 100005;

std::vector<int> e[N];

int n;

struct dp_t
{
  int min = 0;
  int max = 0;

  dp_t() = default;
  dp_t(int min, int max) : min(min), max(max) {}

  dp_t(dp_t lhs, dp_t rhs)
  {
    // see(lhs, rhs);
    min = std::max(
        {(lhs.min + rhs.min) % 2, lhs.min - rhs.max, rhs.min - lhs.max});
    max = lhs.max + rhs.max;
    // see(*this);
  }

  dp_t extend(int val) const
  {
    return {min + val, max + val};
  }

  static constexpr dp_t nop()
  {
    return dp_t();
  }
};

std::ostream &operator<<(std::ostream &lhs, dp_t rhs)
{
  return lhs << "{ min: " << rhs.min << ", max: " << rhs.max << " }";
}

dp_t dp[N];

void dfs_init_dp(int u, int f)
{
  dp_t dpu = dp_t::nop();
  for (int v : e[u])
    if (v != f)
    {
      dfs_init_dp(v, u);
      dpu = dp_t(dpu, dp[v].extend(1));
    }
  dp[u] = dpu;
  // see(u, dp[u]);
}

bool ans[N];

void dfs_calc_ans(int u, int f, dp_t lhs)
{
  dp_t rhs = dp[u];
  ans[u]   = dp_t(lhs, rhs).min == 0;

  std::vector<dp_t> pre{dp_t::nop()};
  for (auto v_it = e[u].begin(); v_it != e[u].end(); v_it++)
    if (*v_it != f)
      pre.push_back(dp_t(pre.back(), dp[*v_it].extend(1)));
  pre.pop_back();

  std::vector<dp_t> suf{dp_t::nop()};
  for (auto v_it = e[u].rbegin(); v_it != e[u].rend(); v_it++)
    if (*v_it != f)
      suf.push_back(dp_t(suf.back(), dp[*v_it].extend(1)));
  suf.pop_back();
  std::reverse(suf.begin(), suf.end());

  size_t it = 0;
  for (int v : e[u])
    if (v != f)
    {
      // see(it);
      dp_t v_lhs = dp_t(lhs, dp_t(pre[it], suf[it]));
      dfs_calc_ans(v, u, v_lhs);
      it++;
    }
}

int main()
{
  [[maybe_unused]] int w = sc.next_int();
  int                  t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    n = sc.next_int();
    for (int i = 1; i <= n; i++)
      e[i].clear();
    for (int i = 1; i < n; i++)
    {
      int u = sc.next_int();
      int v = sc.next_int();
      e[u].push_back(v);
      e[v].push_back(u);
    }
    dfs_init_dp(1, 0);

    std::fill(ans + 1, ans + n + 1, false);
    dfs_calc_ans(1, 0, dp_t::nop());

    for (int u = 1; u <= (w != 3 ? n : 1); u++)
      putchar_unlocked(ans[u] ? '1' : '0');
    putchar_unlocked('\n');
  }
  return 0;
}
