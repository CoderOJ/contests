#include <bits/stdc++.h>

const int N = 505;
const int M = 2500005;
int a[N], n, m, k;

void construct(const std::vector<int> &ids)
{
  std::set<std::pair<int, int>> candi;
  for (int i : ids) candi.emplace(a[i], i);
  while (!candi.empty())
  {
    const auto [fv, fi] = *candi.begin(); candi.erase(candi.begin());
    if (fv == 0) { continue; }
    else if (fv < k) { 
      const auto [tv, ti] = *std::prev(candi.end()); candi.erase(std::prev(candi.end()));
      printf("%d %d %d %d\n", fi + 1, fv, ti + 1, k - fv); candi.emplace(tv - (k - fv), ti); }
    else {
      printf("%d %d\n", fi + 1, k); candi.emplace(fv - k, fi); }
  }
}

std::bitset<M> b[N];

void rmain()
{
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 0; i < n; i++) scanf("%d", &a[i]);
  if (m >= n - 1)
  {
    std::vector<int> ids(n); for (int i = 0; i < n; i++) ids.push_back(i);
    construct(ids);
  }
  else
  {
    int kp = -1;
    b[0].reset(); b[0].set(0);
    for (int i = 0; i < n; i++)
    {
      b[i + 1] = (b[i] << k) | (b[i] << a[i]);
      if (b[i + 1].test(i * k)) { kp = i; break; }
    }
    if (kp == -1)
    {
      puts("-1");
    }
    else
    {
      std::vector<int> ida, idb;
      for (int i = kp + 1; i < n; i++) idb.push_back(i);
      for (int v = kp * k; v > 0; kp--)
      {
        // printf("kp = %d, v = %d\n", kp, v);
        if (v >= k && b[kp][v - k]) { v -= k; idb.push_back(kp); }
        else { ida.push_back(kp); v -= a[kp]; }
      }
      construct(ida);
      construct(idb);
    }
  }
}

int main()
{
  int t; scanf("%d", &t);
  for (int i = 0; i < t; i++) rmain();
  return 0;
}
