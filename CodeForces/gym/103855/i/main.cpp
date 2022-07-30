#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
// #include "/home/jack/cm/math_util.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <algorithm>
#include <cstdio>
#include <limits>
#include <list>
#include <queue>

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int INF = std::numeric_limits<int>::max() / 2;
constexpr int N   = 6005;

struct edge_t
{
  int     v, w;
  edge_t *rev;
};

std::list<edge_t> e[N];

edge_t *add_edge(int u, int v, int w)
{
  see(u, v, w);

  e[u].push_back({v, w, nullptr});
  e[v].push_back({u, 0, nullptr});
  e[u].back().rev = &e[v].back();
  e[v].back().rev = &e[u].back();
  return &e[u].back();
}

int n, m;
int cur_u = n + 1;

int p[N];

int get(int u)
{
  return p[u] == u ? u : p[u] = get(p[u]);
}

bool    has_lost[N];
int     det_w[N];
edge_t *u_key[N];

int dep[N];

bool bfs(int s, int t)
{
  std::fill(dep, dep + cur_u, INF);
  dep[s] = 0;

  std::queue<int> que;
  que.push(s);

  while (!que.empty())
  {
    int u = que.front();
    que.pop();

    if (u == t)
      break;

    for (auto v: e[u])
      if (v.w > 0 && dep[v.v] == INF)
      {
        dep[v.v] = dep[u] + 1;
        que.push(v.v);
      }
  }

  return dep[t] != INF;
}

std::list<edge_t>::iterator ef[N];

int dfs(int u, int t, int lim)
{
  if (u == t)
    return lim;
  else
  {
    int rem = lim;

    for (auto &it = ef[u]; it != e[u].end(); it++)
      if (it->w && dep[it->v] == dep[u] + 1)
      {
        int v_lim = std::min(rem, it->w);
        int v_use = dfs(it->v, t, v_lim);

        rem -= v_use;
        it->w -= v_use;
        it->rev->w += v_use;

        if (rem == 0)
          break;
      }

    return lim - rem;
  }
}

int dinic(int s, int t)
{
  int ans = 0;
  while (bfs(s, t))
  {
    for (int u = 1; u < cur_u; u++)
      ef[u] = e[u].begin();
    ans += dfs(s, t, INF);
  }
  return ans;
}

int main()
{
  n     = sc.next_int();
  m     = sc.next_int();
  cur_u = n + 1;

  for (int i = 1; i <= n + m; i++)
    p[i] = i;

  for (int i = 0; i < m; i++)
  {
    int op = sc.next_int();
    if (op == 1)
    {
      int u = sc.next_int();
      int v = sc.next_int();
      u     = get(u);
      v     = get(v);

      int r = cur_u++;
      p[u]  = r;
      p[v]  = r;

      add_edge(u, r, n);
      add_edge(v, r, n);
    }
    else if (op == 2)
    {
      int u  = sc.next_int();
      int pu = get(u);

      has_lost[u] = true;
      u_key[u]    = add_edge(pu, u, 1);
    }
    else
    {
      int u  = sc.next_int();
      int bl = sc.next_int();
      int br = sc.next_int();
      u      = get(u);

      int r = cur_u++;
      p[u]  = r;

      det_w[u] -= bl;
      det_w[r] += bl;
      add_edge(u, r, br - bl);
    }
  }

  for (int u = 1; u <= n; u++)
    if (!has_lost[u])
    {
      int pu   = get(u);
      u_key[u] = add_edge(pu, u, 1);
    }

  const int s = cur_u++;
  const int t = cur_u++;

  int require_w = 0;
  for (int u = 1; u < cur_u; u++)
    if (det_w[u] != 0)
    {
      require_w += std::abs(det_w[u]);

      if (det_w[u] < 0)
        add_edge(u, t, -det_w[u]);
      else
        add_edge(s, u, det_w[u]);
    }
  require_w /= 2;

  int flow = dinic(s, t);
  see(flow);
  if (flow < require_w)
  {
    puts("NO");
  }
  else
  {
    puts("YES");
    for (int u = 1; u <= n; u++)
      putchar(u_key[u]->w == 0 ? 'R' : 'B');
    puts("");
  }

  return 0;
}
