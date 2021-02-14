#include <bits/stdc++.h>
template<typename _Tp>
inline void red(_Tp &x) {
  x = 0; bool fg = 0; char ch = getchar();
  while(ch < '0' || ch > '9') {
    if(ch == '-') fg ^= 1;
    ch = getchar(); }
  while(ch >= '0'
    && ch <= '9') x = (x << 1) + (x << 3) + (_Tp)(ch ^ 48), ch = getchar();
  if(fg) x = -x; }
template<typename _Tp> bool umax(_Tp &x, _Tp y) {
  return (x < y) ? (x = y, true) : (false); }
template<typename _Tp> bool umin(_Tp &x, _Tp y) {
  return (x > y) ? (x = y, true) : (false); }
using namespace std;

constexpr int N = 55;
constexpr int MAXN = 2510;
constexpr int fig[4][2] = {{0, 1 }, {-1, 0 }, {1, 0 }, {0, -1 } };

int n, m;
char g[N][N];
bool e[MAXN][MAXN];
bool vis[N][N];
inline int getId(int x, int y) { return (x-1) * m + y; }

struct twosat {
  static constexpr int N = 6000;
  static constexpr int M = 20000000;
  int head[N], pnt[M], nxt[M], E, n;
  int dfn[N], low[N], tis, st[N], top, col[N], co, ans[N];
  void add(int u, int v) {
    E++; pnt[E] = v; nxt[E] = head[u]; head[u] = E; }
  void init(int _n) {
    n = _n; }
  void tarjan(int u) {
    st[++top] = u; dfn[u] = low[u] = ++tis;
    for(int i = head[u]; i; i = nxt[i]) {
      int v = pnt[i];
      if(!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
      else if(!col[v]) low[u] = min(low[u], dfn[v]); }
    if(low[u] == dfn[u]) {
      col[u] = ++co;
      while(st[top] != u) {
        col[st[top]] = co;
        top--; }
      top--; } }
  bool solve() {
    for(int i = 1; i <= 2 * n; i++) if(!dfn[i]) tarjan(i);
    for(int i = 1; i <= n; i++) {
      if(col[i] == col[i + n]) return 0;
      ans[i] = (col[i] > col[i + n]); }
    return 1; }
  void insert(int i, bool a, int j, bool b) { 
    add(i + n * (a ^ 1), j + b * n);
    add(j + n * (b ^ 1), i + a * n); }
  void setval(int i, int v) {
    add(i + (v ^ 1), i + v); }
} S;

inline bool check(int x, int y) {
  return (x >= 1 && x <= n && y >= 1 && y <= m) && g[x][y] != '#'; }

void DFS(int x, int y) {
  if(vis[x][y]) return ;
  vis[x][y] = 1;
  for(int i = 0; i < 4; ++i) {
    int tx = x, ty = y;
    while(check(tx + fig[i][0], ty + fig[i][1])) tx += fig[i][0], ty += fig[i][1];
    DFS(tx, ty); } }

void init() {
  S.init(n * m);
  for(int x = 1; x <= n; ++x) {
    for(int y = 1; y <= m; ++y) {
      if(!check(x, y)) continue;
      memset(vis, 0, sizeof(vis));
      DFS(x, y);
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
        S.insert(getId(tx, y), 1, getId(x, ty),
          1);
      } } }
  for(int u = 1; u <= n * m; ++u) {
    for(int v = 1; v <= n * m; ++v) {
      if(e[u][v] == 0 && e[v][u] == 0) S.insert(u, 0, v, 0); } } }
int main() {
  red(n); red(m);
  for(int i = 1; i <= n; ++i) {
    scanf("%s", g[i] + 1); }
  init();
  bool fg = S.solve();
  puts(fg ? "YES" : "NO");
  return 0; }

