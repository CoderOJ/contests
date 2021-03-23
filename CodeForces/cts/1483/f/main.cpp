#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"
#include "/home/jack/code/creats/pipe.h"

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

constexpr int N = 1000005;
constexpr int B = 20;
constexpr int C = 26;
using namespace Temps;

struct GSAM {
  struct Node {
    int next[C], link=-1, len=0, end_cnt=0;
    Temps::Vector<int> e; int fa[B]; int la_len=-1;
    Node() { memset(next, -1, sizeof(next)); memset(fa, -1, sizeof(fa)); }
  } p[N * 2];

  static constexpr int root = 0;
  int last = root, cnt = last + 1;

  void clear() { while (cnt--) { p[cnt] = Node(); } last=root; cnt=root+1; }
  void reset() { p[last].end_cnt++; last = root; }

  // this part is used as normal SAM
  void insert(std::size_t c) {
    int cur = cnt++; 
    p[cur].len = p[last].len + 1; 
    int pos = last;
    while (pos != -1 && p[pos].next[c] == -1) {
      p[pos].next[c] = cur; pos = p[pos].link; }
    if (pos == -1) { p[cur].link = root; }
    else { int q = p[pos].next[c];
      if (p[q].len == p[pos].len + 1) { p[cur].link = q; }
      else {
        int clone = cnt++;
        p[clone] = p[q]; 
        p[clone].len = p[pos].len + 1; 
        p[clone].end_cnt = 0;
        p[q].link = p[cur].link = clone;
        while (pos != -1 && p[pos].next[c] == q) {
          p[pos].next[c] = clone; pos = p[pos].link; } } }
    last = cur; }
  void dfs_fa(int u) {
    p[u].fa[0] = p[u].link;
    for (int b: range(B-1)) if (p[u].fa[b] != -1) {
      p[u].fa[b + 1] = p[ p[u].fa[b] ].fa[b]; }
    for (int v: p[u].e) { dfs_fa(v); } }
  void dfs_len(int u) {
    for (int v: p[u].e) {
      dfs_len(v); checkMax(p[u].la_len, p[v].la_len); } }
  int get(int u, int len) {
    for (int b=B-1;b>=0;b--) {
      if (p[u].fa[b] != -1 && p[p[u].fa[b]].len >= len) {
        u = p[u].fa[b]; } }
    return u; }


  // this part is used as general SAM
  void ginsert(std::size_t c) {
    { if (int q = p[last].next[c]; q != -1) {
        if (p[q].len == p[last].len + 1) { last = q; }
        else { 
          int clone = cnt++;
          p[clone] = p[q];
          p[clone].len = p[last].len + 1;
          p[clone].end_cnt = 0;
          p[q].link = clone;
          while (last != -1 && p[last].next[c] == q) {
            p[last].next[c] = clone; last = p[last].link; }
          last = clone; }
        return; } }
    int cur = cnt++; 
    p[cur].len = p[last].len + 1; 
    int pos = last;
    while (pos != -1 && p[pos].next[c] == -1) {
      p[pos].next[c] = cur; pos = p[pos].link; }
    if (pos == -1) { p[cur].link = root; }
    else { int q = p[pos].next[c];
      if (p[q].len == p[pos].len + 1) { p[cur].link = q; }
      else {
        int clone = cnt++;
        p[clone] = p[q]; 
        p[clone].len = p[pos].len + 1; 
        p[clone].end_cnt = 0;
        p[q].link = p[cur].link = clone;
        while (pos != -1 && p[pos].next[c] == q) {
          p[pos].next[c] = clone; pos = p[pos].link; } } }
    last = cur; }
  void gdfs(int u, int fval = -1, int dep=0) {
    p[u].la_len = fval;
    if (p[u].end_cnt != 0) {
      fval = p[u].len; }
    for (int v: p[u].e) {
      gdfs(v, fval, dep+1); } }

  // build edges on suffix tree
  void build() {
    for (int i: range(1,cnt)) {
      p[p[i].link].e.push_back(i); } }

} sam;

Vector<int> sp_lens[N];
char s[N * 2];
char *s_pos[N];
int n;

struct remove_included : public ranges::rangesMethod {
  int s_id = 0;
  remove_included(int s_id) : s_id(s_id) {}
  Vector<int>&& operator() (Vector<int>&& lens) const {
    int n = lens.size();

    int suf = -1;
    for (int i: range(n-1,-1,-1)) {
      suf--; checkMax(lens[i], suf);
      checkMax(suf, lens[i]); }

    sam.clear();
    char *s_p = s_pos[s_id];
    while (*s_p) {
      sam.insert(*s_p++ - 'a'); }
    sam.build(); sam.dfs_fa(GSAM::root);
    int pos = GSAM::root; s_p = s_pos[s_id];
    Vector<int> pposs;
    for (int x: lens) {
      pos = sam.p[pos].next[*s_p++ - 'a'];
      pposs.push_back(sam.get(pos,x));
      checkMax(sam.p[pposs.back()].la_len, x); }
    sam.dfs_len(GSAM::root);

    for (int i: range(n)) {
      if (sam.p[pposs[i]].la_len > lens[i]) {
        lens[i] = -1; } }

    for (int i: range(n-1)) {
      if (lens[i] != -1 && lens[i] + 1 == lens[i+1]) { 
        sam.p[pposs[i]].end_cnt = 1; } }

    for (int i: range(n)) {
      if (lens[i] != -1) {
        if (sam.p[pposs[i]].end_cnt) { lens[i] = -1; }
        else { sam.p[pposs[i]].end_cnt = 1; } } }

    return std::move(lens);
  }
};

struct count_t : public ranges::rangesMethod {
  int operator() (Vector<int>&& lens) const {
    return std::count_if(lens.begin(), lens.end(), [](int x) { return x != -1; }); }
} count;

void preInit() { } void init() {
  n = sc.n(); s_pos[0] = s; 
  for (int i: range(n)) {
    sc.next(s_pos[i]); int len = std::strlen(s_pos[i]);
    s_pos[i+1] = s_pos[i] + len + 1; }

} void solve() {

  for (int i: range(n)) {
    char *s_p = s_pos[i];
    while (*s_p) { sam.ginsert(*s_p++ - 'a'); }
    sam.reset(); }
  sam.build(); sam.gdfs(GSAM::root);

  for (int i: range(n)) {
    Vector<int> lens;
    int pos = GSAM::root;
    char *s_p = s_pos[i];
    while (*s_p) {
      pos = sam.p[pos].next[*s_p - 'a'];
      int pl = sam.p[pos].la_len;
      if (sam.p[pos].end_cnt > (*(s_p+1)=='\0')) {
        pl = sam.p[pos].len; }
      lens.push_back(pl);
      s_p++; }
    sp_lens[i] = std::move(lens); }

  int ans = 0;
  for (int i: range(n)) {
    ans += std::move(sp_lens[i]) | remove_included(i) | count; }
  printf("%d\n", ans);
}
