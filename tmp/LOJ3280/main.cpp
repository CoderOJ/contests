#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <stack>
#include <vector>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

CONSTRAINT(N, 200005, 105)

std::vector<int> e[N];

int n, k;
int col[N];

int  fa[N], dl[N], dr[N], dfn_cur;
void dfs_init(int u, int f)
{
  fa[u] = f;
  dl[u] = dfn_cur++;
  for (int v : e[u])
    if (v != f)
      dfs_init(v, u);
  dr[u] = dfn_cur;
}

int c2t[N];

std::vector<int> depend[N];

std::stack<int> st;

bool in_st[N];
int  dfn[N], low[N], cur;
int  g_ans;

bool dfs_solve(int u)
{
  bool is_leaf = true;

  st.push(u);
  in_st[u] = true;
  dfn[u] = low[u] = cur++;
  for (int v : depend[u])
  {
    if (dfn[v] == -1)
    {
      is_leaf &= dfs_solve(v);
      check_min(low[u], low[v]);
    }
    else if (in_st[v])
    {
      check_min(low[u], dfn[v]);
    }
    else
    {
      is_leaf = false;
    }
  }
  if (low[u] == dfn[u])
  {
    int cur_cnt = 0;
    while (st.top() != u)
    {
      in_st[st.top()] = false;
      st.pop();
      cur_cnt++;
    }
    in_st[st.top()] = false;
    st.pop();
    cur_cnt++;

    if (is_leaf)
    {
      check_min(g_ans, cur_cnt);
      is_leaf = false;
    }
  }

  return is_leaf;
}

int main()
{
  n = sc.next_int();
  k = sc.next_int();
  for (int i = 0; i < n - 1; i++)
  {
    int u = sc.next_int();
    int v = sc.next_int();
    e[u].push_back(v);
    e[v].push_back(u);
  }
  for (int i = 1; i <= n; i++)
    col[i] = sc.next_int();

  dfs_init(1, 0);
  for (int i = 1; i <= n; i++)
    if (c2t[col[i]] == 0 || dl[c2t[col[i]]] > dl[i])
      c2t[col[i]] = i;
  for (int i = 1; i <= n; i++)
    if (dl[i] >= dr[c2t[col[i]]])
      c2t[col[i]] = 0;

  for (int i = 2; i <= n; i++)
    if (i != c2t[col[i]])
    {
      see("add_edge", col[i], col[fa[i]]);
      depend[col[i]].push_back(col[fa[i]]);
    }

  g_ans = k;
  std::fill(dfn, dfn + n + 1, -1);
  for (int i = 1; i <= k; i++)
    if (dfn[i] == -1)
      dfs_solve(i);

  std::cout << g_ans - 1 << std::endl;

  return 0;
}
