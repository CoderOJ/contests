#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <vector>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

CONSTRAINT(N, 1'000'005, 1'005)

template <class value_type>
struct ftree_t
{
  value_type data[N];

  void add(int p, value_type v)
  {
    for (; p < N; p += p & -p)
      data[p] += v;
  }

  value_type sum(int p)
  {
    value_type res = 0;
    for (; p > 0; p -= p & -p)
      res += data[p];
    return res;
  }
};

enum struct u_type
{
  act,
  virt,
};

std::vector<int> e[N];
std::vector<int> et[N];
std::vector<int> ev[N];

u_type ut[N];
int    topv[N];
int    t[N];
int    n;
int    cur_time;
int    cur_vertex;

struct query_t
{
  int time = 0;
  int u    = 0;
  int ans  = 0;
};

std::vector<query_t>   qs;
std::vector<query_t *> qd_by_u[N];
std::vector<query_t *> qu_by_u[N];

ftree_t<int> by_time;

void dfs_add(std::vector<int> e[], int u, int val)
{
  see("add", u, val);
  by_time.add(t[u], val);
  for (int v : e[u])
    dfs_add(e, v, val);
}

void dfs_calc_qd(int u)
{
  for (int v : e[u])
  {
    if (ut[v] == u_type::act)
      dfs_add(ev, v, 1);
    else
      dfs_calc_qd(v);
  }
  for (query_t *q : qd_by_u[u])
  {
    q->ans += by_time.sum(q->time);
  }
  for (int v : et[u])
    dfs_add(ev, v, -1);
}

int  size[N], wson[N];
void dfs_dsu_init(int u)
{
  int max_son = 0;
  wson[u]     = -1;
  size[u]     = 1;
  for (int v : ev[u])
  {
    dfs_dsu_init(v);
    size[u] += size[v];
    if (check_max(max_son, size[v]))
      wson[u] = v;
  }
}

void dfs_dsu(int u)
{
  cm_assert(by_time.sum(cur_time) == 0, u);

  see("dfs_dsu", u, wson[u]);
  if (wson[u] == -1)
  {
    by_time.add(t[u], 1);
    for (int v : et[u])
      for (query_t *q : qu_by_u[v])
      {
        q->ans += by_time.sum(q->time);
        see(q->time, q->u, q->ans);
      }
    return;
  }

  for (int v : ev[u])
    if (v != wson[u])
    {
      dfs_dsu(v);
      dfs_add(ev, v, -1);
    }

  auto it = e[u].rbegin();
  by_time.add(t[u], 1);
  for (; *it != wson[u]; it++)
  {
    see("before wson", u, *it);
    int v = *it;
    if (ut[v] == u_type::virt)
      dfs_add(ev, v, 1);
    else
    {
      for (query_t *q : qu_by_u[v])
        q->ans += by_time.sum(q->time);
    }
  }
  by_time.add(t[u], -1);
  for (auto itv = e[u].rbegin(); itv != it; itv++)
    if (ut[*itv] == u_type::virt)
      dfs_add(ev, *itv, -1);
  dfs_dsu(wson[u]);
  by_time.add(t[u], 1);
  for (auto itv = e[u].rbegin(); itv != it; itv++)
    if (ut[*itv] == u_type::virt)
      dfs_add(ev, *itv, 1);
  it++;
  for (; it != e[u].rend(); it++)
  {
    see("after wson", u, *it);
    int v = *it;
    if (ut[v] == u_type::virt)
      dfs_add(ev, v, 1);
    else
    {
      for (query_t *q : qu_by_u[v])
      {
        q->ans += by_time.sum(q->time);
        see(q->time, q->u, q->ans);
      }
    }
  }
}

int main()
{
  n = sc.next_int();

  e[1].push_back(2);
  et[1].push_back(2);
  topv[1] = 1;
  topv[2] = 2;
  t[1]    = 1;
  t[2]    = 2;

  cur_time   = 3;
  cur_vertex = 3;

  qs.reserve(n);
  for (int i = 0; i < n; i++)
  {
    char opt = sc.next_char();
    if (opt == '?')
    {
      int u = sc.next_int();
      qs.push_back({cur_time, u, 0});
      qd_by_u[u].push_back(&qs.back());
      qu_by_u[topv[u]].push_back(&qs.back());
    }
    else if (opt == 'W')
    {
      int f   = sc.next_int();
      int u   = cur_vertex++;
      topv[u] = u;
      t[u]    = cur_time;
      ut[u]   = u_type::act;
      e[f].push_back(u);
      et[f].push_back(u);
    }
    else if (opt == 'Z')
    {
      int f   = sc.next_int();
      int u   = cur_vertex++;
      topv[u] = topv[f];
      t[u]    = cur_time;
      ut[u]   = u_type::virt;
      e[f].push_back(u);
      ev[f].push_back(u);
    }
    cur_time++;
  }

  for (int u = 1; u < cur_vertex; u++)
    if (ut[u] == u_type::act)
    {
      see(u);
      dfs_calc_qd(u);
    }
  for (int u = 1; u < cur_vertex; u++)
    if (ut[u] == u_type::act)
    {
      dfs_dsu_init(u);
      dfs_dsu(u);
      dfs_add(ev, u, -1);
    }

  for (const auto &q : qs)
  {
    printf("%d\n", q.ans);
  }

  return 0;
}