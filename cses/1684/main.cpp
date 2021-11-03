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
  std::vector<std::vector<int>> e(m * 2);

  for (int i = 0; i < n; i++)
  {
    bool op_a = sc.next_char() == '+';
    int id_a = sc.next_int() - 1;
    bool op_b = sc.next_char() == '+';
    int id_b = sc.next_int() - 1;
    e[id_a * 2 + !op_a].push_back(id_b * 2 + op_b);
    e[id_b * 2 + !op_b].push_back(id_a * 2 + op_a);
  }

  std::vector<int> dfn(m * 2, -1), low(m * 2), col(m * 2);
  int cur_dfn = 0, cur_col = 0;
  std::vector<bool> in_stack(m * 2, false);
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

  for (int i = 0; i < m * 2; i++)
    if (dfn[i] == -1)
      dfs(i);

  std::vector<bool> ans(m);
  for (int i = 0; i < m; i++)
  {
    if (col[i * 2] == col[i * 2 + 1])
    {
      puts("IMPOSSIBLE");
      return 0;
    }
    ans[i] = col[i * 2] < col[i * 2 + 1] ? false : true;
  }

  for (int i = 0; i < m; i++)
    printf(ans[i] ? "+ " : "- ");

  return 0;
}
