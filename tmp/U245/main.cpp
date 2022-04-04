#include <bits/stdc++.h>

const int N = 100005;

struct minmax_que
{
  int l = 0, r = 0;
  std::deque<std::pair<int, int>> min;
  std::deque<std::pair<int, int>> max;

  void push(int val)
  {
    while (!min.empty() && min.back().first > val)
      min.pop_back();
    min.emplace_back(val, r);
    while (!max.empty() && max.back().first < val)
      max.pop_back();
    max.emplace_back(val, r);
    r++;
  }

  int size()
  {
    return r - l;
  }

  int det()
  {
    return max.front().first - min.front().first;
  }

  void pop()
  {
    if (min.front().second == l)
      min.pop_front();
    if (max.front().second == l)
      max.pop_front();
    l++;
  }
};

int a[N], n;
int ans[N];

void solve(int x)
{
  minmax_que que;
  int max_len = 0;
  for (int i = 0; i < n; i++)
  {
    que.push(a[i]);
    while (que.det() > x)
      que.pop();
    max_len = std::max(max_len, que.size());
  }
  for (int i = 2; i <= max_len; i++)
    ans[i] = std::min(ans[i], x);
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%d", &a[i]);
  std::fill(ans + 2, ans + n + 1, 0x3f3f3f3f);
  for (int x = 0; x <= 1050000; x = std::max(x + 1, static_cast<int>(x * 1.05)))
    solve(x);
  for (int i = 2; i <= n; i++)
    printf("%d\n", ans[i]);
  return 0;
}
