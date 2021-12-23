#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 3005;

int r, c, n, k;
int cnt[N], pre[N], nxt[N];
int f[N], g[N];

struct point_t
{
  int x, y;
} a[N];

bool operator<(const point_t &u, const point_t &v)
{
  return u.x == v.x ? u.y < v.y : u.x < v.x;
}

int main()
{
  r = sc.next_int();
  c = sc.next_int();
  n = sc.next_int();
  k = sc.next_int();
  for (int i = 0; i < n; i++)
  {
    a[i].x = sc.next_int();
    a[i].y = sc.next_int();
  }
  std::sort(a, a + n);
  cnt[0] = cnt[c + 1] = 1e9;

  long long ans = 0, now = 0;
  for (int xl = 1; xl <= r; xl++)
  {
    int l = 0, last = 0;
    for (; l < n && a[l].x < xl; l++)
      ;
    for (int i = l; i < n; i++)
      cnt[a[i].y]++;

    f[0] = 0;
    g[0] = cnt[0];
    now  = 0;

    for (int y = 1; y <= c + 1; y++)
    {
      if (cnt[y] == 0)
        continue;
      nxt[last] = y;
      pre[y]    = last;
      now += f[last] * (y - last);
      f[y] = f[last];
      g[y] = g[last] + cnt[y];
      for (; g[y] - cnt[f[y]] >= k; g[y] -= cnt[f[y]], f[y] = nxt[f[y]])
        ;
      last = y;
    }

    for (int xr = r, i = n - 1; xr >= xl; xr--)
    {
      ans += now;
      for (; i >= l && a[i].x == xr; i--)
      {
        cnt[a[i].y]--;
        for (int y = a[i].y; y <= c + 1; y = nxt[y])
        {
          if (f[y] > a[i].y)
            break;
          now -= f[y] * (nxt[y] - y);
          g[y]--;
          for (; g[y] < k; f[y] = pre[f[y]], g[y] += cnt[f[y]])
            ;
          now += f[y] * (nxt[y] - y);
        }
        int y = a[i].y;
        if (cnt[y] == 0)
        {
          nxt[pre[y]] = nxt[y];
          pre[nxt[y]] = pre[y];
        }
      }
    }
  }

  std::cout << ans << std::endl;

  return 0;
}
