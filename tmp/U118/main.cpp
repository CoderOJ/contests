#include <bits/stdc++.h>

const int N = 100005;
int a[N], b[N], ap[N], bp[N];
int n, m, q;

int main()
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++) scanf("%d", &a[i]);
  for (int i = 0; i < m; i++) scanf("%d", &b[i]);
  for (int i = 1; i < n; i++) ap[i] = ap[i - 1] + (a[i] != a[i - 1]);
  for (int i = 1; i < m; i++) bp[i] = bp[i - 1] + (b[i] != b[i - 1]);
  ap[n] = ap[n - 1] + (a[0] != a[n - 1]);  
  bp[m] = bp[m - 1] + (b[0] != b[m - 1]);  

  scanf("%d", &q);
  for (int i = 0; i < q; i++)
  {
    int ax, ay, bx, by;
    scanf("%d%d%d%d", &ax, &ay, &bx, &by);
    ax--, ay--, bx--, by--;
    if (ax > bx) std::swap(ax, bx);
    if (ay > by) std::swap(ay, by);
    int dx = ap[bx] - ap[ax];
    int dy = bp[by] - bp[ay];
    printf("%d\n", std::min(dx, ap[n] - dx) + std::min(dy, bp[m] - dy));
  }
  return 0;
}
