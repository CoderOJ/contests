#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

#define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

using Temps::Vector;
[[maybe_unused]] constexpr int MOD = 1000000007;
constexpr int N = 2005;
int n, m, q;
Vector<int> up[N][N], right[N][N];
int umax[N][N], rmax[N][N];

void initUR() {
  for (int i=0; i<q; ++i) {
    int x1=sc.n(), y1=sc.n(), x2=sc.n(), y2=sc.n();
    right[x1][y1].push_back(x2); right[x1][y2].push_back(-x2);
    up[x1][y1].push_back(y2); up[x2][y1].push_back(-y2); }
  
  for (int i=1; i<=n; ++i) {
    std::multiset<int> rs{i};
    for (int j=1; j<=m; ++j) {
      for (const int d: right[i][j]) {
        if (d > 0) { rs.insert(d); }
        else { rs.erase(rs.find(-d)); } }
      rmax[i][j] = *rs.rbegin(); } }

  for (int j=1; j<=m; ++j) {
    std::multiset<int> us{j};
    for (int i=1; i<=n; ++i) {
      for (const int d: up[i][j]) {
        if (d > 0) { us.insert(d); }
        else { us.erase(us.find(-d)); } }
      umax[i][j] = *us.rbegin(); } }
  
  for (int i=1; i<=n; ++i) {
    for (int j=1; j<=m; ++j) {
      checkMax(umax[i][j], umax[i][j-1]);
      checkMax(rmax[i][j], rmax[i-1][j]); } }
}

struct State { int val, num; State(int val=0, int num=0) : val(val), num(num) {} };
std::ostream& operator<< (std::ostream& out, const State p) {
  out << "(val = " << p.val << ", num = " << p.num << ")"; return out; }

struct Queue {
  struct Node : public State { 
    int cnt; Node() =default;
    explicit Node(const State state, int cnt=1) : State(state), cnt(cnt) {} };
  Node p[N], *begin=p, *end=p;
  void clear() { begin = end = p; }

  void push(const State u) {
    // slog("%p push %d,%d", this, u.val, u.num);
    while (end != begin && (end-1)->val < u.val) { --end; }
    if (begin == end) { *end++ = Node(u); }
    else if ((end-1)->val > u.val) { *end++ = Node(u); }
    else { (end-1)->num = ((end-1)->num + u.num) % MOD; (end-1)->cnt++; } }
  State front() const { 
    if (begin == end) { return State{0,0}; }
    return *begin; }
  void pop(const State u) {
    // slog("%p pop %d,%d", this, u.val, u.num);
    if (begin->val > u.val) { return; }
    begin->cnt--; begin->num = (begin->num + MOD - u.num) % MOD;
    if (begin->cnt == 0) { begin++; } }

} qr[N];
int qr_r[N];

inline State max(const State a, const State b) {
  if (a.val == b.val) {
    return State{a.val, (a.num + b.num) % MOD}; }
  return a.val > b.val ? a : b; }

State dp[N][N];

int Q = 0, S = 0;
void preInit() { } void init() {
  n=sc.n(); m = sc.n(); q = sc.n();
  S += n * m; Q += q;
  for (int i=1; i<=n; ++i) for (int j=1; j<=m; ++j) {
    up[i][j].clear(); right[i][j].clear(); } 
}

void solve() {
  initUR();
  for (int j=1; j<=m; ++j) { dp[n][j] = State{1,1}; qr[j].clear(); qr_r[j] = n; }

  for (int i=n-1; i>=1; --i) {
    dp[i][m] = State{1,1}; Queue qu; int qu_u=m;
    for (int j=m-1; j>=1; --j) {
      if (j+2 <= m) { qu.push(dp[i+1][j+2]); }
      while (qu_u > umax[i][j] && qu_u-j >= 2) { qu.pop(dp[i+1][qu_u--]); }
      qr[j].push(dp[i+1][j+1]);
      while (qr_r[j] > rmax[i][j]) { qr[j].pop(dp[qr_r[j]--][j+1]); }
      dp[i][j] = max(State{0, 1}, max(qu.front(), qr[j].front()));
      dp[i][j].val += 1; } }

  State ans{0,1};
  for (int i=1; i<=n; ++i) for (int j=1; j<=m; ++j) {
    ans = max(ans, dp[i][j]); }

  printf("%d %d\n", ans.val, ans.num);
}

/*
struct ATEXIT {
  ~ATEXIT() { fprintf(stderr, "Q = %d, S = %d\n", Q, S); }
} AT;
*/
