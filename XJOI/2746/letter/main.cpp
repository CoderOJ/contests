#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
#define INTM_FAST_64 long long
#include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 1000005;
// constexpr int M = 12;

template <int MOD, int seed>
struct Hash {
  using value_type = Temps::Intm<MOD>;
  value_type wei[N], inv[N], val[N];

  Hash() {
    wei[0] = inv[0] = 1; wei[1] = seed, inv[1] = wei[1].inv();
    for (int i=2; i<N; ++i) {
      wei[i] = wei[i-1] * wei[1]; inv[i] = inv[i-1] * inv[1]; } }
  inline int low(int u) { return u & (-u); }
  void modify(int pos, int _delta) {
    auto delta = wei[pos] * _delta;
    while (pos < N) { 
      val[pos] += delta; pos += low(pos); } }
  value_type query(int r) {
    value_type res = 0;
    while (r) {
      res += val[r]; r -= low(r); } 
    return res; }
  value_type query(int l, int r) {
    return (query(r) - query(l - 1)) * inv[l - 1]; }
};

Hash<1019260817, 113> hash;
int s[N], p[N], v[N];
int n, m;
long long pre_ans;

bool is_sub4() {
  for (int i=1; i<=n; ++i) 
    if (p[i] != n - i + 1)
      return false;
  return true; }

bool less(int p1, int p2) {
  for (int i=0; i<5; ++i)
    if (s[p1 + i] != s[p2 + i])
      return s[p1 + i] < s[p2 + i];
  int l = 0, r = std::min(n-p1+1, n-p2+1);
  while (l < r) {
    int mid = (l + r + 1) / 2;
    if (hash.query(p1, p1+mid-1) == hash.query(p2, p2+mid-1)) { l = mid; }
    else { r = mid - 1; } }
  return s[p1 + l] < s[p2 + l]; }

struct heap {
  std::priority_queue<int, std::vector<int>, std::greater<int>> up;
  std::priority_queue<int, std::vector<int>, std::less<int>> down;

  int mid() { return down.top(); }
  void insert(int x) {
    if (down.size() && x > down.top()) {
      up.push(x); if (up.size() > down.size()) { down.push(up.top()); up.pop(); } }
    else { down.push(x); if (down.size() > up.size() + 1) { up.push(down.top()); down.pop(); } } }
  std::size_t size() { return up.size() + down.size(); }

  long long destory_and_count() {
    long long res = 0;
    int key = mid();
    if (key < 1) key = 1;
    if (key > m) key = m;
    while (up.size()) { res += std::abs(up.top() - key); up.pop(); }
    while (down.size()) { res += std::abs(key - down.top()); down.pop(); }
    return res; }
};

void merge(heap& a, heap& b) {
  if (a.size() < b.size())
    std::swap(a, b);
  while (b.up.size()) {
    a.insert(b.up.top()); b.up.pop(); }
  while (b.down.size()) {
    a.insert(b.down.top()); b.down.pop(); } }

void preInit() { } 
void init() 
{
  n = sc.n(); m = sc.n();
  for (int i=1; i<=n; ++i) p[i] = sc.n();
  for (int i=1; i<=n; ++i) v[i] = sc.n();
  for (int i=1; i<=n; ++i) 
    if (v[i] == 0) 
      v[i] = 1, pre_ans++;
} 

heap stack[N], *stack_top = stack;

void solve() 
{
  if (!is_sub4()) {
    for (int i=1; i<=n; ++i) { hash.modify(p[i], i); s[p[i]] = i; }
    s[n + 1] = 0, s[p[1]] = 1;
    int cur = 1;
    for (int i=2; i<=n; ++i) {
      hash.modify(p[i], cur - s[p[i]]); s[p[i]] = cur;
      if (!less(p[i-1], p[i])) {
        hash.modify(p[i], 1); s[p[i]]++; cur++; m--; }
      v[p[i]] -= cur - 1; } } else {
    std::fill(s + 1, s + n + 1, 1); }
  // logArray(s + 1, s + n + 1);

  if (m < 1) { puts("-1"); return; }
  // if (*std::max_element(v + 1, v + n + 1) == 1) {
  //   printf("%lld\n", std::accumulate(s + 1, s + n + 1, 0ll));
  //   return; }

  for (int i=1; i<=n; ++i) {
    stack_top->insert(v[p[i]]);
    stack_top++;
    while (stack_top - stack >= 2 && stack_top[-1].mid() <= stack_top[-2].mid()) {
      merge(stack_top[-2], stack_top[-1]), stack_top--; } }
  long long ans = 0;
  for (heap *i = stack; i < stack_top; ++i) {
    ans += i->destory_and_count(); }
  printf("%lld\n", pre_ans + ans);
}
