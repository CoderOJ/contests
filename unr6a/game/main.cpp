#include <bits/stdc++.h>

const int N = 200005;

int a[N];
int n, q;

int main()
{
  scanf("%d%d", &n, &q);
  for (int i = 0; i < n; i++)
    scanf("%d", &a[i]);

  for (int i = 0; i < q; i++)
  {
    int l, r;
    scanf("%d%d", &l, &r);
    l -= 1;

    int64_t ans = std::accumulate(a + l, a + r, (int64_t)0);

    std::priority_queue<int, std::vector<int>, std::greater<int>> que;
    for (int i = l; i + 2 <= r; i += 2)
    {
      que.emplace(a[i]);
      que.emplace(a[i + 1]);
      ans -= que.top();
      que.pop();
    }

    std::cout << ans << std::endl;
  }

  return 0;
}
