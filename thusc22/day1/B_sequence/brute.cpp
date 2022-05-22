#include <bits/stdc++.h>

const int N = 100005;
int       a[N], b[N], n, m;

int main()
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++)
    scanf("%d", &a[i]);
  for (int i = 0; i < m; i++)
    scanf("%d", &b[i]);

  int64_t ans = std::numeric_limits<int64_t>::min();
  for (int l = 0; l < n; l++)
  {
    std::priority_queue<int, std::vector<int>, std::greater<int>> h1;
    std::priority_queue<int, std::vector<int>, std::less<int>>    h2;
    int64_t                                                       h1sum = 0;

    for (int i = 0; i < m; i++)
      h2.emplace(b[i]);

    for (int r = l; r < n; r++)
    {
      h2.emplace(a[r]);
      h1.emplace(h2.top());
      h1sum += h2.top();
      h2.pop();
      ans = std::max(ans, h1sum);
    }
  }

  std::cout << ans << std::endl;

  return 0;
}
