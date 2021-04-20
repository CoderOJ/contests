#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
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

#define long long long

constexpr int MOD = 1000000007;
typedef std::pair<int, int> pii;
inline int upd(const int x) {
  return x + (x >> 31 & MOD); }
inline void reduce(int&x) { x -= MOD, x += x >> 31 & MOD; }
inline void add(int&x, const int y) { x = upd((x + y) % MOD); }
constexpr int N = 2005;

int n, m, T, mxv, ans, dis[N][N];
std::pair<int, int>li[N];
int et, hed[N];
struct edge { int nx, to, vl; } e[N << 1];
struct Node { int x, y, z;
  Node(int x_, int y_, int z_) { x = x_, y = y_, z = z_; } };

std::vector<Node>E;

void add_edge(int u, int v, int d) {
  e[++et].nx = hed[u], e[et].to = v, e[et].vl = d, hed[u] = et; }

void Dij() {
  static bool vis[N][N];
  memset(vis, 0, sizeof(vis)); memset(dis, -1, sizeof(dis));
  std::queue<std::pair<int, int> >q;
  q.push(std::make_pair(1, dis[1][0] = 0)); vis[1][0] = 1;
  while(!q.empty()) {
    std::pair<int, int>now = q.front(); q.pop();
    int u = now.first, t = now.second;
    if(t == n)continue;
    for(int i = hed[u]; i; i = e[i].nx) {
      int v = e[i].to;
      if(dis[v][t + 1] < dis[u][t] + e[i].vl) {
        dis[v][t + 1] = dis[u][t] + e[i].vl;
        if(!vis[v][t + 1])q.push(std::make_pair(v, t + 1)), vis[v][t + 1] = 1; } } } }

int calc(long a1, long d, long n) {
  static const int iv2 = (MOD + 1) >> 1;
  return 1ll * (a1 + a1 + (n - 1) * d) % MOD * n % MOD * iv2 % MOD; }

void preInit(){}
void init() {
  n = sc.n(); m = sc.n(); T = sc.nl();
  E.push_back(Node(114, 514, 1919810));
  for (int i=1; i<=m; ++i) {
    int x=sc.n(), y=sc.n(), z=sc.n();
    add_edge(x, y, z), add_edge(y, x, z); 
    E.push_back(Node(x, y, z));
    mxv = std::max(mxv, z); } }

void solve() {
  Dij();
  for (int i=1; i<=m; ++i) li[i].second = -2e9 - 5, li[i].first = E[i].z;
  for (int i=1; i<=std::min(n, T); ++i) {
    for (int j=1; j<=m; ++j) {
      int x = E[j].x, y = E[j].y, z = E[j].z;
      if(~dis[x][i])li[j].second = std::max(dis[x][i] - i * z, li[j].second);
      if(~dis[y][i])li[j].second = std::max(dis[y][i] - i * z, li[j].second); }
    long res = 0;
    for(int j=1; j<=m; ++j)res = std::max(res, 1ll * li[j].first * i + li[j].second);
    reduce(ans += res % MOD); }

  for (int i=1; i<=m; ++i) {
    int L = n + 1, R = T;
    for (int j=1; j<=m; ++j) {
      if(i == j) continue;
      if(L > R) break;

      if(li[i].first == li[j].first) {
        if(li[i].second < li[j].second) { R = 114514, L = 1919810; break; }
        else if(li[i].second == li[j].second && i > j) { R = 114514, L = 1919810; break; }
        else continue; }
      if(li[i].first > li[j].first)L = std::max(L,
            (li[j].second - li[i].second) / (li[i].first - li[j].first) + 1);
      else R = std::min(R, (li[j].second - li[i].second) / (li[i].first -
              li[j].first)); }
    if(L > R) continue;
    reduce(ans += calc(1ll * li[i].first * L % MOD + li[i].second, li[i].first, R - L + 1)); }
  std::cout << ans << std::endl; }
