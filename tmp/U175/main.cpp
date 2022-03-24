#include <bits/stdc++.h>

const int N = 100005;

uint64_t get_seed()
{
  int *p = new int;
  delete p;
  return reinterpret_cast<uint64_t>(p);
}

auto w = []{
  std::mt19937_64 rd(get_seed());
  std::array<uint64_t, N> res;
  for (int i = 0; i < N; i++)
    res[i] = rd();
  return res;
}();

int n, m;
std::vector<int> e[N];
uint64_t ew[N];
bool ok[N];

void rmain()
{
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= n; i++)
  {
    e[i].clear();
    ew[i] = 0;
    ok[i] = false;
  }
  for (int i = 0; i < m; i++)
  {
    int u, v; scanf("%d%d", &u, &v);
    e[u].push_back(v); e[v].push_back(u);
    ew[u] += w[v]; ew[v] += w[u];
  }

  for (int u = 1; u <= n; u++)
    if (e[u].size() == 1)
    {
      ok[u] = true;
      ok[e[u][0]] = true;
    }

  for (int u = 1; u <= n; u++)
    for (int v : e[u])
      if (ew[u] - w[v] == ew[v] - w[u])
      {
        ok[u] = true;
        ok[v] = true;
      }

  {
    std::vector<int> us(n);
    for (int i = 0; i < n; i++)
      us[i] = i + 1;
    std::sort(us.begin(), us.end(), [](int u, int v) { 
      return ew[u] < ew[v];
    });
    for (auto l = us.begin(), r = l; l != us.end(); l = r)
    {
      while (r != us.end() && ew[*r] == ew[*l]) r++;
      if (std::distance(l, r) > 1)
        for (auto i = l; i != r; i++)
          ok[*i] = true;
    }
  }

  int ans = static_cast<int>(std::count(ok + 1, ok + n + 1, true));
  std::cout << ans << std::endl;
  for (int u = 1; u <= n; u++)
    if (ok[u])
      std::cout << u << " ";
  std::cout << std::endl;
}

int main()
{
  int t; scanf("%d", &t);
  for (int i = 0; i < t; i++)
    rmain();
  return 0;
}
