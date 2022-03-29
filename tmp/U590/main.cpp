#include <bits/stdc++.h>

int main()
{
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<std::pair<int, int>> a(n);
  for (int i = 0; i < n; i++)
    scanf("%d%d", &a[i].first, &a[i].second);
  std::sort(a.begin(), a.end());

  std::priority_queue<int, std::vector<int>, std::greater<int>> que;
  auto a_it = a.begin();
  int ans = 0;
  for (int i = 0; a_it != a.end() || !que.empty(); i++)
  {
    if (que.empty()) i = a_it->first;
    while (a_it != a.end() && a_it->first == i)
    {
      que.push(a_it->second);
      a_it++;
    }
    for (int j = 0; j < m && !que.empty(); j++)
    {
      int ddl = que.top(); que.pop();
      ans = std::max(ans, i - ddl);
    }
  }
  std::cout << ans << std::endl;
  return 0;
}
