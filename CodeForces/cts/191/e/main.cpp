#include "/home/jack/code/creats/gpl.hpp"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/Scanner.hpp"
#include "/home/jack/code/creats/log.hpp"
#include "/home/jack/code/creats/range.hpp"
#include "/home/jack/code/creats/util.hpp"
#include "/home/jack/code/creats/Vector.hpp"
// #include "/home/jack/code/creats/STree.hpp"
// #include "/home/jack/code/creats/Tree.hpp"
// #include "/home/jack/code/creats/Graph.hpp"
// #include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"


// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
#define int long long

/** My code begins here **/

constexpr int inf = std::numeric_limits<int>::max() / 16;
constexpr int N = 100005;
int a[N], n, k;
std::vector<std::pair<int,int>> sa;

struct FTree {
  static constexpr int OFFSET = 5;
  int a[N + OFFSET];
  FTree() { memset(a, 0, sizeof(a)); }
  static inline int low(int u) { return u & (-u); }
  void modify(int pos, int val) { pos += OFFSET;
    for (; pos < N+OFFSET; pos+=low(pos)) a[pos] += val; }
  int query(int pos) { pos += OFFSET;
    int val = 0; for (; pos; pos -= low(pos)) { val += a[pos]; }
    return val; } };

int count(int del) {
  FTree st; size_t l = 0; int res = 0;
  for (const auto& [val, id] : sa) {
    while (l < sa.size() && sa[l].first + del <= val) {
      st.modify(sa[l].second, 1); l++; }
    // see(val, id, st.query(id - 1));
    res += st.query(id - 1); }
  return res; }

void preInit() { } 
void init() 
{
  n = sc.n(); k = sc.nl();
  for (int i=0; i<n; i++) a[i] = sc.nextInt();
  std::partial_sum(a, a + n, a);
  sa.emplace_back(0, -1);
  for (int i=0; i<n; i++) sa.emplace_back(a[i], i);
  std::sort(sa.begin(), sa.end());
  // see(sa);
} 

void solve() 
{
  // int l = -100, r = 100;
  int l = -inf, r = inf;
  while (l < r) {
    int mid = l + (r - l + 1) / 2; 
    // see(mid, count(mid));
    if (count(mid) >= k) { l = mid; } 
    else { r = mid - 1; } }
  printf("%lld\n", l);
}
