#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <cstring>
#include <numeric>
#include <queue>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int INF = 0x3f3f3f3f;

constexpr int N = 105;
constexpr int K = 1005;
constexpr int V = N * N + N * 10;
constexpr int E = V * 10;

int cur_u = 0;

struct edge_t
{
  int v;
  int c;
} __attribute__((aligned(8)));

edge_t  es[E] __attribute__((aligned(16)));
edge_t *es_p = es;

edge_t *get_rev_edge(edge_t *p)
{
  return reinterpret_cast<edge_t *>(reinterpret_cast<uintptr_t>(p) ^
                                    sizeof(edge_t));
}

std::vector<edge_t *>           e[V];
std::vector<edge_t *>::iterator e_first[V];

void add_edge(int u, int v, int c)
{
  es_p->v = v;
  es_p->c = c;
  e[u].push_back(es_p);
  es_p++;
  es_p->v = u;
  es_p->c = 0;
  e[v].push_back(es_p);
  es_p++;
}

int dep[V];

bool bfs(int s, int t)
{
  memset(dep, 0x3f, sizeof(*dep) * cur_u);
  dep[s] = 0;
  std::queue<int> que;
  que.push(s);
  while (!que.empty())
  {
    int u = que.front();
    que.pop();
    if (u == t)
      return true;
    for (edge_t *i : e[u])
      if (i->c > 0)
        if (check_min(dep[i->v], dep[u] + 1))
          que.push(i->v);
  }
  return false;
}

int dfs(int u, int t, int limit)
{
  // see(u, t, limit);
  if (limit == 0 || u == t)
    return limit;
  int remain = limit;
  for (auto &it = e_first[u]; remain > 0 && it != e[u].end(); it++)
    if ((*it)->c > 0 && dep[(*it)->v] == dep[u] + 1)
    {
      int v_limit = std::min((*it)->c, remain);
      int v_cur   = dfs((*it)->v, t, v_limit);
      remain -= v_cur;
      (*it)->c -= v_cur;
      get_rev_edge(*it)->c += v_cur;
    }
  e_first[u]--;
  return limit - remain;
}

int dinic(int s, int t)
{
  int ans = 0;
  while (bfs(s, t))
  {
    for (int i = 0; i < cur_u; i++)
      e_first[i] = e[i].begin();
    int cur = 0;
    while (true)
    {
      cur = dfs(s, t, INF);
      if (cur == 0)
        break;
      ans += cur;
    }
  }
  return ans;
}

int n, m, k;
int a[N], d[N][N];
int s, t;

int d_u[N][N];
int m_u[K];

int main()
{
  n = sc.next_int();
  m = sc.next_int();
  for (int i = 1; i <= n; i++)
    a[i] = sc.next_int();
  for (int i = 1; i <= n; i++)
    for (int j = i; j <= n; j++)
      d[i][j] = sc.next_int();
  k = *std::max_element(a + 1, a + n + 1);

  s = cur_u++;
  t = cur_u++;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++)
      d_u[i][j] = cur_u++;
  for (int i = 1; i <= k; i++)
    m_u[i] = cur_u++;

  int ans = 0;

  for (int i = 1; i <= n; i++)
    for (int j = i; j <= n; j++)
    {
      if (d[i][j] > 0)
      {
        ans += d[i][j];
        add_edge(s, d_u[i][j], d[i][j]);
      }
      else
      {
        add_edge(d_u[i][j], t, -d[i][j]);
      }
      if (j > i)
      {
        add_edge(d_u[i][j], d_u[i][j - 1], INF);
        add_edge(d_u[i][j], d_u[i + 1][j], INF);
      }
      else
      {
        add_edge(d_u[i][i], t, a[i]);
        add_edge(d_u[i][i], m_u[a[i]], INF);
      }
    }
  for (int i = 1; i <= k; i++)
    add_edge(m_u[i], t, m * i * i);

  see(ans);
  ans -= dinic(s, t);

  std::cout << ans << std::endl;

  return 0;
}
