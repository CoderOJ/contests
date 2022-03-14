#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

struct int_kt
{
  int64_t val;
  int64_t cnt;

  int_kt() = default;
  int_kt(int64_t val, int64_t cnt) : val(val), cnt(cnt) {}

  int_kt operator+(int_kt rhs) const
  {
    return {val + rhs.val, cnt + rhs.cnt};
  }

  bool operator<(int_kt rhs) const
  {
    return val != rhs.val ? val < rhs.val : cnt < rhs.cnt;
  }
};

struct dp_t
{
  int_kt dp0 = {0, 0};
  int_kt dp1 = {0, 0};
  int_kt dp2 = {0, 0};

  int_kt answer() const
  {
    return std::max({dp0, dp1, dp2});
  }
};

dp_t trans(dp_t lhs, dp_t rhs, int64_t w, int64_t k)
{
  auto rhs_ans = std::max(rhs.dp0, int_kt(k, 1) + rhs.answer());
  rhs.dp1.val += w;

  lhs.dp2 = std::max({
      lhs.dp0 + rhs.dp2,
      lhs.dp1 + rhs.dp1,
      lhs.dp2 + rhs_ans,
  });
  lhs.dp1 = std::max({
      lhs.dp1 + rhs_ans,
      lhs.dp0 + rhs.dp1,
  });
  lhs.dp0 = lhs.dp0 + rhs_ans;

  return lhs;
}

constexpr int N = 300'005;

std::vector<std::pair<int, int>> e[N];

int n, k;

dp_t dfs(int u, int f, int64_t k)
{
  dp_t res;

  for (const auto &[v, w] : e[u])
    if (v != f)
      res = trans(res, dfs(v, u, k), w, k);

  return res;
}

int main()
{
  n = sc.next_int();
  k = sc.next_int();

  for (int i = 1; i < n; i++)
  {
    int u = sc.next_int();
    int v = sc.next_int();
    int w = sc.next_int();
    e[u].emplace_back(v, w);
    e[v].emplace_back(u, w);
  }

  int64_t l = -1e10;
  int64_t r = 1e10;

  while (l < r)
  {
    int64_t m   = l + (r - l) / 2;
    auto    ans = dfs(1, 0, m).answer();

    if (ans.cnt == k)
    {
      l = m;
      r = m;
      break;
    }

    if (ans.cnt >= k)
      r = m;
    else
      l = m + 1;
  }

  auto ans = dfs(1, 0, l).answer();
  std::cout << ans.val - l * k << std::endl;

  return 0;
}
