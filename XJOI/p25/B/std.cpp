#include <bits/stdc++.h>
#include "/home/jack/code/creats/Scanner.h"
#define int long long

const int N = 4 * 1e5 + 100;
int x[N], y[N], kind[N], vi[N], pre[N], suc[N];
int c[N * 2];
int n, w;
struct Node { int x, a, b; } ans[N];

std::vector <Node> a, b;
Node operator+ (Node a,const Node& b) {
  a.a += b.a; a.b += b.b; return a; }
bool operator ==(Node a, Node b) {
  return (a.a == b.a && a.b == b.b); }

inline void del(int x) {
  suc[pre[x]] = suc[x];
  pre[suc[x]] = pre[x]; }
inline void cal(int wh[], int x, int v, int &a, int &b) {
  if (suc[x] == n + 1) return;
  if (kind[x] != kind[suc[x]]) a += v;
  b += v * abs(wh[x] - wh[suc[x]]); }

void solve(int x[], std::vector <Node> &ans) {
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;
  memset(vi, 0, sizeof(vi)); kind[1] = 0; for (int i = 2; i <= n; i++) kind[i] = (x[i] < x[i - 1]);

  int a = 0, b = 0;
  for (int i = 1; i < n; i++) {
    if (kind[i] != kind[i + 1]) q.push(std::make_pair(abs(x[i] - x[i + 1]), i)), a++;
    b += abs(x[i] - x[i + 1]); }

  for (int i = 1; i <= n; i++) { pre[i] = i-1; suc[i] = i+1; }
  ans.push_back((Node){ 0, a, b });
  while (!q.empty()) {
    int l=q.top().first, now = q.top().second; q.pop();
    if (vi[now]) { continue; } vi[suc[now]] = 1;
    cal(x, now, -1, a, b); cal(x, suc[now], -1, a, b); del(suc[now]); cal(x, now, 1, a, b);
    if (suc[now] != n + 1 && kind[now] != kind[suc[now]]) 
      q.push(std::make_pair(abs(x[now] - x[suc[now]]), now));
    ans.push_back((Node) { l, a, b }); } }

signed main() {
  n = sc.n();
  for (int i = 1; i <= n; i++) x[i] = sc.n(), y[i] = sc.n();
  solve(x, a); solve(y, b);
  for (int i = 0; i < (int)a.size(); i++) c[++w] = a[i].x;
  for (int i = 0; i < (int)b.size(); i++) c[++w] = b[i].x;
  std::sort(c + 1, c + 1 + w);
  w = std::unique(c + 1, c + 1 + w) - c - 1;
  for (int i = 0; i < (int)a.size(); i++) 
    a[i].x = std::lower_bound(c + 1, c + 1 + w, a[i].x) - c;
  for (int i = 0; i < (int)b.size(); i++) 
    b[i].x = std::lower_bound(c + 1, c + 1 + w, b[i].x) - c;

  a.push_back((Node) { w + 1, 0, 0 });
  b.push_back((Node) { w + 1, 0, 0 });

  for (int i = 0; i < (int)a.size() - 1; i++) {
    for (int j = a[i].x; j < a[i + 1].x; j++) ans[j] = ans[j] + a[i]; }
  for (int i = 0; i < (int)b.size() - 1; i++) {
    for (int j = b[i].x; j < b[i + 1].x; j++) ans[j] = ans[j] + b[i]; }
  for (int i = 1; i <= w;) {
    int j = i; while (j <= w && ans[i] == ans[j]) j++;
    printf("%lld %lld %lld\n", c[i], ans[i].a, ans[i].b);
    i = j; } }
