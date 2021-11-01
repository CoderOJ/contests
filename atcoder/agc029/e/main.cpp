#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 200005;
std::vector<int> e[N];
int n;

int dep[N], max_a[N], max_b[N], ans[N], from[N];
void dfs(int u, int f)
{
  dep[u] = dep[f] + 1;
  max_a[u] = max_a[f], max_b[u] = max_b[f];
  if (u > max_a[u])
  {
    max_b[u] = max_a[u], max_a[u] = u;
    from[u] = u;
  }
  else if (u > max_b[u])
    max_b[u] = u;

  if (dep[max_b[u]] > dep[max_a[u]])
    ans[from[u]]++;
  else
    ans[max_a[u]]++;

  for (int v : e[u])
    if (v != f)
    {
      from[v] = max_a[u] == u ? v : from[u];
      dfs(v, u);
    }
}

void dfs_ans(int u, int f)
{
  for (int v : e[u])
    if (v != f)
    {
      ans[v] += ans[u];
      dfs_ans(v, u);
    }
}

int main()
{
  n = sc.next_int();
  for (int i = 1; i < n; i++)
  {
    int u = sc.next_int(), v = sc.next_int();
    e[u].push_back(v);
    e[v].push_back(u);
  }

  dfs(1, 0);
  dfs_ans(1, 0);

  for (int i = 2; i <= n; i++)
    printf("%d ", ans[i] - 1);

  return 0;
}
