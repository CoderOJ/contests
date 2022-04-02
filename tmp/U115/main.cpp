#include <bits/stdc++.h>

const int N = 100005;
const int B = 20;
int f[N][B], n;
std::vector<int> e[N];

void init_f()
{
  for (int i = 0; i + 1 < B; i++)
    for (int u = 1; u <= n; u++)
      f[u][i + 1] = f[f[u][i]][i];
}

int in_deg[N];
bool is_cyc[N];
void init_is_cyc()
{
  for (int i = 1; i <= n; i++) in_deg[f[i][0]]++;
  std::queue<int> que;
  for (int i = 1; i <= n; i++) if (in_deg[i] == 0) que.push(i);
  while (!que.empty())
  {
    int u = que.front(); que.pop();
    in_deg[f[u][0]]--;
    if (in_deg[f[u][0]] == 0) que.push(f[u][0]);
  }
  for (int i = 1; i <= n; i++) is_cyc[i] = (in_deg[i] > 0);
}

int dep[N];
bool dep_vis[N];
void dfs_init_dep(int u)
{
  dep_vis[u] = true;
  for (int v : e[u]) if (!dep_vis[v])
  {
    dep[v] = dep[u]  +1;
    dfs_init_dep(v);
  }
}

void init_dep()
{
  for (int i = 1; i <= n; i++)
    if (is_cyc[i] && !dep_vis[i])
      dfs_init_dep(i);
}

std::vector<std::vector<int>> dfn;
bool dfn_vis[N];
void dfs_init_dfn(int u)
{
  dfn_vis[u] = true;
  dfn.back().push_back(u);  
  for (int v : e[u]) if (!dfn_vis[v] && !is_cyc[v]) dfs_init_dfn(v);
  for (int v : e[u]) if (!dfn_vis[v] && is_cyc[v]) dfs_init_dfn(v);
}

void init_dfn()
{
  for (int i = 1; i <= n; i++)
    if (is_cyc[i] && !dfn_vis[i])
    {
      dfn.push_back({});
      dfs_init_dfn(i);
    }
}

int forward(int u, int d)
{
  if (d <= 0) return u;
  for (int i = 0; i < B; i++)
    if (d & (1 << i))
      u = f[u][i];
  return u;
}

int get_fw(int u)
{
  static int mem[N];

  if (mem[u] != 0) return mem[u];
  if (dep[f[u][0]] > dep[u])
    return mem[u] = dep[f[u][0]] - dep[u] + 1;
  else if (is_cyc[u])
    return mem[u] = get_fw(f[u][0]);
  else
    return mem[u] = get_fw(f[u][0]) + 1;
}

int get_cyc(int u)
{
  static int mem[N];

  if (mem[u] != 0) return mem[u];
  if (is_cyc[u]) return mem[u] = u;
  else return mem[u] = get_cyc(f[u][0]);
}

int get_fw(int u, int b)
{
  if (is_cyc[b])
  {
    int r = get_cyc(u);
    if (dep[r] >= dep[b]) return dep[u] - dep[b] + 1;
    else return get_fw(u) - (dep[b] - dep[r] - 1);
  }
  else
  {
    int r = forward(u, dep[u] - dep[b]);
    if (r == b) return dep[u] - dep[b] + 1;
    else return get_fw(u);
  }
}

int p_max[N], p_min[N];

int main()
{
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
  {
    scanf("%d", &f[i][0]);
    e[f[i][0]].push_back(i);
  }

  init_f();
  init_is_cyc();
  init_dep();
  init_dfn();

  for (auto &d : dfn)
  {
    for (size_t i = 0; i < d.size(); i++)
    {
      p_max[d[i]] = d[(i + 1) % d.size()];
      p_min[d[(i + 1) % d.size()]] = d[i];
    }
  }
  int64_t p_max_ans = 0;
  int64_t p_min_ans = 0;
  for (int i = 1; i <= n; i++)
  {
    p_max_ans += get_fw(i, p_max[i]);
    // printf("get_fw(%d, %d) = %d\n", i, p_max[i], get_fw(i, p_max[i]));
    p_min_ans += get_fw(i, p_min[i]);
    // printf("get_fw(%d, %d) = %d\n", i, p_min[i], get_fw(i, p_min[i]));
  }
  printf("%" SCNi64 "\n", p_min_ans);
  for (int i = 1; i <= n; i++) printf("%d ", p_min[i]);
  puts("");
  printf("%" SCNi64 "\n", p_max_ans);
  for (int i = 1; i <= n; i++) printf("%d ", p_max[i]);
  puts("");

  return 0;
}
