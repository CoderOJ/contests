#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <cstdio>
#include <functional>
#include <vector>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

void passert(bool cond, const char *str)
{
  if (!cond)
  {
    puts(str);
    exit(0);
  }
}

int main()
{
  int n = sc.next_int();
  int m = sc.next_int();
  std::vector<std::vector<int>> e(n);
  std::vector<int> deg_in(n), deg_out(n);
  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    deg_out[u]++;
    deg_in[v]++;
    e[u].push_back(v);
  }

  see(deg_in);
  see(deg_out);

  passert(deg_out[0] - deg_in[0] == 1, "IMPOSSIBLE");
  passert(deg_in[n - 1] - deg_out[n - 1] == 1, "IMPOSSIBLE");
  for (int i = 1; i < n - 1; i++)
    passert(deg_in[i] == deg_out[i], "IMPOSSIBLE");

  std::vector<std::vector<int>::iterator> e_cur(n);
  for (int i = 0; i < n; i++)
    e_cur[i] = e[i].begin();

  std::vector<int> ans;
  std::function<void(int)> dfs = [&](int u) {
    for (auto &it = e_cur[u]; it != e[u].end();)
    {
      int v = *it;
      it++;
      dfs(v);
    }
    ans.push_back(u);
  };

  dfs(0);
  std::reverse(ans.begin(), ans.end());
  passert(static_cast<int>(ans.size()) == m + 1, "IMPOSSIBLE");
  for (int x : ans)
    std::cout << x + 1 << " ";

  return 0;
}
