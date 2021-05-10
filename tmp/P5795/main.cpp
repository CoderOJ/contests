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

constexpr int N = 300005;
constexpr int B = 31;

namespace Trie {

struct Node;
extern Node null_node;
constexpr Node *null = &null_node;

struct Node {
  Node *s[2] = {null, null};
  int cnt = 0; 
  void *operator new(size_t); };

Node null_node;

static char tn_pool[N * 32 * sizeof(Node)];
static struct Node *tn_pool_top = reinterpret_cast<Node*>(tn_pool);
void *Node::operator new(size_t) { return tn_pool_top++; }

void insert(Node *origin, Node *pos, int mask) {
  for (int i=B-1; i>=0; i--) {
    int cur = (mask >> i) & 1;
    pos->cnt = origin->cnt + 1;
    pos->s[!cur] = origin->s[!cur], pos->s[cur] = new Node();
    pos = pos->s[cur], origin = origin->s[cur]; }
  pos->cnt++; }

} /* namespace Trie */

using Trie::Node;
using Trie::insert;

int n, m, a[N], b[N];
Node *b2t[N];
std::pair<Node*, Node*> a2t[N];

void preInit() { } void init() {
  n = sc.n(), m = sc.n();     
  for (int i=0; i<n; ++i) a[i] = sc.n();
  for (int i=0; i<m; ++i) b[i] = sc.n();
} void solve() {
  b2t[0] = new Node();
  for (int i=0; i<m; ++i) 
    insert(b2t[i], b2t[i + 1] = new Node(), b[i]);

  int qs = sc.n();
  for (int i=0; i<qs; ++i) {
    int la=sc.n()-1, ra=sc.n(), lb=sc.n()-1, rb=sc.n(), k=sc.n();
    for (int i=la; i<ra; ++i) a2t[i] = std::make_pair(b2t[lb], b2t[rb]);
    int ans = 0;
    for (int i=B-1; i>=0; --i) {
      int p1cnt = 0;
      for (int j=la; j<ra; ++j) {
        int cur = (a[j] >> i) & 1;
        p1cnt += a2t[j].second->s[!cur]->cnt - 
                 a2t[j].first ->s[!cur]->cnt; }

      int next = 1;
      if (p1cnt < k) { k -= p1cnt; next = 0; }
      else { ans ^= (1 << i); }
      for (int j=la; j<ra; ++j) {
        int cur = ((a[j] >> i) & 1) ^ next;
        a2t[j].first  = a2t[j].first ->s[cur]; 
        a2t[j].second = a2t[j].second->s[cur]; } }
    printf("%d\n", ans); }
}
