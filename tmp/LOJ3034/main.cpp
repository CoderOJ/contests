#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <set>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

CONSTRAINT(N, 1000005, 1005)

int64_t a[N], b[N];
int64_t s[N], t[N];
int     p[N], q[N];
int     n, m;

std::vector<std::pair<int, int>> mod[N];

int64_t       dp[N];
std::set<int> nz, lz;

void dp_add(int p, int64_t v)
{
  if (p == 0)
  {
    dp[p] += v;
  }
  else
  {
    nz.erase(p);
    lz.erase(p);
    dp[p] += v;
    if (dp[p] != 0)
      nz.insert(p);
    if (dp[p] < 0)
      lz.insert(p);
  }
}

int main()
{
  n = sc.next_int();
  m = sc.next_int();
  for (int i = 1; i <= n; i++)
  {
    a[i] = sc.next_int() + a[i - 1];
    s[i] = sc.next_long();
    p[i] = sc.next_int();
  }
  for (int i = 1; i <= m; i++)
  {
    b[i] = sc.next_int() + b[i - 1];
    t[i] = sc.next_long();
    q[i] = sc.next_int();
  }

  int64_t ans = 0;

  for (int i = 1; i <= n; i++)
  {
    int pos =
        static_cast<int>(std::upper_bound(b, b + m + 1, s[i] - a[i]) - b) - 1;
    if (pos >= 0)
    {
      ans += p[i];
      mod[i - 1].emplace_back(pos + 1, -p[i]);
    }
  }
  for (int i = 1; i <= m; i++)
  {
    int pos =
        static_cast<int>(std::upper_bound(a, a + n + 1, t[i] - b[i]) - a) - 1;
    if (pos >= 0)
      mod[pos].emplace_back(i, q[i]);
  }

  for (int i = 0; i <= n; i++)
  {
    while (!lz.empty())
    {
      int  pa    = *lz.begin();
      auto pb_it = nz.upper_bound(pa);
      if (pb_it == nz.end())
      {
        dp_add(pa, -dp[pa]);
      }
      else
      {
        dp_add(*pb_it, dp[pa]);
        dp_add(pa, -dp[pa]);
      }
    }

    for (const auto &[p, d] : mod[i])
      dp_add(p, d);
  }

  for (int i = 0; i <= m; i++)
    ans += dp[i];
  std::cout << ans << std::endl;

  return 0;
}
