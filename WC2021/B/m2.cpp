#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"

/** My code begins here **/

const int M = 10;
const int N = 50005;
const int E = 50005;
const int MOD = 1000000007;
char s[E]; int match[E], n, m, l;
int a[M][N];

const int ETypeMin = -1;
const int ETypeMax = -2;
const int ETypeAny = -3;
const int root = 0;
int Er_cnt = 1;

struct ETree {
  int sl, sr, opt;
  ETree() { sl=sr=-1; opt=0; }
  void parse(int l, int r);
} Er[E];

void ETree::parse(int l, int r) {
  if (l == r) { opt = s[l] - '0'; return; }
  if (s[l] == '(' && match[l] == r) {
    parse(l + 1, r - 1); return; }
  int mid = match[r] - 1;
  if (s[mid] == '<') { opt = ETypeMin; }
  else if (s[mid] == '>') { opt = ETypeMax; }
  else { opt = ETypeAny; }
  sl = Er_cnt++; Er[sl].parse(l, mid-1);
  sr = Er_cnt++; Er[sr].parse(mid+1, r); }

namespace BruteNQ {
const int MAXN = 5005;
int ua[MAXN][MAXN];
void dfs(int u = root) {
  if (Er[u].opt >= 0) {
    memcpy(ua[u], a[Er[u].opt], sizeof(**ua) * n); }
  else if (Er[u].opt == ETypeMax) { dfs(Er[u].sl); dfs(Er[u].sr); 
    rep (i,n) ua[u][i] = std::max(ua[Er[u].sl][i], ua[Er[u].sr][i]); }
  else { dfs(Er[u].sl); dfs(Er[u].sr); 
    rep (i,n) ua[u][i] = std::min(ua[Er[u].sl][i], ua[Er[u].sr][i]); } }
void main() {
  dfs();
  int ans = 0;
  rep (i,n) (ans += ua[root][i]) %= MOD; 
  printf("%d\n", ans);
}
} /* BruteNQ */

namespace N2 {
int g_d;
inline int imin(int x, int y) {
  return a[x][g_d] < a[y][g_d] ? x : y; } 
inline int imax(int x, int y) {
  return a[x][g_d] > a[y][g_d] ? x : y; } 
struct Map {
  int prob[10];
  void reset() { memset(prob, 0, sizeof(prob)); }
  void set(int bel) { prob[bel] = 1; }
  void mergeMin(const Map& a, const Map& b) {
    rep (i,10) rep (j,10) {
      (prob[imin(i, j)] += (1ll * a.prob[i] * b.prob[j]) % MOD) %= MOD; } }
  void mergeMax(const Map& a, const Map& b) {
    rep (i,10) rep (j,10) {
      (prob[imax(i, j)] += (1ll * a.prob[i] * b.prob[j]) % MOD) %= MOD; } }
  void mergeMinMax(const Map& a, const Map& b) {
    rep (i,10) rep (j,10) {
      int del = (1ll * a.prob[i] * b.prob[j]) % MOD; 
      (prob[i] += del) %= MOD; (prob[j] += del) %= MOD; } }
};
const int MAXL = 5005;
Map ua[MAXL];
void dfs(int u = root) {
  ua[u].reset();
  if (Er[u].opt >= 0) { ua[u].set(Er[u].opt); return; }
  dfs(Er[u].sl); dfs(Er[u].sr);
  if (Er[u].opt == ETypeMin) { ua[u].mergeMin(ua[Er[u].sl], ua[Er[u].sr]); }
  else if (Er[u].opt == ETypeMax) { ua[u].mergeMax(ua[Er[u].sl], ua[Er[u].sr]); }
  else { ua[u].mergeMinMax(ua[Er[u].sl], ua[Er[u].sr]); } }
void main() {
  int ans = 0;
  rep (i,n) { g_d = i; 
    dfs(); 
    rep (j, 10) ans = (ans + 1ll * ua[root].prob[j] * a[j][i]) % MOD; }
  printf("%d\n", ans); 
}
};

void preInit() { 
#ifndef __LOCALE__
  freopen("expr.in", "r", stdin);
  freopen("expr.out", "w", stdout);
#endif
} void init() {
  scanf("%d%d", &n, &m); 
  rep (i,m) rep (j,n) scanf("%d", &a[i][j]);
  scanf("%s", s); l = std::strlen(s);
  std::stack<int> lb;
  rep (i,l) {
    if (s[i] == '(') { lb.push(i); }
    else if (s[i] == ')') {
      int lp = lb.top(); lb.pop();
      match[lp] = i; match[i] = lp; }
    else { match[i] = i; } }
  Er[root].parse(0, l-1);
} void solve() {
  { N2::main(); return; }
}
