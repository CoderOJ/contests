#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>
#include <limits>

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 1000005;
constexpr int inf = std::numeric_limits<int>::max() / 2;
int a[N], b[N];
int n, m;

int v[N], ans[N];
inline void get(int i, int k, int &x)
{
  int o = static_cast<int>(std::lower_bound(b + 1, b + m + 1, k) - b - 1);
  v[o] = 1, x = ans[i] = b[o];
}

int l[N], p[N], f[N], g[N];

int main()
{
  n = sc.next_int();
  for (int i = 1; i <= n; i++)
  {
    a[i] = sc.next_int();
    f[i] = inf;
  }

  ++n, a[n] = f[n] = inf;
  m = sc.next_int();
  for (int i = 1; i <= m; i++)
    b[i] = sc.next_int();
  std::sort(b + 1, b + m + 1);

  for (int i = 1; i <= n; i++)
    if (~a[i])
    {
      int j =
          static_cast<int>(std::lower_bound(f + 1, f + n + 1, a[i]) - f - 1);
      l[i] = j + 1, p[i] = g[j], f[j + 1] = a[i], g[j + 1] = i;
    }
    else
      for (int j = n, o = m; o; o--)
      {
        while (f[j] >= b[o])
          --j;
        f[j + 1] = b[o], g[j + 1] = i;
      }

  int i = l[n], j = n, x = a[n];
  while (i--)
  {
    if (~a[j])
    {
      if (!~a[p[j]])
        get(p[j], a[j], x);
      else
        x = a[p[j]];
      j = p[j];
    }
    else
    {
      bool ok = 0;
      for (int s = j - 1; s; s--)
        if (~a[s] && l[s] == i && a[s] < x)
        {
          x = a[j = s], ok = 1;
          break;
        }
      if (ok)
        continue;
      for (int s = j - 1; s; s--)
        if (!~a[s])
        {
          get(s, x, x), j = s;
          break;
        }
    }
  }

  for (int i = 1, j = 1; i <= n; i++)
    if (!~a[i])
    {
      if (ans[i])
        continue;
      while (v[j])
        ++j;
      v[j] = 1, ans[i] = b[j];
    }
    else
      ans[i] = a[i];

  for (int i = 1; i < n; i++)
    printf("%d%c", ans[i], " \n"[i == n]);

  return 0;
}
