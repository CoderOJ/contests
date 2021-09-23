#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 1005;
std::vector<int> e[N];

int dep[N];
bool ban[N];

void dfs(int u, int f)
{
  dep[u] = 0;
  for (int v: e[u]) if (v != f && !ban[v])
  {
    dfs(v, u);
    check_max(dep[u], dep[v] + 1);
  }
}

std::pair<int,int> find_far(int u, int f)
{
  std::pair<int,int> res(0, u);
  for (int v : e[u]) if (!ban[v] && v != f)
    check_max(res, find_far(v, u));
  res.first++;
  return res;
}

std::vector<int> ans;

void dfs_fp(int u, int f)
{
  ans.push_back(u);
  std::sort(e[u].begin(), e[u].end(), [](int a, int b) { return dep[a] < dep[b]; });
  cm::once_t rec;
  for (int v: e[u]) if (!ban[v] && v != f)
  {
    if (!rec()) ans.push_back(u);
    dfs_fp(v, u);
  }
}

int main()
{
  int n = sc.next_int();
  int m = sc.next_int();
  if (m >= n) { puts("NO"); return 0; }
  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int();
    int v = sc.next_int();
    e[u].push_back(v);
    e[v].push_back(u);
  }
  for (int u = 1; u <= n; u++)
  {
    dfs(u, u);
    if (std::count_if(e[u].begin(), e[u].end(), [](int v) { return dep[v] >= 2; }) >= 3)
    {
      puts("NO");
      return 0;
    }
  }
  puts("YES");

  if (n == 1) { puts("1\n1"); }
  else if (n == 2) { puts("2\n1 1"); }
  else
  {
    for (int u = 1; u <= n; u++)
      if (e[u].size() == 1)
        ban[u] = true;
    int root = find_far(1, 0).second;
    see(root);
    dfs(root, 0);
    dfs_fp(root, 0);

    auto ans_r = ans;
    std::reverse(ans_r.begin(), ans_r.end());
    ans += std::move(ans_r);

    printf("%zu\n", ans.size());
    for (int u : ans) printf("%d ", u);

  }
  return 0;
}

