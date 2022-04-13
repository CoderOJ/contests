#include <bits/stdc++.h>

int main()
{
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  if (k == 1)
  {
    puts("-1");
  }
  else if (k == 2)
  {
    if (n == 1 || m == 1)
    {
      for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
          printf("%d %d\n", i, j);
    }
    else
    {
      puts("-1");
    }
  }
  else
  {
    std::vector<std::pair<int, int>> a, b;
    if (n % 2 == 0)
    {
      for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
          ((i + j / 2) % 2 ? a : b).emplace_back(i, j);
    }
    else
    {
      for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
          ((i / 2 + j) % 2 ? a : b).emplace_back(i, j);
    }
    if (a.size() < b.size())
      std::swap(a, b);
    for (size_t i = 0; i < a.size(); i++)
    {
      if (i < a.size()) printf("%d %d\n", a[i].first + 1, a[i].second + 1);
      if (i < b.size()) printf("%d %d\n", b[i].first + 1, b[i].second + 1);
    }
  }
  return 0;
}
