#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

long long   m[110], f[125010];
int         p[110], v[110], p1[110], la[110];
inline bool cmp(int a, int b)
{
  return v[a] * m[b] > v[b] * m[a];
}
int main()
{
  int n   = sc.next_int();
  int x   = sc.next_int();
  int d   = sc.next_int();
  int num = 0, ans = 0;
  v[1]  = 1;
  p1[1] = 1;
  m[1]  = sc.next_int();
  for (int i = 2; i <= n; i++)
  {
    m[i]  = sc.next_int();
    p[i]  = sc.next_int();
    v[i]  = 1;
    p1[i] = i;
  }

  for (int i = n; i >= 2; i--)
  {
    m[p[i]] += m[i];
    v[p[i]] += v[i];
    num += v[i] * std::min(n, d);
    la[i] = std::max(d - n, 0);
  }

  la[1] = x;
  std::sort(p1 + 1, p1 + n + 1, cmp);
  for (int i = 1; i <= num; i++)
    f[i] = 1ll << 60;
  for (int i = 2; i <= n; i++)
  {
    for (int j = num; j >= 0; j--)
      if (f[j] < (1ll << 60))
      {
        for (int k = 1; k <= std::min(n, d); k++)
          f[j + k * v[i]] = std::min(f[j + k * v[i]], f[j] + k * m[i]);
      }
  }

  for (int i = 0; i <= num; i++)
    if (f[i] <= x)
    {
      int x1 = x - f[i];
      int vv = i;
      for (int j = 1; j <= n; j++)
      {
        int x2 = std::min(x1 / m[p1[j]], 1ll * la[p1[j]]);
        vv += x2 * v[p1[j]];
        x1 -= x2 * m[p1[j]];
      }
      ans = std::max(ans, vv);
    }

  printf("%d\n", ans);
}
