#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 200005;
std::vector<int> e[N];
int n;

int size[N];
long long ans[N];
void dfs(int u, int f)
{
  size[u] = 1;
  for (int v : e[u]) if (v != f)
  {
    dfs(v, u);
    size[u] += size[v];
  }
  for (int v : e[u]) if (v != f)
  {
    ans[1] += size[v];
    ans[v] -= size[v];
    ans[v] += n - size[v];
  }
}

void dfs2(int u, int f)
{
  for (int v : e[u]) if (v != f)
  {
    ans[v] += ans[u];
    dfs2(v, u);
  }
}

int main()
{
  n = sc.next_int();
  for (int i = 1; i < n; i++)
  {
    int u = sc.next_int();
    int v = sc.next_int();
    e[u].push_back(v);
    e[v].push_back(u);
  }

  dfs(1, 0);
  dfs2(1, 0);

  for (int i = 1; i <= n; i++)
    printf("%lld\n", ans[i]);
  return 0;
}

