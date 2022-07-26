#include <bits/stdc++.h>

constexpr int N = 200005;

int a[N], b[N], px[N], py[N], n, m;
int tx, ty;

int64_t sx[N], sy[N];

int64_t get_xsum(int l, int r)
{
  return sx[r] - sx[l - 1];
}

int64_t get_mis(int x, int y, bool has_cut)
{
  if (px[x] < y)
  {
    int d = 0;
    if (has_cut)
    {
      if (tx > x && ty > y)
        d = 1;
      else if (tx <= x && ty <= y && ty <= px[tx])
        d = 1;
    }
    int l = py[y];
    return 1ll * l * y + get_xsum(l + 1, x) + 1ll * (n - x) * (m - y) - d;
  }
  else
  {
    int d = 0;
    if (has_cut)
    {
      if (tx <= x && ty <= y)
        d = 1;
      else if (tx > x && ty > y && ty > px[tx])
        d = 1;
    }
    int r = py[y];
    return 1ll * x * y + (1ll * (r - x) * m - get_xsum(x + 1, r))
         + 1ll * (n - r) * (m - y) - d;
  }
}

bool check(int x)
{
  px[0] = m;
  for (int i = 1; i <= n; i++)
    for (px[i] = px[i - 1]; px[i] && a[i] + b[px[i]] > x;)
      px[i] -= 1;
  for (int i = 1; i <= n; i++)
    sx[i] = sx[i - 1] + px[i];

  py[0] = n;
  for (int i = 1; i <= m; i++)
    for (py[i] = py[i - 1]; py[i] && a[py[i]] + b[i] > x;)
      py[i] -= 1;

  int64_t a0 = std::max(get_xsum(1, n), (int64_t)n * m - get_xsum(1, n));
  int64_t a1 = std::max(
      get_xsum(1, n) - (ty <= px[tx]),
      (int64_t)n * m - get_xsum(1, n) - (ty > px[tx]));
  {
    int p = 1;
    for (int i = 1; i <= n; i++)
    {
      while (p < m && get_mis(i, p, false) <= get_mis(i, p + 1, false))
        p++;
      a0 = std::max(a0, get_mis(i, p, false));
    }
  }

  {
    int p = 1;
    for (int i = 1; i <= n; i++)
    {
      while (p < m && get_mis(i, p, true) <= get_mis(i, p + 1, true))
        p++;
      a1 = std::max(a1, get_mis(i, p, true));
    }
  }
  return a0 != a1 + 1;
}

int main()
{
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  for (int i = 1; i <= m; i++)
    scanf("%d", &b[i]);

  tx = a[1];
  ty = b[1];
  std::sort(a + 1, a + n + 1);
  std::sort(b + 1, b + m + 1);
  tx = (int)(std::lower_bound(a + 1, a + n + 1, tx) - a);
  ty = (int)(std::lower_bound(b + 1, b + m + 1, ty) - b);

  int l = a[1] + b[1], r = a[tx] + b[ty];
  int ans = r;
  while (l <= r)
  {
    int mid = (l + r) >> 1;
    if (check(mid))
      r = mid - 1, ans = mid;
    else
      l = mid + 1;
  }
  printf("%d\n", ans);

  return 0;
}
