#include "/home/jack/cm/debug"
#include "/home/jack/cm/intm"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int MOD = 1'000'000'007;
constexpr int N   = 200050;
using int_t       = cm::intm<MOD>;

int n, m;
int a[N], b[N];

int_t dp[N];

void modify(int p, int_t d)
{
  p += 5;
  for (; p < N; p += p & (-p))
    dp[p] += d;
}

int_t query(int p)
{
  p += 5;
  int_t res = 0;
  for (; p; p -= p & (-p))
    res += dp[p];
  return res;
}

int main()
{
  n = sc.next_int();
  m = sc.next_int();
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();
  for (int i = 0; i < m; i++)
    b[i] = sc.next_int();

  std::vector<std::pair<int, int>> poss;
  for (int i = 0; i < n; i++)
    if (a[i] > b[0] && a[i] < b[m - 1])
    {
      auto pr = std::lower_bound(b, b + m, a[i]);
      auto pl = pr - 1;
      poss.emplace_back(a[i] - *pl, *pr - a[i]);
    }

  std::vector<int> values{0};
  for (const auto &[x, y] : poss)
  {
    values.push_back(x);
    values.push_back(y);
  }
  std::sort(values.begin(), values.end());
  values.erase(std::unique(values.begin(), values.end()), values.end());
  for (auto &[x, y] : poss)
  {
    x = static_cast<int>(std::distance(
        values.begin(), std::lower_bound(values.begin(), values.end(), x)));
    y = static_cast<int>(std::distance(
        values.begin(), std::lower_bound(values.begin(), values.end(), y)));
  }

  std::sort(poss.begin(), poss.end(), [](auto x, auto y) {
    return x.first != y.first ? x.first < y.first : x.second > y.second;
  });
  poss.erase(std::unique(poss.begin(), poss.end()), poss.end());

  modify(0, 1);
  for (const auto &[x, y] : poss)
    modify(y, query(y - 1));

  std::cout << query(N - 10) << std::endl;

  return 0;
}
