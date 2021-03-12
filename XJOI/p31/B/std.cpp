#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/base.h"
#include "/home/jack/code/creats/Vector.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

#define rep(i,s,t) for(int i=s;i<=t;++i)

constexpr int N = 100005;
int head[N], e[N << 1], cnt, nxt[N << 1];

inline void add(int u, int v) { nxt[++ cnt] = head[u]; head[u] = cnt; e[cnt] = v; }
inline void link(int u, int v) { add(u, v); add(v, u); }

int n, m;
struct Node {
  long long k, b;
  int l, r;
  Node(long long k = 0, long long b = 0, int l = 0, int r = 0) : k(k), b(b), l(l), r(r) {}
  inline void input() { k=sc.nl(); b=sc.nl(); l=sc.n(); r=sc.n(); }
  inline long long calc(int x) { return (l <= x && x <= r) ? k * x + b : 0; } } a[N], t[N];

struct Point {
  int x, y, pos;
  Point(int x, int y, int pos) : x(x), y(y), pos(pos) {}
  inline bool operator < (const Point &tmp) const {
    return pos > tmp.pos; } };

namespace Block {

constexpr int block = 114;
constexpr int B = N / block + 5;

int bel[N], fst[B], lst[B], mp[B];
Temps::Vector <Point> s[B];

inline void rebuild(int x, int k) {
  mp[x] = 0;
  rep(i, fst[x], lst[x]) if(k >= t[i].l && k <= t[i].r && t[i].calc(k) > t[mp[x]].calc(k)) mp[x] = i; }
inline long long solve(int x, int k) { 
  bool tag = 0;
  while(!s[x].empty() && s[x].back().pos <= k) {
    Point it = s[x].back(); s[x].pop_back();
    int p = it.pos;
    if(!it.x) {
      if(t[mp[x]].calc(p) < t[it.y].calc(p)) mp[x] = it.y; }
    else if(!it.y) tag = 1;
    else {
      if(t[mp[x]].calc(p) < t[it.y].calc(p)) mp[x] = it.y;
      if(t[mp[x]].calc(p) < t[it.x].calc(p)) mp[x] = it.x; } }
  if(tag) rebuild(x, k);
  return t[mp[x]].calc(k); }
inline void build(int x) {
  rep(i, fst[x], lst[x]) {
    rep(j, i + 1, lst[x]) {
      if(t[i].k == t[j].k) continue;
      long long Y = t[j].b - t[i].b, X = t[i].k - t[j].k;
      double num = (1.0 * Y) / (1.0 * X);
      if(num > 1e6) continue;
      s[x].push_back(Point(i, j, floor(num) + 1)); } }
  rep(i, fst[x], lst[x]) {
    s[x].push_back(Point(0, i, t[i].l));
    s[x].push_back(Point(i, 0, t[i].r + 1)); }
  sort(s[x].begin(), s[x].end());
  rebuild(x, -1); }

inline long long query(int l, int r, int x) {
  long long res = 0;
  int L = bel[l], R = bel[r];
  if(L == R) {
    rep(i, l, r) checkMax(res, t[i].calc(x));
    return res; }
  else {
    rep(i, l, lst[L]) checkMax(res, t[i].calc(x));
    rep(i, fst[R], r) checkMax(res, t[i].calc(x));
    rep(i, L + 1, R - 1) checkMax(res, solve(i, x));
    return res; } }
inline void init() {
  rep(i, 1, n) bel[i] = (i - 1) / block + 1;
  rep(i, 1, bel[n]) {
    fst[i] = lst[i - 1] + 1;
    lst[i] = std::min(n, i * block); }
  rep(i, 1, bel[n]) build(i); } }

namespace Tree {
int dep[N], tp[N], fa[N], sz[N], son[N], id[N], tot;
void dfs1(int x, int pre) {
  dep[x] = dep[pre] + 1; fa[x] = pre; sz[x] = 1;
  for (int i = head[x]; i; i = nxt[i]) {
    if(e[i] == pre) continue;
    dfs1(e[i], x);
    if(sz[e[i]] > sz[son[x]]) son[x] = e[i];
    sz[x] += sz[e[i]]; } }
void dfs2(int x, int tt) {
  id[x] = ++ tot; t[tot] = a[x]; tp[x] = tt;
  if(son[x]) dfs2(son[x], tt);
  for (int i = head[x]; i; i = nxt[i]) {
    if(e[i] == fa[x] || e[i] == son[x]) continue;
    dfs2(e[i], e[i]); } }

inline long long query(int x, int y, int z) {
  long long res = 0;
  while(tp[x] ^ tp[y]) {
    if(dep[tp[x]] < dep[tp[y]]) std::swap(x, y);
    checkMax(res, Block::query(id[tp[x]], id[x], z));
    x = fa[tp[x]]; }
  if(id[x] > id[y]) std::swap(x, y);
  return std::max(res, Block::query(id[x], id[y], z)); }
inline void init() {
  dfs1(1, 0); dfs2(1, 1); Block :: init(); } } 

struct Quest {
  int u, v, x, id;
  inline bool operator < (const Quest& tmp) const { return x < tmp.x; }
  inline void input(int qwq) { u=sc.n(); v=sc.n(); x=sc.n(); id = qwq; } } q[N];
long long ans[N];

void preInit() { } void init() {
  n = sc.n(); m = sc.n();
  rep(i,1,n) a[i].input();
  rep(i,1,n-1) { int u=sc.n(), v=sc.n(); link(u, v); }
} void solve() {
  Tree::init();
  rep(i, 1, m) q[i].input(i);
  std::sort(q + 1, q + m + 1);
  rep(i, 1, m) ans[q[i].id] = Tree :: query(q[i].u, q[i].v, q[i].x);
  cout_list_sep = "\n";
  std::cout << Temps::Vector<long long>(ans + 1, ans + n + 1);
}

