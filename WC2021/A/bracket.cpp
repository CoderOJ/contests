#include <bits/stdc++.h>

const int N = 300005;

std::unordered_map<int, int> e[N];
int n, m, k;

std::queue<std::pair<int, int>> task_list;

int p[N], size[N];
int get(int u)
{
  return u == p[u] ? u : p[u] = get(p[u]);
}

int main()
{
  scanf("%d%d%d", &n, &m, &k);
  for (int i = 1; i <= n; i++) p[i] = i, size[i] = 1;
  for (int i = 0; i < m; i++)
  {
    int u, v, w; scanf("%d%d%d", &v, &u, &w);
    if (e[u].count(w))
      task_list.emplace(e[u][w], v);
    else
      e[u][w] = v;
  }
  while (!task_list.empty())
  {
    auto [u, v] = task_list.front();
    // printf("%d %d\n", u, v);
    task_list.pop();
    u = get(u), v = get(v);
    if (u != v)
    {
      if (e[u].size() < e[v].size())
        std::swap(u, v);
      p[v] = u, size[u] += size[v];
      for (const auto &[vc, vv] : e[v])
      {
        if (e[u].count(vc))
          task_list.emplace(e[u][vc], vv);
        else
          e[u][vc] = vv;
      }
    }
  }
  int64_t ans = 0;
  for (int i = 1; i <= n; i++)
    if (p[i] == i)
      ans += (int64_t)(size[i] - 1) * size[i] / 2;
  std::cout << ans << std::endl;
  return 0;
}
