#include <bits/stdc++.h>

#define rep(i, n) for (int i = 0; i < n; i++)

const int N = 150'005;

struct node_t
{
  int x, y, z;
};

bool ban[N];
node_t a[N];
int n;

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].z);

  std::vector<int> x(n); rep (i, n) x[i] = i; std::sort(x.begin(), x.end(), [](int x, int y) { return a[x].x != a[y].x ? a[x].x > a[y].x : x < y; });
  std::vector<int> y(n); rep (i, n) y[i] = i; std::sort(y.begin(), y.end(), [](int x, int y) { return a[x].y != a[y].y ? a[x].y > a[y].y : x < y; });
  std::vector<int> z(n); rep (i, n) z[i] = i; std::sort(z.begin(), z.end(), [](int x, int y) { return a[x].z != a[y].z ? a[x].z > a[y].z : x < y; });

  int xx = 0, yy = 0, zz = 0;
  while (true)
  {
    // printf("%d %d %d\n", x[xx], y[yy], z[zz]);
    if (xx == n || yy == n || zz == n) break;
    if (ban[x[xx]]) { xx++; continue; }
    if (ban[y[yy]]) { yy++; continue; }
    if (ban[z[zz]]) { zz++; continue; }
    auto valid = [&](int id) { 
      return 
        (a[x[xx]].x == a[id].x) +
        (a[y[yy]].y == a[id].y) +
        (a[z[zz]].z == a[id].z)
      == 1;
    };
    if (!valid(x[xx])) ban[x[xx]] = true;
    else if (!valid(y[yy])) ban[y[yy]] = true;
    else if (!valid(z[zz])) ban[z[zz]] = true;
    else break;
  }
  
  if (xx == n || yy == n || zz == n) puts("-1");
  else printf("%d\n", a[x[xx]].x + a[y[yy]].y + a[z[zz]].z);

  return 0;
}
