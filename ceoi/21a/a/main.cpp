#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <cstring>
#include <algorithm>

cm::scanner<cm::optimal_reader> sc (stdin);

constexpr int N = 300005;
int a[N], n, q;

long long calc (int *_a, int n) {
  struct info_t {
    int cnt = 0;
    bool vis = false; };
  static info_t a[N];

  for (int i = 0; i < n; i++) {
    a[_a[i]].cnt++; }

  static int v[N];
  int *ve = v;
  for (int i = 0; i < n; i++) if (!a[_a[i]].vis) {
      *ve++ = a[_a[i]].cnt;
      a[_a[i]].vis = true; }

  std::sort (v, ve);
  int gl = 0, gr = n;
  bool front = true;
  long long ans = 0;
  for (int *i = v; i < ve; i++) {
    // see(*i);
    if (front) {
      int l = gl, r = l + *i;
      // see(l, r);
      ans += 1ll * (n - l) * l + 1ll * (n * 2 - l - r + 1) * (r - l) / 2;
      gl += *i;
      front = false; }
    else {
      int r = gr, l = r - *i;
      // see(l, r);
      ans += 1ll * (n - l) * l + 1ll * (n * 2 - l - r + 1) * (r - l) / 2;
      gr -= *i;
      front = true; } }

  for (int i = 0; i < n; i++) {
    a[_a[i]] = info_t(); }

  return ans; }

int main() {
;;n = sc.next_int();
;;q = sc.next_int();
;;for (int i = 0; i < n; i++) {
;;;;a[i] = sc.next_int(); }
;;for (int i = 0; i < q; i++) {
;;;;int l = sc.next_int() - 1;
;;;;int r = sc.next_int();
;;;;printf ("%lld\n", calc (a + l, r - l) ); }
;;return 0; }

