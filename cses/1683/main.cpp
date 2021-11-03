#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
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
  std::vector<std::vector<int>> e(n);
  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    e[u].push_back(v);
  }

  std::vector<bool> in_stack(n, false);
  std::stack<int> st;
  std::vector<int> dfn(n, -1), low(n, -1);
  int cur_dfn = 0;
  std::vector<int> label(n, -1);
  int cur_label = 0;

  std::function<void(int)> dfs = [&](int u) {
    dfn[u] = low[u] = cur_dfn++;
    st.emplace(u);
    in_stack[u] = true;
    for (int v : e[u])
    {
      if (dfn[v] == -1)
        dfs(v);
      if (in_stack[v])
        check_min(low[u], low[v]);
    }
    if (dfn[u] == low[u])
    {
      label[u] = cur_label++;
      while (st.top() != u)
      {
        in_stack[st.top()] = false;
        label[st.top()] = label[u];
        st.pop();
      }
      in_stack[u] = false;
      st.pop();
    }
  };

  for (int i = 0; i < n; i++)
    if (dfn[i] == -1)
      dfs(i);

  std::cout << cur_label << std::endl;
  for (int i = 0; i < n; i++)
    std::cout << label[i] + 1 << " ";

  return 0;
}
