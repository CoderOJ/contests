#include <bits/stdc++.h>

int init_io = []{
#ifndef CM_DEBUG
  freopen("discuss.in", "r", stdin);
  freopen("discuss.out", "w", stdout);
#endif
  return 0;
}();

const int N = 1000005;
std::vector<int> a[N];
std::vector<int> b[N];
int n;

bool is_subset(int i, int j)
{
  // printf("is_subset(%d, %d)\n", i, j);
  for (int x : a[i])
  {
    auto y = std::lower_bound(a[j].begin(), a[j].end(), x);
    if (y == a[j].end() || *y != x)
      return false;
  }
  return true;
}

void rmain()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++) a[i].clear(), b[i].clear();
  for (int i = 0; i < n; i++)
  {
    int m; scanf("%d", &m);
    for (int j = 0; j < m; j++)
    {
      int x; scanf("%d", &x); x--;
      a[i].push_back(x);
      b[x].push_back(i);
    }
    std::sort(a[i].begin(), a[i].end());
  }
  std::set<std::pair<int, int>> cache;
  for (int i = 0; i < n; i++)
  {
    std::stable_sort(b[i].begin(), b[i].end(), [](int x, int y) {
      return a[x].size() < a[y].size();
    });
    for (size_t j = 0; j + 1 < b[i].size(); j++) 
    {
      int x = b[i][j], y = b[i][j + 1];
      if (!cache.count({x, y}))
      {
        if (is_subset(x, y))
        {
          cache.insert({x, y});
        }
        else
        {
          puts("YES");
          printf("%d %d\n", x + 1, y + 1);
          return;
        }
      }
    }
  }
  puts("NO");
}

int main()
{
  int t; scanf("%d", &t);
  for (int i = 0; i < t; i++)
    rmain();
  return 0;
}
