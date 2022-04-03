#include <bits/stdc++.h>

const int N = 100005;
std::vector<std::pair<int, int>> claim[N];
std::vector<int> c_true[N];
std::vector<int> c_true_pre[N];
std::vector<int> c_true_suf[N];
std::vector<int> c_false[N];
int c_true_all[N];
int c_false_any[N];
int n, m;

std::vector<int> e[N * 6];
int cur_u;

int scc[N * 6], scc_cur;
int dfn[N * 6], low[N * 6], dfn_cur;
std::stack<int> st;
bool in_stack[N * 6];

void dfs(int u)
{
  low[u] = dfn[u] = dfn_cur++;
  st.push(u);
  in_stack[u] = true;
  for (int v : e[u])
  {
    // printf("edge: %d %d\n", u, v);
    if (dfn[v] == -1)
    {
      dfs(v);
      low[u] = std::min(low[u], low[v]);
    }
    if (in_stack[v])
    {
      low[u] = std::min(low[u], dfn[v]);
    }
  }
  if (low[u] == dfn[u])
  {
    int scc_id = scc_cur++;
    while (st.top() != u)
    {
      scc[st.top()] = scc_id;
      in_stack[st.top()] = false;
      st.pop();
    }
    scc[u] = scc_id;
    in_stack[u] = false;
    st.pop();
  }
}

bool ans[N];

int main()
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < m; i++)
  {
    int u, v, w;
    scanf("%d%d%d", &u, &v, &w);
    claim[u].emplace_back(v, w);
  }

  for (int u = 1; u <= n; u++)
  {
    auto &c_true = ::c_true[u];
    auto &c_true_pre = ::c_true_pre[u];
    auto &c_true_suf = ::c_true_suf[u];
    auto &c_false = ::c_false[u];
    auto &c_true_all = ::c_true_all[u];
    auto &c_false_any = ::c_false_any[u];
    for (size_t i = 0; i < claim[u].size(); i++)
    {
      c_true.push_back(cur_u++);
      c_true_pre.push_back(cur_u++);
      c_true_suf.push_back(cur_u++);
      c_false.push_back(cur_u++);
    }
    c_true_all = cur_u++;
    c_false_any = cur_u++;
    for (size_t i = 0; i < claim[u].size(); i++)
    {
      e[c_true_pre[i]].push_back(c_true[i]);
      e[c_true_suf[i]].push_back(c_true[i]);
      if (i > 0) 
      {
        e[c_true_pre[i]].push_back(c_true_pre[i - 1]);
        e[c_false[i]].push_back(c_true_pre[i - 1]);
      }
      if (i + 1 < claim[u].size()) 
      {
        e[c_true_suf[i]].push_back(c_true_suf[i + 1]);
        e[c_false[i]].push_back(c_true_suf[i + 1]);
      }
      e[c_true_all].push_back(c_true[i]);
      e[c_false[i]].push_back(c_false_any);
    }
  }

  for (int u = 1; u <= n; u++)
    for (size_t i = 0; i < claim[u].size(); i++)
    {
      const auto &[v, w] = claim[u][i];
      if (w == 0) 
      {
        e[c_false[u][i]].push_back(c_true_all[v]);
        e[c_true_all[v]].push_back(c_false[u][i]);
        e[c_true[u][i]].push_back(c_false_any[v]);
        e[c_false_any[v]].push_back(c_true[u][i]);
      }
      else  
      {
        e[c_true[u][i]].push_back(c_true_all[v]);
        e[c_true_all[v]].push_back(c_true[u][i]);
        e[c_false[u][i]].push_back(c_false_any[v]);
        e[c_false_any[v]].push_back(c_false[u][i]);
      }
    }

  memset(dfn, -1, sizeof(dfn));
  for (int i = 0; i < cur_u; i++)
    if (dfn[i] == -1)
      dfs(i);

  for (int u = 1; u <= n; u++)
  {
    for (size_t i = 0; i < claim[u].size(); i++)
    {
      // printf("claim %d %zu: %d %d\n", u, i, scc[c_true[u][i]], scc[c_false[u][i]]);
      if (scc[c_true[u][i]] == scc[c_false[u][i]])
      {
        puts("Impossible");
        return 0;
      }
      else
      {
        bool cur_truth = (scc[c_true[u][i]] < scc[c_false[u][i]]);
        if (!cur_truth) ans[u] = true;
        ans[claim[u][i].first] = cur_truth ^ claim[u][i].second;
      }
    }
  }

  std::vector<int> fake;
  for (int u = 1; u <= n; u++)
    if (ans[u])
      fake.push_back(u);

  printf("%zu\n", fake.size());
  for (int u : fake) printf("%d ", u);
  puts("");

  return 0;
}
