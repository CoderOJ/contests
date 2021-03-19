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

typedef __int128_t int128_t;
constexpr int N = 3000;
int64_t a[N], b[N];
int n, k;

struct BufferWriter {
  static constexpr int BUF_SIZE = 1 << 18;
  char buf[BUF_SIZE], *buf_pos=buf, *const buf_end=buf+BUF_SIZE;
  FILE* dest;

  BufferWriter(FILE* dest) : dest(dest) {}
  void flush() {
    fwrite(buf, buf_pos - buf, 1, dest);
    buf_pos = buf; }
  template<class T> void print(T val);
  ~BufferWriter() { flush(); fclose(dest); }
} out(stdout);

template<> void BufferWriter::print<char>(char val) {
  *buf_pos++ = val; 
  if (buf_pos == buf_end) { flush(); } }
template<> void BufferWriter::print<int128_t>(int128_t val) {
  if (val == 0) { print('0'); return; }
  static char stack[50];
  char *stack_pos = stack;
  while (val) {
    *stack_pos++ = '0' + (val % 10);
    val /= 10; }
  while (stack_pos != stack) {
    print(*--stack_pos); } }

struct Array {
  static uint64_t hash_wei[N];

  int id[N];
  uint64_t hash = 0;
  int128_t value = 0;
  void set(int i, int val) {
    hash -= hash_wei[i] * id[i];
    id[i] = val;
    hash += hash_wei[i] * id[i]; }
  void swap(int i) {
    value -= static_cast<int128_t>(a[id[i+1]] - a[id[i]]) * (b[i+1] - b[i]); 
    int id_i = id[i]; set(i,id[i+1]); set(i+1,id_i); }
  bool can_swap(int i) { return id[i] < id[i+1]; }
  bool operator< (const Array& rhs) const {
    if (value != rhs.value) { return value > rhs.value; }
    if (hash != rhs.hash) { return hash < rhs.hash; }
    rep (i,n) if (id[i] != rhs.id[i]) { return id[i] < rhs.id[i]; }
    return false; }
};

uint64_t Array::hash_wei[N];

void preInit() { 
  std::mt19937_64 wei_rd(20050610);
  rep (i,N) Array::hash_wei[i] = wei_rd();
} void init() {
  n = sc.n(); k = sc.n();
  rep (i,n) { a[i] = sc.nl(); } std::sort(a, a+n);
  rep (i,n) { b[i] = sc.nl(); } std::sort(b, b+n);
} void solve() {
  Array o; rep (i,n) { o.set(i,i); o.value += static_cast<int128_t>(a[i]) * b[i]; }
  std::set<Array> sarr; sarr.insert(o);
  Temps::Vector<int128_t> ans;
  rep (i,k) {
    Array pos = *sarr.begin(); sarr.erase(sarr.begin());
    ans.push_back(pos.value);
    rep (i,n-1) if (pos.can_swap(i)) {
      pos.swap(i); sarr.insert(pos); pos.swap(i); }
    while (ans.size() + sarr.size() > (size_t)(k)) { sarr.erase(--sarr.end()); } }
  for (const auto i: ans) {
    out.print(i); out.print('\n'); }
}
