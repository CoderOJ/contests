#include "/home/jack/code/creats/gpl.hpp"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/Scanner.hpp"
#include "/home/jack/code/creats/log.hpp"
// #include "/home/jack/code/creats/range.hpp"
#include "/home/jack/code/creats/util.hpp"
// #include "/home/jack/code/creats/Vector.hpp"

// #include "/home/jack/code/creats/STree.hpp"
// #include "/home/jack/code/creats/Tree.hpp"
// #include "/home/jack/code/creats/Graph.hpp"
#define INTM_FAST_64 long long
#include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"


// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int MOD = 998244353;
constexpr int N = 300005;
using Int = Temps::Intm<MOD>;
Int inv[N];
uint64_t hash_cpow[N];

template <class T, size_t N>
struct pool_allocator
{
  T pool[N], *pos = pool;
  T *allocate()
  {
    return pos++;
  }
};

using hash_val_t = uint64_t;
using hash_ord_t = std::pair<size_t, hash_val_t>;
hash_ord_t hash_join(hash_ord_t a, hash_ord_t b)
{
  return hash_ord_t(a.first + b.first,
                    a.second + hash_cpow[a.first] * b.second);
}
hash_ord_t hash_det(hash_ord_t a, hash_ord_t b)
{
  return hash_ord_t(b.first - a.first,
                    b.second - a.second * hash_cpow[b.first - a.first]);
}

struct ftreap_node_t
{
  constexpr static auto ord_cmp = std::greater<hash_ord_t>();
  static std::mt19937_64 rand_eng;
  static pool_allocator<ftreap_node_t, N * 16> allocator;
  hash_ord_t hash_val;
  hash_ord_t hash_sum;
  ftreap_node_t *l = nullptr, *r = nullptr;
  unsigned long weight = rand_eng();
  size_t size = 1;

  void push_up()
  {
    size = 0;
    hash_sum = {0,0};
    if (l != nullptr)
    {
      size += l->size;
      hash_sum = hash_join(hash_sum, l->hash_sum);
    }
    size += 1;
    hash_sum = hash_join(hash_sum, hash_val);
    if (r != nullptr)
    {
      size += r->size;
      hash_sum = hash_join(hash_sum, r->hash_sum);
    }
  }
};
std::mt19937_64 ftreap_node_t::rand_eng(18100820);
pool_allocator<ftreap_node_t, N * 16> ftreap_node_t::allocator;
extern ftreap_node_t *t[N];

void ftreap_join(ftreap_node_t *&u, ftreap_node_t *l, ftreap_node_t *r)
{
  if (l == nullptr) { u = r; return; }
  if (r == nullptr) { u = l; return; }
  if (l->weight > r->weight)
    ftreap_join((u = l)->r, l->r, r);
  else
    ftreap_join((u = r)->l, l, r->l);
  u->push_up();
}

void ftreap_split(ftreap_node_t *&l, ftreap_node_t *&r,
                  ftreap_node_t *u, hash_ord_t thr)
{
  if (u == nullptr)
  {
    l = r = nullptr;
    return;
  }
  if (ftreap_node_t::ord_cmp(u->hash_val, thr))
    ftreap_split((l = u)->r, r, u->r, thr);
  else
    ftreap_split(l, (r = u)->l, u->l, thr);
  u->push_up();
}

// return key count (before)
size_t ftreap_erase_once(ftreap_node_t *&u, hash_ord_t val)
{
  // see("erase", &u - t, val);
  ftreap_node_t *a, *b, *c;
  ftreap_split(a, b, u, val);
  val.second--;
  ftreap_split(b, c, b, val);
  size_t res = b->size;
  ftreap_join(b, b->l, b->r);
  ftreap_join(a, a, b);
  ftreap_join(u, a, c);
  return res;
}

// return key count (after)
size_t ftreap_insert(ftreap_node_t *&u, hash_ord_t val)
{
  // see("insert", &u - t, val);
  ftreap_node_t *a, *b, *c, *d;
  d = ftreap_node_t::allocator.allocate();
  d->hash_val = d->hash_sum = val;
  ftreap_split(a, b, u, val);
  val.second--;
  ftreap_split(b, c, b, val);
  ftreap_join(b, b, d);
  size_t res = b->size;
  ftreap_join(a, a, b);
  ftreap_join(u, a, c);
  return res;
}

hash_ord_t ftreap_first(ftreap_node_t *u)
{
  while (u->l != nullptr)
    u = u->l;
  return u->hash_val;
}

