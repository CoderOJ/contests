#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int C = 10;

struct Trie {
  struct Node {
    Node *next[C] = { nullptr, nullptr, nullptr, nullptr, nullptr,
                      nullptr, nullptr, nullptr, nullptr, nullptr, };
    std::vector<int> ans;
    size_t cnt = 0;

    void increase(int event_id) {
      if (cnt == ans.size()) 
        ans.push_back(event_id);
      cnt++; }
    void decrease() { cnt--; }
  };

  Node *root = new Node();
  
  void increase(const char *s, int event_id) {
    Node *pos = root;
    for (; *s; ++s) {
      pos->increase(event_id);
      if (pos->next[*s - 'a'] == nullptr)
        pos->next[*s - 'a'] = new Node();
      pos = pos->next[*s - 'a']; } 
    pos->increase(event_id); }

  void decrease(const char *s) {
    Node *pos = root;
    for (; *s; ++s) {
      pos->decrease();
      pos = pos->next[*s - 'a']; } 
    pos->decrease(); }

  int query(const char *s, size_t kth) {
    Node *pos = root;
    for (; *s; ++s) {
      pos = pos->next[*s - 'a']; 
      if (pos == nullptr) { return -1; } }
    return pos->ans.size() > kth ? pos->ans[kth] : -1; } 
} T;

char name[65];
int n;

void preInit() { } void init() {
  n = sc.n();
} void solve() {
  int last_ans = 0;
  for (int i=1; i<=n; ++i) {
    int opt = sc.n(); sc.next(name); 
    if (opt == 1) { T.increase(name, i); }
    else if (opt == 2) { T.decrease(name); }
    else { int a=sc.n(), b=sc.n(), c=sc.n(); 
      size_t ask = (size_t)((1ll * a * std::abs(last_ans) + b) % c);
      printf("%d\n", last_ans = T.query(name, ask)); } }
}
