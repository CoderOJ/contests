#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <limits>
#include <set>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

struct node_t
{
  using min_t = std::pair<int, int>;

  node_t *f     = nullptr;
  node_t *s[2]  = {nullptr, nullptr};
  bool    rev   = false;
  int     cnt_v = 1;
  int     cnt_a = 1;
  min_t   e_max = {-1, 0};
  min_t   e_val = e_max;

  bool is_root()
  {
    return f == nullptr || (f->s[0] != this && f->s[1] != this);
  }
  bool get_son()
  {
    return f->s[1] == this;
  }
  void push_up()
  {
    e_max = e_val;
    cnt_a = cnt_v;
    if (s[0] != nullptr)
    {
      check_max(e_max, s[0]->e_max);
      cnt_a += s[0]->cnt_a;
    }
    if (s[1] != nullptr)
    {
      check_max(e_max, s[1]->e_max);
      cnt_a += s[1]->cnt_a;
    }
  }
  void push_rev()
  {
    std::swap(s[0], s[1]);
    rev = !rev;
  }
  void push_down()
  {
    if (rev)
    {
      if (s[0] != nullptr)
        s[0]->push_rev();
      if (s[1] != nullptr)
        s[1]->push_rev();
      rev = false;
    }
  }
  void push()
  {
    if (!is_root())
      f->push();
    push_down();
  }
  void rotate()
  {
    node_t *const uu = this;
    node_t *const ff = uu->f;
    node_t *const aa = ff->f;
    const bool    ss = get_son();
    if (!ff->is_root())
      aa->s[ff->get_son()] = uu;
    ff->f      = uu;
    ff->s[ss]  = uu->s[!ss];
    uu->f      = aa;
    uu->s[!ss] = ff;
    if (ff->s[ss] != nullptr)
      ff->s[ss]->f = ff;
    ff->push_up();
  }
  void splay()
  {
    push();
    while (!is_root())
    {
      if (f->is_root())
      {
        rotate();
        break;
      }
      else
      {
        (get_son() == f->get_son() ? f : this)->rotate();
        rotate();
      }
    }
    push_up();
  }
  void access()
  {
    node_t *uu = this;
    node_t *ss = nullptr;
    while (uu != nullptr)
    {
      uu->splay();
      if (uu->s[1] != nullptr)
        uu->cnt_v += uu->s[1]->cnt_a;
      uu->s[1] = ss;
      if (uu->s[1] != nullptr)
        uu->cnt_v -= uu->s[1]->cnt_a;
      uu->push_up();
      ss = uu;
      uu = uu->f;
    }
  }
  void make_root()
  {
    access();
    splay();
    push_rev();
  }
  node_t *find_root()
  {
    access();
    splay();
    node_t *uu = this;
    while (uu->s[0] != nullptr)
    {
      uu->push_down();
      uu = uu->s[0];
    }
    uu->splay();
    return uu;
  }
};

constexpr int N = 100005;
constexpr int M = 300005;

node_t p[N + M];

void link(int u, int v)
{
  p[u].make_root();
  p[v].make_root();
  p[u].f = &p[v];
  p[v].cnt_v += p[u].cnt_a;
  p[v].push_up();
}

void split(int u, int v)
{
  p[u].make_root();
  p[v].access();
  p[v].splay();
}

void cut(int u, int v)
{
  split(u, v);
  p[v].s[0] = nullptr;
  p[u].f    = nullptr;
  p[v].push_up();
}

int get_size(int u)
{
  p[u].access();
  p[u].splay();
  return p[u].cnt_a;
}

int n, m;
struct edge_t
{
  int u, v, w;
};
edge_t e[M];

std::set<std::pair<int, int>> es;
int                           odd_cnt;

void cut_edge(int id)
{
  const auto [u, v, w] = e[id];
  const int r          = n + id + 1;
  cut(u, r);
  cut(v, r);
  es.erase({w, id});

  int su = get_size(u), sv = get_size(v);
  if (su % 2 == 1 && sv % 2 == 1)
    odd_cnt += 2;
}

void add_edge(int id)
{
  const auto [u, v, w] = e[id];
  if (p[u].find_root() == p[v].find_root())
  {
    split(u, v);
    const auto [max_w, max_id] = p[v].e_max;
    if (max_w < w)
      return;
    cut_edge(max_id);
  }

  int su = get_size(u), sv = get_size(v);
  if (su % 2 == 1 && sv % 2 == 1)
    odd_cnt -= 2;

  const int r = n + id + 1;
  p[r].e_val  = {w, id};
  p[r].cnt_v  = 0;
  link(u, r);
  link(v, r);
  es.insert({w, id});
}

int main()
{
  n       = sc.next_int();
  odd_cnt = n;
  m       = sc.next_int();
  for (int i = 0; i < m; i++)
  {
    e[i].u = sc.next_int();
    e[i].v = sc.next_int();
    e[i].w = sc.next_int();
  }

  for (int i = 0; i < m; i++)
  {
    add_edge(i);
    while (odd_cnt == 0)
    {
      const auto [max_w, max_id] = *es.rbegin();
      cut_edge(max_id);
      see(es, odd_cnt);
      if (odd_cnt != 0)
      {
        add_edge(max_id);
        break;
      }
    }
    see(es, odd_cnt);
    printf("%d\n", odd_cnt == 0 ? es.rbegin()->first : -1);
  }
  return 0;
}
