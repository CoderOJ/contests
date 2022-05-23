#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

const int N = 1095;

std::vector<int> e[N];
int              n, m;

int  dl[N], dr[N], dfn;
void dfs_init(int u, int f)
{
  dl[u] = dfn++;
  if (f != 0)
    e[u].erase(std::find(e[u].begin(), e[u].end(), f));
  for (int v : e[u])
    dfs_init(v, u);
  dr[u] = dfn;
}

bool is_path[N][N];

std::vector<int> dfs(int u)
{
  int k = static_cast<int>(e[u].size());

  std::vector<std::vector<int>> vs;
  for (int v : e[u])
    vs.emplace_back(dfs(v));

  std::vector<int> max_sd(k, 0);
  for (int i = 0; i < k; i++)
  {
    int v = e[u][i];
    for (int c = dl[v]; c < dr[v]; c++)
      check_max(max_sd[i], vs[i][c - dl[v]] + is_path[dl[u]][c]);
  }

  std::vector<std::vector<int>> max_d(k, std::vector<int>(k, 0));
  for (int i = 0; i < k; i++)
    for (int j = i + 1; j < k; j++)
    {
      const auto &da = vs[i];
      const auto &db = vs[j];
      const int   va = e[u][i];
      const int   vb = e[u][j];
      for (int ca = dl[va]; ca < dr[va]; ca++)
        for (int cb = dl[vb]; cb < dr[vb]; cb++)
          check_max(max_d[i][j],
                    da[ca - dl[va]] + db[cb - dl[vb]] + is_path[ca][cb]);
    }

  std::vector<int> ans(1 << k, 0);
  for (int i = 1; i < (1 << k); i++)
  {
    for (int x = 0; x < k; x++)
      if (i & (1 << x))
        check_max(ans[i], ans[i ^ (1 << x)] + max_sd[x]);
    for (int x = 0; x < k; x++)
      if (i & (1 << x))
        for (int y = x + 1; y < k; y++)
          if (i & (1 << y))
            check_max(ans[i], ans[i ^ (1 << x) ^ (1 << y)] + max_d[x][y]);
  }

  const int        fm = (1 << k) - 1;
  std::vector<int> res(dr[u] - dl[u], 0);
  res[0] = ans[fm];
  for (int i = 0; i < k; i++)
  {
    int v = e[u][i];
    for (int c = dl[v]; c < dr[v]; c++)
      check_max(res[c - dl[u]], ans[fm ^ (1 << i)] + vs[i][c - dl[v]]);
  }
  return res;
}

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    n = sc.next_int();
    for (int i = 1; i <= n; i++)
      e[i].clear();
    for (int i = 0; i < n - 1; i++)
    {
      int u = sc.next_int();
      int v = sc.next_int();
      e[u].push_back(v);
      e[v].push_back(u);
    }
    dfn = 0;
    dfs_init(1, 0);

    m = sc.next_int();
    for (int i = 0; i < n; i++)
      std::fill(is_path[i], is_path[i] + n, false);
    for (int i = 0; i < m; i++)
    {
      int u         = dl[sc.next_int()];
      int v         = dl[sc.next_int()];
      is_path[u][v] = true;
      is_path[v][u] = true;
    }

    auto res = dfs(1);
    std::cout << res[0] << std::endl;
  }

  return 0;
}
