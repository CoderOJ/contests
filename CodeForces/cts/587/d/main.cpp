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
  struct edge_t
  {
    int u, v, c, t;
  };

  int n = sc.next_int();
  int m = sc.next_int();
  std::vector<edge_t> es;
  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int() - 1;
    int v = sc.next_int() - 1;
    int c = sc.next_int() - 1;
    int t = sc.next_int();
    es.push_back({u, v, c, t});
  }

  auto check = [&](int thr, bool print_ans = false) -> bool {
    std::vector<std::vector<int>> e(m * 10);

    for (int i = 0; i < m; i++)
      if (es[i].t > thr)
        e[i * 2 + 1].push_back(i * 2);

    std::vector<std::vector<int>> eu(n);
    for (int i = 0; i < m; i++)
    {
      eu[es[i].u].push_back(i);
      eu[es[i].v].push_back(i);
    }

    int cur_uid = m * 2;
    for (int i = 0; i < n; i++)
    {
      int k = static_cast<int>(eu[i].size());
      int pre_offset = cur_uid;
      int suf_offset = cur_uid + k;
      cur_uid += 2 * k;
      for (int j = 0; j < k; j++)
      {
        e[pre_offset + j].push_back(eu[i][j] * 2);
        e[suf_offset + j].push_back(eu[i][j] * 2);
        if (j > 0)
        {
          e[pre_offset + j].push_back(pre_offset + j - 1);
          e[eu[i][j] * 2 + 1].push_back(pre_offset + j - 1);
        }
        if (j + 1 < k)
        {
          e[suf_offset + j].push_back(suf_offset + j + 1);
          e[eu[i][j] * 2 + 1].push_back(suf_offset + j + 1);
        }
      }

      std::sort(eu[i].begin(), eu[i].end(),
                [&](int x, int y) { return es[x].c < es[y].c; });
      pre_offset = cur_uid;
      suf_offset = cur_uid + k;
      cur_uid += 2 * k;
      for (int jl = 0, jr = 0; jl < k; jl = jr)
      {
        while (jr < k && es[eu[i][jl]].c == es[eu[i][jr]].c)
          jr++;
        for (int j = jl; j < jr; j++)
        {
          e[pre_offset + j].push_back(eu[i][j] * 2 + 1);
          e[suf_offset + j].push_back(eu[i][j] * 2 + 1);
          if (j > jl)
          {
            e[pre_offset + j].push_back(pre_offset + j - 1);
            e[eu[i][j] * 2].push_back(pre_offset + j - 1);
          }
          if (j + 1 < jr)
          {
            e[suf_offset + j].push_back(suf_offset + j + 1);
            e[eu[i][j] * 2].push_back(suf_offset + j + 1);
          }
        }
      }
    }

    cm_assert(m * 10 == cur_uid, m, cur_uid);

    std::vector<int> dfn(cur_uid, -1), low(cur_uid), col(cur_uid);
    int cur_dfn = 0, cur_col = 0;
    std::vector<bool> in_stack(cur_uid);
    std::stack<int> st;

    std::function<void(int)> dfs = [&](int u) {
      low[u] = dfn[u] = cur_dfn++;
      in_stack[u] = true;
      st.push(u);
      for (int v : e[u])
      {
        if (dfn[v] == -1)
          dfs(v);
        if (in_stack[v])
          check_min(low[u], low[v]);
      }
      if (low[u] == dfn[u])
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

    for (int i = 0; i < cur_uid; i++)
      if (dfn[i] == -1)
        dfs(i);

    for (int i = 0; i < m; i++)
      if (col[i * 2] == col[i * 2 + 1])
      {
        if (print_ans)
          puts("No");
        return false;
      }

    if (print_ans)
    {
      puts("Yes");
      std::vector<int> ans;
      for (int i = 0; i < m; i++)
        if (col[i * 2 + 1] < col[i * 2])
          ans.push_back(i);
      std::cout << thr << " " << ans.size() << std::endl;
      for (int x : ans)
        std::cout << x + 1 << " ";
      std::cout << std::endl;
    }

    return true;
  };

  int l = 0, r = 1e9;
  while (l < r)
  {
    int mid = (l + r) / 2;
    if (check(mid))
      r = mid;
    else
      l = mid + 1;
  }
  check(l, true);

  return 0;
}
