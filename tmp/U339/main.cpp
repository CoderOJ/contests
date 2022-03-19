#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 1000005;

std::vector<int> e[N];

int n;

int  mf[N];
void dfs_calc_mf(int u, int f)
{
  int s = static_cast<int>(e[u].size()) - (u != f);
  if (s <= 1)
    mf[u] = u;
  else
    mf[u] = n + 1;
  for (int v : e[u])
    if (v != f)
    {
      dfs_calc_mf(v, u);
      check_min(mf[u], mf[v]);
    }
  see(u, mf[u]);
}

std::vector<int> ans;

void dfs_exact_subtree(int u, int f)
{
  int s = static_cast<int>(e[u].size()) - (u != f);

  std::vector<int> vs;
  for (int v : e[u])
    if (v != f)
      vs.push_back(v);

  if (s == 0)
  {
    ans.push_back(u);
  }
  else if (s == 1)
  {
    if (u < mf[vs[0]])
    {
      ans.push_back(u);
      dfs_exact_subtree(vs[0], u);
    }
    else
    {
      dfs_exact_subtree(vs[0], u);
      ans.push_back(u);
    }
  }
  else
  {
    if (mf[vs[0]] > mf[vs[1]])
      std::swap(vs[0], vs[1]);
    dfs_exact_subtree(vs[0], u);
    ans.push_back(u);
    dfs_exact_subtree(vs[1], u);
  }
}

void dfs_ltor(int u, int f)
{
  int s = static_cast<int>(e[u].size()) - (u != f);

  std::vector<int> vs;
  for (int v : e[u])
    if (v != f)
      vs.push_back(v);

  if (s == 0)
  {
    ans.push_back(u);
  }
  else if (s == 1)
  {
    ans.push_back(u);
    int v = vs[0];
    if (mf[v] < v)
      dfs_exact_subtree(v, u);
    else
      dfs_ltor(v, u);
  }
  else
  {
    ans.push_back(u);
    if (mf[vs[0]] > mf[vs[1]])
      std::swap(vs[0], vs[1]);
    dfs_exact_subtree(vs[0], u);
    dfs_ltor(vs[1], u);
  }
}

int main()
{
  n = sc.next_int();
  for (int u = 1; u <= n; u++)
  {
    int t = sc.next_int();
    for (int i = 0; i < t; i++)
    {
      int v = sc.next_int();
      e[u].push_back(v);
    }
  }

  int root = [] {
    for (int u = 1; u <= n; u++)
      if (e[u].size() <= 2)
        return u;
    return -1;
  }();

  dfs_calc_mf(root, root);
  dfs_ltor(root, root);

  for (int u : ans)
    std::cout << u << ' ';
  std::cout << std::endl;

  return 0;
}
