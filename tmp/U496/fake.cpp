#include <bits/stdc++.h>

const int N = 1000005;
std::set<std::pair<int, int>> e[N];
int r[N], deg[N];
int n;

void solve()
{  
  scanf("%d", &n);
  if (n == 3)
  {
    puts("-1");
    return;
  }

  for (int i = 1; i <= n * 2; i++) e[i].clear(), r[i] = -1, deg[i] = 0;

  for (int i = 0; i < n; i++)
  {
    int u = i + 1, v = (i + 1) % n + 1;
    e[u].insert({v, i}); e[v].insert({u, i});
    r[i] = -1;
  }
  for (int i = 0; i < n - 3; i++)
  {
    int u, v; scanf("%d%d", &u, &v);
    e[u].insert({v, n + i}); e[v].insert({u, n + i});
    r[n + i] = -1;
  }
  std::queue<int> que;
  for (int i = 1; i <= n; i++)
    if (e[i].size() <= 2)
      que.push(i);
  std::vector<std::pair<int, int>> ans;
  for (int i = 0; i < n - 2; i++)
  {
    int u = que.front(); que.pop();
    const auto [v1, i1] = *e[u].begin();
    const auto [v2, i2] = *std::next(e[u].begin());
    int i12 = e[v1].lower_bound({v2, 0})->second;
    // printf("extend %d %d %d %d %d\n", u, v1, v2, r[i1], r[i2]);
    if (r[i12] != -1) ans.push_back({v1, r[i12]}), r[i12] = -1;
    if (r[i1] == -1 && r[i2] == -1) r[i12] = u;
    else if (r[i1] == -1 && r[i2] != -1) ans.push_back({u, v2}), ans.push_back({r[i2], v2});
    else if (r[i1] != -1 && r[i2] == -1) ans.push_back({u, v1}), ans.push_back({r[i1], v1});
    else ans.push_back({r[i1], u}), ans.push_back({r[i2], u}), r[i12] = u;
    e[v1].erase({u, i1}); if (e[v1].size() <= 2) que.push(v1);
    e[v2].erase({u, i2}); if (e[v2].size() <= 2) que.push(v2);
    e[u].clear();
  }
  for (const auto &[u, v] : ans) deg[u]++, deg[v]++;
  int v1 = que.front(); que.pop();
  int v2 = que.front(); que.pop();
  int i12 = e[v1].lower_bound({v2, 0})->second;
  printf("last: %d %d %d %d, deg = %d %d\n", v1, v2, i12, r[i12], deg[v1], deg[v2]);
  if (r[i12] != -1 && deg[v1] == 0 && deg[v2] == 0)
  {
    ans.push_back({r[i12], v1});
    ans.push_back({r[i12], v2});
  }
  else
  {
    ans.push_back({v1, v2});
    if (r[i12] != -1) ans.push_back({deg[v1] == 0 ? v2 : v1, r[i12]});
  }
  for (const auto &[u, v] : ans) printf("%d %d\n", u, v);
}

int main()
{
  // int t; scanf("%d", &t);
  int t = 1;
  for (int i = 0; i < t; i++) solve();
  return 0;
}