// lct maintains the hash tuple of one's wson
struct lct_node_t
{
  lct_node_t *f = nullptr, *s[2] = {nullptr, nullptr};
  hash_ord_t val = {0,0}, join = {0,0};
  Int ans = 1, ans_mul = 1;
  bool is_root() { return f == nullptr || (f->s[0] != this && f->s[1] != this); }
  bool get_son() { return f->s[1] == this; }
  void push_join(hash_ord_t det) { val = hash_join(det, val); join = hash_join(det, join); }
  void push_mul(Int det_mul) { ans *= det_mul; ans_mul *= det_mul; }
  void push_down() 
  { 
    if (s[0] != nullptr) { s[0]->push_join(join); s[0]->push_mul(ans_mul); }
    if (s[1] != nullptr) { s[1]->push_join(join); s[1]->push_mul(ans_mul); }
    join = {0,0}; ans_mul = 1;
  }
  void push()
  {
    if (!is_root()) f->push();
    push_down();
  }
  void rotate()
  {
    lct_node_t *uu = this, *ff = f, *aa = ff->f;
    bool ss = uu->get_son();
    if (!ff->is_root()) aa->s[ff->get_son()] = uu;
    ff->f = uu; ff->s[ss] = uu->s[!ss];
    uu->f = aa; uu->s[!ss] = ff;
    if (ff->s[ss] != nullptr) ff->s[ss]->f = ff;
  }
  void splay()
  {
    push();
    while (!is_root())
    {
      if (f->is_root()) { rotate(); break; }
      (is_root() == f->is_root() ? f : this)->rotate();
      rotate();
    }
  }
  void access()
  {
    lct_node_t *uu = this, *ss = nullptr;
    while (uu != nullptr)
    {
      uu->splay(); uu->s[1] = ss;
      ss = uu; uu = uu->f;
    }
  }
};


lct_node_t p[N];
lct_node_t pp[N];
ftreap_node_t *t[N];
int fa[N], dep[N], ws[N];

void lct_link(int u)
{
  // see("LCT: link", u);
  p[u].access();
  p[u].splay();
  p[u].f = &p[fa[u]];
}

void lct_cut(int u)
{
  // see("LCT: cut", u);
  p[fa[u]].access();
  p[u].splay();
  p[u].f = nullptr;
}

void lct_reset(int u, hash_ord_t val)
{
  p[u].splay();
  p[u].val = val;
}

hash_ord_t get_hash(int u)
{
  p[u].access();
  p[u].splay();
  hash_ord_t ws_hash = p[u].val;
  hash_ord_t ot_hash = t[u]->hash_sum;
  see(u, ws_hash, ot_hash);
  return hash_join(ws_hash, ot_hash);
}

int get_top(int u)
{
  p[u].access();
  p[u].splay();
  lct_node_t *pos = &p[u];
  while (pos->s[0] != nullptr)
    pos = pos->s[0];
  pos->splay();
  return static_cast<int>(pos - p);
}

size_t get_size(int u)
{
  p[u].splay();
  return p[u].val.first + t[u]->hash_sum.first;
}

size_t get_smax_size(int u)
{
  if (t[u]->size == 1)
    return 0;
  return ftreap_first(t[u]).first;
}

void update_hash(int u, hash_ord_t u_ori, hash_ord_t u_cur)
{
  see(u, u_ori, u_cur);
  if (u == 1) return;

  const int f = fa[u];
  const size_t u_size = get_size(u);

  const hash_ord_t f_ori = get_hash(f);
  if (ws[f] != 0)
  {
    size_t fs_size = get_size(ws[f]);
    if (fs_size <= u_size)
    {
      assert(fs_size == u_size);
      ftreap_insert(t[f], get_hash(ws[f]));
      lct_cut(ws[f]);
      lct_reset(f, {0,0});
      ws[f] = 0;
    }
  }
  if (u_ori != (hash_ord_t){0,0})
  {
    const size_t ori_cnt = ftreap_erase_once(t[f], u_ori);
    // see("mod_div", f, ori_cnt);
    pp[f].access();
    pp[f].splay();
    pp[f].push_mul(inv[ori_cnt]);
  }
  if (ws[f] == 0 && get_smax_size(f) < u_size)
  {
    lct_link(u);
    lct_reset(f, u_cur);
    // see(f, u_cur);
    ws[f] = u;
  }
  else
  {
    size_t cur_cnt = ftreap_insert(t[f], u_cur);
    // see("mod_mul", f, cur_cnt);
    pp[f].access();
    pp[f].splay();
    pp[f].push_mul(cur_cnt);
  }
  const hash_ord_t f_cur = get_hash(f);

  int top = get_top(f);
  hash_ord_t top_ori, top_cur;
  if (top != f)
  {
    top_ori = get_hash(top);
    const hash_ord_t det = hash_det(f_ori, f_cur);
    see(det);
    int ff = fa[f];
    p[ff].access();
    p[ff].splay();
    p[ff].push_join(det);
    top_cur = get_hash(top);
  }
  else
  {
    top_ori = f_ori;
    top_cur = f_cur;
  }
  update_hash(top, top_ori, top_cur);
}

void preInit() 
{ 
  hash_cpow[0] = 1;
  hash_cpow[1] = 82061943317773333ull;
  for (int i = 2; i < N; i++)
    hash_cpow[i] = hash_cpow[i - 1] * hash_cpow[1];
  inv[1] = 1;
  for (int i = 2; i < N; i++)
    inv[i] = inv[MOD % i] * (MOD - MOD / i);
} 

int m;
void init() 
{ 
  m = sc.n(); 
  dep[1] = 1;
  ftreap_insert(t[1], {1,1});
}

void solve() 
{
  int u = 2;
  for (int i = 0; i < m; i++)
  {
    int opt = sc.n();
    if (opt == 0)
    {
      int f = sc.n(); 
      see("add", f, u);
      fa[u] = f;
      pp[u].f = &pp[f];
      dep[u] = dep[f] + 1;
      ftreap_insert(t[u], {1,dep[u]});
      update_hash(u, {0,0}, {1,dep[u]});
      u++;
    }
    else
    {
      int u = sc.n();
      pp[u].splay();
      std::cout << pp[u].ans << std::endl;
    }
  }
}
