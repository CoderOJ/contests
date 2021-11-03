#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <cstring>
#include <iostream>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#define int long long

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 200005;

int n, m;
int ans = 0;
int a[N];
int d1[N], d2[N], pre[N], ed[N], b[N];
int dis(int x, int y, int op)
{
  if (op == 1)
  {
    if (y > x)
    {
      return y - x;
    }
    else
    {
      return y + n - x;
    }
  }
  else
  {
    if (y < x)
      return x - y;
    return x + n - y;
  }
}
signed main()
{
  n = sc.next_int();
  m = sc.next_int();
  for (int i = 1; i <= m; i++)
    a[i] = sc.next_int();

  for (int i = 1; i <= m; i++)
  {
    d1[i] = dis(0, a[i], 1);
    d2[i] = dis(0, a[i], 0);
  }
  for (int i = 1; i <= m; i++)
    pre[i] = pre[i - 1] + d1[i];
  for (int i = m; i >= 1; i--)
    ed[i] = ed[i + 1] + d2[i];

  for (int i = 1; i <= m; i++)
  {
    int rem = m - i + 1;
    int fin = rem / 2 + i;
    if (rem & 1)
      ans = std::max(ans, pre[fin - 1] * 2 + d1[fin] + ed[fin + 1] * 2 -
                              pre[i - 1] * 2);
    else
      ans = std::max(ans, pre[fin - 1] * 2 + ed[fin + 1] * 2 + d2[fin] -
                              pre[i - 1] * 2);
  }

  memset(pre, 0, sizeof(pre));
  memset(ed, 0, sizeof(ed));
  memset(d1, 0, sizeof(d1));
  memset(d2, 0, sizeof(d2));
  for (int i = 1; i <= m; i++)
    b[i] = a[i];
  for (int i = 1; i <= m; i++)
    a[i] = b[m - i + 1];
  for (int i = 1; i <= m; i++)
  {
    d1[i] = dis(0, a[i], 0);
    d2[i] = dis(0, a[i], 1);
  }
  for (int i = 1; i <= m; i++)
    pre[i] = pre[i - 1] + d1[i];
  for (int i = m; i >= 1; i--)
    ed[i] = ed[i + 1] + d2[i];
  for (int i = 1; i <= m; i++)
  {
    int rem = m - i + 1;
    int fin = rem / 2 + i;
    if (rem & 1)
      ans = std::max(ans, pre[fin - 1] * 2 + d1[fin] + ed[fin + 1] * 2 -
                              pre[i - 1] * 2);
    else
      ans = std::max(ans, pre[fin - 1] * 2 + ed[fin + 1] * 2 + d2[fin] -
                              pre[i - 1] * 2);
  }

  std::cout << ans;
  return 0;
}
