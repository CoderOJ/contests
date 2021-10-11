#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 500005;

struct node_t
{
  node_t *f = nullptr, *s[2] = {nullptr, nullptr};
  bool rev = false; 
  int val = 1e6, min = val;
  int cover = 0, max_cover, add = 0;
  int weigh = 0, max_weigh;

  bool is_root() { return f==nullptr || (f->s[0] != this && f->s[1] != this); }
  bool get_son() { return f->s[1] == this; }
  void push_up() { min = val; max_cover = cover; max_weigh = weigh;
    if (s[0]) check_min(min, s[0]->min), check_max(max_cover, s[0]->max_cover), check_max(max_weigh, s[0]->max_weigh);
    if (s[1]) check_min(min, s[1]->min), check_max(max_cover, s[1]->max_cover), check_max(max_weigh, s[1]->max_weigh); }
  void push_add(int delta) { cover += weigh ? delta : 0; max_cover += max_weigh ? delta : 0; add += delta; }
  void push_rev() { rev ^= 1; std::swap(s[0], s[1]); }
  void push_down() {
    if (rev) { if (s[0]) s[0]->push_rev(); if (s[1]) s[1]->push_rev(); rev = false; }
    if (add) { if (s[0]) s[0]->push_add(add); if (s[1]) s[1]->push_add(add); add = 0; } }
  void push() { if (!is_root()) f->push(); push_down(); }

  void rotate() { 
    node_t *uu=this, *ff=f, *aa=ff->f;
    bool ss = get_son(); 
    if (!ff->is_root()) aa->s[ff->get_son()] = uu;
    ff->f = uu; ff->s[ss] = uu->s[!ss];
    uu->f = aa; uu->s[!ss] = ff;
    if (ff->s[ss]) ff->s[ss]->f = ff;
    ff->push_up(); uu->push_up(); }
  void splay() { push();
    while (!is_root()) { if (f->is_root()) { rotate(); break; }
      (f->get_son() == get_son() ? f : this)->rotate(); rotate(); } }
  void access() { node_t *uu = this, *ss = nullptr;
    while (uu != nullptr) { 
      uu->splay(); uu->s[1] = ss; uu->push_up();
      ss = uu; uu = uu->f; } }
  void make_root() { access(); splay(); push_rev(); }
  node_t *find_root() {
    access(); splay(); node_t *uu = this; uu->push_down();
    while (uu->s[0]) { uu = uu->s[0]; uu->push_down(); } 
    uu->splay(); return uu; }
};

node_t p[N * 2];
int u[N], v[N];
int n, m;
bool is_te[N];

void add_edge(int id)
{
  is_te[id] = true;
  int eid = n + id;
  see("add_edge", id, u[id], v[id]);
  p[eid].val = p[eid].min = id; p[eid].weigh = 1;
  p[u[id]].make_root(); p[u[id]].splay(); p[u[id]].f = &p[eid];
  p[v[id]].make_root(); p[v[id]].splay(); p[v[id]].f = &p[eid];
}

std::pair<int,int> query_cover(int u, int v)
{
  p[u].make_root(); p[v].access(); p[v].splay();
  see("query", u, v, p[v].max_cover, p[v].min);
  return std::make_pair(p[v].max_cover, p[v].min);
}

void cover(int id, int delta)
{
  int u = ::u[id], v = ::v[id];
  see("cover", id, u, v, delta);
  p[u].make_root(); p[v].access(); p[v].splay();
  p[v].push_add(delta);
}

void erase_edge(int id)
{
  see("erase_edge", id, u[id], v[id]);
  cm_assert(p[u[id]].find_root() == p[v[id]].find_root());
  is_te[id] = false;
  int eid = n + id;
  p[u[id]].make_root(); p[eid].access(); p[eid].splay(); p[eid].s[0] = p[u[id]].f = nullptr; p[eid].push_up();
  p[v[id]].make_root(); p[eid].access(); p[eid].splay(); p[eid].s[0] = p[v[id]].f = nullptr; p[eid].push_up();
}

int main()
{
  n = sc.next_int(); m = sc.next_int();
  for (int i = 1; i <= m; i++) 
    u[i] = sc.next_int(), v[i] = sc.next_int();

  long long ans = 0;

  int l = 1;
  for (int r = 1; r <= m; r++)
  {
    int u = ::u[r], v = ::v[r];

restart:
    see(l, r);
    auto ru = p[u].find_root(), rv = p[v].find_root();
    see(ru, rv);
    if (ru != rv)
      add_edge(r);
    else 
    {
      auto [c,id] = query_cover(u, v);
      if (c == 0)
      {
        erase_edge(id);   
        add_edge(r);
        cover(id, 1);
      }
      else
      {
        if (is_te[l])
          erase_edge(l);
        else
          cover(l, -1);
        l++;
        goto restart;
      }
    }

    ans += r - l + 1;
  }

  std::cout << ans << std::endl;
  return 0;
}

