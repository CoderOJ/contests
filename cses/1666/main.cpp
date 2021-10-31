#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  int m = sc.next_int();
  std::vector<std::vector<int>> e(n + 1);
  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int(), v = sc.next_int();
    e[u].push_back(v), e[v].push_back(u);
  }

  std::vector<int> col(n + 1);
  auto dfs = [&](auto &&self, int u, int c) -> void {
    col[u] = c;
    for (int v : e[u])
      if (col[v] == 0)
        self(self, v, c);
  };

  int cur_col = 1;
  std::vector<std::pair<int, int>> ans;
  for (int i = 1; i <= n; i++)
    if (col[i] == 0)
    {
      dfs(dfs, i, cur_col);
      if (cur_col > 1)
        ans.emplace_back(1, i);
      cur_col++;
    }

  std::cout << ans.size() << std::endl;
  for (const auto &[u, v] : ans)
    std::cout << u << " " << v << std::endl;

  return 0;
}
