#include <stdio.h>

#define N 200005

int h, w, n, u, d, l, r, x, y;
char s[N], t[N];
int min(int a, int b) { return a < b ? a : b; }
int max(int a, int b) { return a > b ? a : b; }

int main()
{
  scanf("%d%d%d%d%d%s%s", &h, &w, &n, &x, &y, s + 1, t + 1);
  d = h, r = w, l = u = 1;
  for (int i = n; i; --i)
  {
    if (t[i] == 'U')
      d = min(d + 1, h);
    else if (t[i] == 'D')
      u = max(u - 1, 1);
    else if (t[i] == 'L')
      r = min(r + 1, w);
    else
      l = max(l - 1, 1);
    if (s[i] == 'U')
      ++u;
    else if (s[i] == 'D')
      --d;
    else if (s[i] == 'L')
      ++l;
    else
      --r;
    if (u > d || l > r)
    {
      puts("NO");
      return 0;
    }
  }
  if (x < u || x > d || y < l || y > r)
    puts("NO");
  else
    puts("YES");
  return 0;
}
