#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <functional>
#include <stack>
#include <vector>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  int m = sc.next_int();

  std::vector<long long> val(n);
  for (int i = 0; i < n; i++)
    val[i] = sc.next_int();

  std::vector<std::vector<int>> e(n);
  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    e[u].push_back(v);
  }

  std::vector<int> dfn(n, -1), low(n), col(n);
  int cur_dfn = 0, cur_col = 0;
  std::vector<bool> in_stack(n, false);
  std::stack<int> st;

  std::function<void(int)> dfs = [&](int u) {
    dfn[u] = low[u] = cur_dfn++;
    in_stack[u] = true;
    st.push(u);
    for (int v : e[u])
    {
      if (dfn[v] == -1)
        dfs(v);
      if (in_stack[v])
        check_min(low[u], low[v]);
    }
    if (dfn[u] == low[u])
    {
      col[u] = cur_col++;
      while (st.top() != u)
      {
        col[st.top()] = col[u];
        in_stack[st.top()] = false;
        st.pop();
      }
      in_stack[u] = false;
      st.pop();
    }
  };

  for (int i = 0; i < n; i++)
    if (dfn[i] == -1)
      dfs(i);

  std::vector<std::vector<int>> scc_e(cur_col);
  std::vector<long long> scc_val(cur_col, 0);
  for (int i = 0; i < n; i++)
    scc_val[col[i]] += val[i];
  for (int u = 0; u < n; u++)
    for (int v : e[u])
      if (col[u] != col[v])
        scc_e[col[u]].push_back(col[v]);

  std::vector<long long> ans(cur_col, -1);
  std::function<long long(int)> get_ans = [&](int u) {
    if (ans[u] != -1)
      return ans[u];
    ans[u] = scc_val[u];
    for (int v : scc_e[u])
      check_max(ans[u], scc_val[u] + get_ans(v));
    return ans[u];
  };

  for (int i = 0; i < cur_col; i++)
    get_ans(i);
  std::cout << *std::max_element(ans.begin(), ans.end()) << std::endl;

  return 0;
}
