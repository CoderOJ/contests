#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <functional>
#include <limits>
#include <memory>
#include <queue>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

template <class T>
struct leftist_t
{
  using value_type = T;

  struct node_t
  {
    node_t    *ls = nullptr;
    node_t    *rs = nullptr;
    value_type value;
    int        dist = 0;

    void update_dist()
    {
      dist = std::max(ls ? ls->dist + 1 : 0, rs ? rs->dist + 1 : 0);
    }
    void balance()
    {
      if ((ls ? ls->dist : -1) > (rs ? rs->dist : -1))
      {
        std::swap(ls, rs);
      }
    }

    node_t() = default;
    node_t(const value_type &value) : value(value) {}
  };

  static node_t *new_node_t(const value_type &value)
  {
    static node_t  _p[1'000'000];
    static node_t *p = _p;
    p->value         = value;
    return p++;
  }

  node_t *root = nullptr;

  static node_t *join(node_t *lt, node_t *rt)
  {
    // see(lt, rt);
    if (lt == nullptr || rt == nullptr)
    {
      return lt ?: rt;
    }
    else
    {
      if (lt->value <= rt->value)
      {
        auto res = new_node_t(lt->value);
        res->ls  = join(lt->ls, rt);
        res->rs  = lt->rs;
        res->update_dist();
        res->balance();
        return res;
      }
      else
      {
        return join(rt, lt);
      }
    }
  }

  void insert(const value_type &value)
  {
    root = join(root, new_node_t(value));
  }

  void merge(const leftist_t &rhs)
  {
    root = join(root, rhs.root);
  }
};

constexpr int                    N   = 5005;
constexpr int                    inf = std::numeric_limits<int>::max() / 2;
std::vector<std::pair<int, int>> e[N];
std::vector<std::pair<int, int>> e_rev[N];
std::vector<int>                 et[N];
int                              n, m, k, s, t;

int  dis_rev[N];
int  pre_rev[N];
void init_rev()
{
  std::fill(dis_rev + 1, dis_rev + n + 1, inf);
  dis_rev[t] = 0;
  pre_rev[t] = -1;
  std::priority_queue<std::pair<int, int>,
                      std::vector<std::pair<int, int>>,
                      std::greater<std::pair<int, int>>>
      que;
  que.emplace(0, t);
  while (!que.empty())
  {
    const auto [d, u] = que.top();
    see(d, u);
    que.pop();
    if (d > dis_rev[u])
      continue;
    for (const auto &[v, w] : e_rev[u])
      if (check_min(dis_rev[v], d + w))
      {
        pre_rev[v] = u;
        que.emplace(dis_rev[v], v);
      }
  }

  for (int i = 1; i <= n; i++)
    if (pre_rev[i] != -1)
      et[pre_rev[i]].push_back(i);
}

using value_t = std::pair<int, int>;
using pq_t    = leftist_t<value_t>;
pq_t pq[N];

void init_pq(int u)
{
  cm::once_t skip_once;
  for (const auto &[v, w] : e[u])
    if (dis_rev[v] < inf)
      if (!(v == pre_rev[u] && w == dis_rev[u] - dis_rev[v] && skip_once()))
        pq[u].insert({w - (dis_rev[u] - dis_rev[v]), v});
  for (int v : et[u])
  {
    pq[v] = pq[u];
    init_pq(v);
  }
  see(u, pq[u].root);
}

int main()
{
  n = sc.next_int();
  m = sc.next_int();
  for (int i = 0; i < m; i++)
  {
    int u = sc.next_int();
    int v = sc.next_int();
    int w = sc.next_int();
    e[u].emplace_back(v, w);
    e_rev[v].emplace_back(u, w);
  }
  s = sc.next_int();
  t = sc.next_int();
  k = sc.next_int();

  if (n == 1)
  {
    puts("-1");
    return 0;
  }

  init_rev();
  if (dis_rev[s] == inf)
  {
    puts("-1");
    return 0;
  }
  init_pq(t);

  struct pq_node_t
  {
    pq_t::node_t *p;
    int           pre_dis;
    int           u;

    bool operator<(const pq_node_t &rhs) const
    {
      return pre_dis + p->value.first > rhs.pre_dis + rhs.p->value.first;
    }
  };

  std::priority_queue<pq_node_t> que;
  if (pq[s].root != nullptr)
    que.push({pq[s].root, 0, 1});
  int ans = dis_rev[s];

  if (s == t)
    k++;

  for (int i = 1; i < k; i++)
  {
    if (que.empty())
    {
      puts("-1");
      return 0;
    }

    const auto t = que.top();
    cm_assert(t.p != nullptr);
    que.pop();

    see(t.u, t.pre_dis, t.p->value);
    ans = t.pre_dis + t.p->value.first + dis_rev[s];
    if (pq[t.p->value.second].root != nullptr)
      que.push({pq[t.p->value.second].root,
                t.pre_dis + t.p->value.first,
                t.p->value.second});
    if (t.p->ls != nullptr)
      que.push({t.p->ls, t.pre_dis, t.u});
    if (t.p->rs != nullptr)
      que.push({t.p->rs, t.pre_dis, t.u});
  }

  std::cout << ans << std::endl;

  return 0;
}
