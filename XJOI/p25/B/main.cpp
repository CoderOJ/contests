#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
#define int long long

/** My code begins here **/

constexpr int N = 400505;
int x[N], y[N], kind[N], vi[N], pre[N], suc[N], c[N * 2];
int n, w;
struct Node { 
  int x=0, a=0, b=0; 
  Node() =default;
  Node(int x, int a, int b) : x(x), a(a), b(b) {}
  Node operator+ (const Node& B) {
    return Node(x, a+B.a, b+B.b); }
  bool operator== (const Node& B) {
    return a==B.a && b==B.b; }
} ans[N];
std::vector<Node> a, b;

inline void del(int x) {
  suc[pre[x]] = suc[x];
  pre[suc[x]] = pre[x]; }
inline void cal(const int wh[], int x, int v, int &a, int &b) {
  if (suc[x] == n + 1) return;
  if (kind[x] != kind[suc[x]]) a += v;
  b += v * abs(wh[x] - wh[suc[x]]); }

void doit(const int x[], std::vector <Node> &ans) {
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;
  memset(vi, 0, sizeof(vi)); kind[1] = 0; for (int i = 2; i <= n; i++) kind[i] = (x[i] < x[i - 1]);

  int a = 0, b = 0;
  for (int i = 1; i < n; i++) {
    if (kind[i] != kind[i + 1]) q.push(std::make_pair(std::abs(x[i] - x[i + 1]), i)), a++;
    b += std::abs(x[i] - x[i + 1]); }

  for (int i = 1; i <= n; i++) { pre[i] = i-1; suc[i] = i+1; }
  ans.push_back(Node{0,a,b });
  while (!q.empty()) {
    int l=q.top().first, now = q.top().second; q.pop();
    if (vi[now]) { continue; } vi[suc[now]] = 1;
    cal(x, now, -1, a, b); cal(x, suc[now], -1, a, b); del(suc[now]); cal(x, now, 1, a, b);
    if (suc[now] != n + 1 && kind[now] != kind[suc[now]]) 
      q.push(std::make_pair(abs(x[now] - x[suc[now]]), now));
    ans.push_back(Node{l,a,b}); } }

void preInit() { } void init() {
  n = sc.n();
  repa (i,n) { x[i] = sc.n(); y[i] = sc.n(); }
} void solve() {
  doit(x,a); doit(y,b);
  rep (i,(int)a.size()) c[++w] = a[i].x;
  rep (i,(int)b.size()) c[++w] = b[i].x;
  std::sort(c + 1, c + 1 + w); w = std::unique(c + 1, c + 1 + w) - c - 1;
  rep (i,(int)a.size()) a[i].x = std::lower_bound(c + 1, c + 1 + w, a[i].x) - c;
  rep (i,(int)b.size()) b[i].x = std::lower_bound(c + 1, c + 1 + w, b[i].x) - c;
  a.push_back(Node{ w + 1, 0, 0 });
  b.push_back(Node{ w + 1, 0, 0 });

  rep (i,(int)a.size()-1) {
    for (int j = a[i].x; j < a[i + 1].x; j++) ans[j] = ans[j] + a[i]; }
  rep (i,(int)b.size()-1) {
    for (int j = b[i].x; j < b[i + 1].x; j++) ans[j] = ans[j] + b[i]; }
  for (int i = 1; i <= w;) {
    int j = i; while (j <= w && ans[i] == ans[j]) j++;
    printf("%lld %lld %lld\n", c[i], ans[i].a, ans[i].b);
    i = j; }
}
