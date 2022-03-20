#include <bits/stdc++.h>

const int N = 50;

using inter_t = std::pair<int, int>;

int a[N], n, m;
inter_t inters[N];
int intersect_cnt[N];
int cross_mask[N];
int cross_cnt[N];

int ans;
void dfs(int p, int mask, int sum)
{
  if (sum < ans)
  {
    if (p == m)
    {
      ans = sum;
    }
    else
    {
      int s0_cnt = __builtin_popcount(mask & cross_mask[p]);
      int s1_cnt = cross_cnt[p] - s0_cnt;
      dfs(p + 1, mask | (1 << p), sum + std::min(s0_cnt, intersect_cnt[p] - s0_cnt));
      if (p != 0)
        dfs(p + 1, mask, sum + std::min(s1_cnt, intersect_cnt[p] - s1_cnt));
    }
  }
}

void rmain()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++) scanf("%d", &a[i]);
  
  m = 0;
  for (int v = 1; v <= n; v++)
  {
    std::vector<int> occurs;
    for (int i = 0; i < n; i++) if (a[i] == v) occurs.push_back(i);
    if (occurs.size() == 2) inters[m++] = {occurs[0], occurs[1]};
  }
  std::sort(inters, inters + m);

  for (int i = 0; i < m; i++)
  {
    intersect_cnt[i] = 0;
    cross_mask[i] = 0;
    cross_cnt[i] = 0;
    for (int j = 0; j < i; j++)
    {
      if (inters[j].second > inters[i].first) {
        intersect_cnt[i] += 1; }
      if (inters[j].second > inters[i].first && inters[j].second < inters[i].second) {
        cross_mask[i] |= (1 << j);
        cross_cnt[i] += 1; }
    }
  }

  ans = 0x3f3f3f3f;
  dfs(0, 0, 0);
  std::cout << ans << std::endl;
}

int main()
{
  int t; scanf("%d", &t);
  for (int i = 0; i < t; i++)
    rmain();
  return 0;
}
