#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <queue>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

CONSTRAINT(N, 200005, 205)

int     a[N], b[N];
int     n, m, t;
int64_t x[N], c[N];

std::vector<std::pair<int, int64_t>> g[N];

bool check(int64_t k, int ex)
{
  static std::priority_queue<std::pair<int, int64_t>> q;

  static int64_t res[N];

  int64_t d = x[t] - k + ex, s = 0;

  while (!q.empty())
    q.pop();

  for (int i = 1; i <= n; i++)
    res[i] = 0, g[i].clear();

  res[t] -= d;

  for (int i = 1; i <= m; i++)
    if (a[i] <= t && t <= b[i])
      g[a[i]].push_back({b[i], c[i]});

  for (int i = 1; i <= t; i++)
  {
    for (auto v : g[i])
      q.push(v);

    while (x[i] - s + (d - s) - k > 0)
    {
      if (q.empty())
        return false;

      auto [u, v] = q.top();
      q.pop();
      int64_t w = std::min(v, (x[i] - s + (d - s) - k + 1) / 2);
      s += w, res[u] += w * 2;

      if (w < v)
        q.push({u, v - w});
    }
  }

  for (int i = t + 1; i <= n; i++)
    res[i] += res[i - 1];

  for (int i = t + 1; i <= n; i++)
    if (x[i] + res[i] > k)
      return false;

  return true;
}

int main()
{
  n = sc.next_int();
  m = sc.next_int();

  for (int i = 1; i <= m; i++)
  {
    a[i] = sc.next_int();
    b[i] = sc.next_int();
    c[i] = sc.next_int();

    if (a[i] > b[i])
      std::swap(a[i], b[i]);

    x[a[i]] += c[i];
    x[b[i]] -= c[i];
  }

  for (int i = 1; i <= n; i++)
    x[i] += x[i - 1];

  t = static_cast<int>(std::max_element(x + 1, x + n + 1) - x);

  int64_t l = 1, r = *std::max_element(x + 1, x + n + 1);
  int64_t ans = 0;
  while (l <= r)
  {
    int64_t mid = l + (r - l) / 2;

    if (check(mid, 0) || check(mid, 1))
      r = mid - 1, ans = mid;
    else
      l = mid + 1;
  }

  std::cout << ans << std::endl;
  return 0;
}
