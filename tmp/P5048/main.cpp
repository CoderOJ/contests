#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
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

constexpr int N = 500005;
constexpr int BLEN = 701;
int a[N], n, q;

template <class ForwardIterator, class OutputIterator>
void dissociate(ForwardIterator __begin, ForwardIterator __end, OutputIterator __dest) {
  Temps::Vector<typename std::iterator_traits<ForwardIterator>::value_type> values(__begin, __end); 
  std::sort(values.begin(), values.end()); std::unique(values.begin(), values.end()); 
  while (__begin != __end) {
    *__dest = std::distance(values.begin(), std::lower_bound(values.begin(), values.end(), *__begin));
    __dest++; __begin++; } }

Temps::Vector<int> appears[N];
int appear_id[N];
int bel[N], left[N], bn;
int cnt[N / BLEN + 2][N / BLEN + 2];

void preInit() { } void init() {
  n = sc.n(); q = sc.n();
  rep (i,n) { a[i] = sc.n(); } dissociate(a, a+n, a);
  rep (i,n) { appear_id[i] = appears[a[i]].size(); appears[a[i]].push_back(i); }
  bn = (n - 1) / BLEN + 1; rep (i,bn) left[i] = i * BLEN;
  rep (i,n) bel[i] = i / BLEN;
  see(bn);
  rep (i,bn) {
    static int cnt[N]; std::fill(cnt, cnt+n, 0);
    int pos = 0;
    for (int j=left[i]; j<n; ++j) {
      cnt[a[j]]++; checkMax(pos, cnt[a[j]]);
      ::cnt[i][bel[j] + 1] = pos; } }
} void solve() {
  int last_ans = 0;
  rep (_case, q) {
    int l = (sc.n() ^ last_ans) - 1, r = sc.n() ^ last_ans;
    int p_ans = cnt[bel[l] + 1][bel[r]];
    for (int i=l; i<left[bel[l] + 1]; ++i) {
      while (appear_id[i] + p_ans < static_cast<int>(appears[a[i]].size()) &&
             appears[a[i]][appear_id[i] + p_ans] < r) { p_ans++; } }
    for (int i=left[bel[r]]; i<r; ++i) {
      while (appear_id[i] - p_ans >= 0 && 
             appears[a[i]][appear_id[i] - p_ans] >= l) { p_ans++; } }
    printf("%d\n",last_ans = p_ans); }
}
