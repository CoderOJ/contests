#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
#include "/home/jack/code/Graph/graph.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

[[maybe_unused]] constexpr int N = 55;
[[maybe_unused]] constexpr int M = 2505;
constexpr std::pair<int, int> fig[4] = {{0, 1 }, {-1, 0 }, {1, 0 }, {0, -1 } };

int n, m;
char g[N][N];
bool e[M][M];
bool vis[N][N];
inline int getId(int x, int y) {
  return (x - 1) * m + y; }

struct twosat {
  [[maybe_unused]] static constexpr int N = 6000;
  [[maybe_unused]] static constexpr int M = 20000000;
  int head[N], pnt[M], nxt[M], E, n;
  int dfn[N], low[N], tis, st[N], top, col[N], co, ans[N];

  void init(int n) {
    this->n = n; }
  void add(int u, int v) {
    E++; pnt[E] = v; nxt[E] = head[u]; head[u] = E; }
  void insert(int i, bool a, int j, bool b) {
    add(i + n * (a ^ 1), j + b * n);
    add(j + n * (b ^ 1), i + a * n); }
  void setval(int i, int v) {
    add(i + (v ^ 1), i + v); };

  void tarjan(int u) {
    st[++top] = u; dfn[u] = low[u] = ++tis;
    for(int i = head[u]; i; i = nxt[i]) {
      int v = pnt[i];
      if(!dfn[v]) tarjan(v), low[u] = std::min(low[u], low[v]);
      else if(!col[v]) low[u] = std::min(low[u], dfn[v]); }
    if(low[u] == dfn[u]) {
      col[u] = ++co;
      while(st[top] != u) { col[st[top]] = co; top--; }
      top--; } }

  bool solve() {
    for(int i = 1; i <= 2 * n; i++) if(!dfn[i]) tarjan(i);
    for(int i = 1; i <= n; i++) {
      if(col[i] == col[i + n]) return false;
      ans[i] = (col[i] > col[i + n]); }
    return true; } } S;

inline bool check(int x, int y) {
  return (x >= 1 && x <= n && y >= 1 && y <= m) && g[x][y] != '#'; }

void dfs(int x, int y) {
  if(vis[x][y]) return ;
  vis[x][y] = 1;
  for (const auto& [dx, dy] : fig) {
    int tx = x, ty = y;
    while(check(tx + dx, ty + dy)) {
      tx += dx; ty += dy; }
    dfs(tx, ty); } }


void preInit() {}
void init() {
  n = sc.n(); m = sc.n();
  repa (i, n) sc.next(g[i] + 1);
  S.init(n * m);
  for(int x = 1; x <= n; ++x) {
    for(int y = 1; y <= m; ++y) {
      if(!check(x, y)) continue;
      memset(vis, 0, sizeof(vis));
      dfs(x, y);
      for(int tx = 1; tx <= n; ++tx)
        for(int ty = 1; ty <= m; ++ty)
          e[getId(x, y)][getId(tx, ty)] = vis[tx][ty];
      if(g[x][y] == 'O') {
        for(int tx = 1; tx <= n; ++tx)
          for(int ty = 1; ty <= m; ++ty)
            if(e[getId(x, y)][getId(tx, ty)] == 0) S.setval(getId(tx, ty), 0); }

      if(g[x][y] == '*') {
        int tx = x, ty = y;
        while(check(tx - 1, y)) --tx;
        while(check(x, ty - 1)) --ty;
        S.insert(getId(tx, y), 1, getId(x, ty), 1); } } }
  for(int u = 1; u <= n * m; ++u) {
    for(int v = 1; v <= n * m; ++v) {
      if(e[u][v] == 0 && e[v][u] == 0) S.insert(u, 0, v, 0); } } }

void solve() {
  puts(S.solve() ? "YES" : "NO"); }

