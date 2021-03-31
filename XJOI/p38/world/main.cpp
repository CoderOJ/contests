#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/util.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

#define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 50;
constexpr int M = N * N;

typedef std::bitset<M> Bits;
int n, m, k;
Bits a,b;

struct LinearBasis {
  Bits w[M];
  void insert(Bits x) {
    for (int i=0;i<k;++i) {
      if (x[i]) {
        if (w[i].any()) { x ^= w[i]; }
        else { w[i] = std::move(x); break; } } } }
  bool check(Bits x) {
    for (int i=0;i<k;++i) {
      if (x[i]) {
        if (w[i].any()) { x ^= w[i]; }
        else { return false; } } }
    return true; }
} lb;

void preInit() { } void init() {
  lb = LinearBasis();
  n = sc.n(); m = sc.n(); k = n * m;
  rep (i,n) rep (j,m) a[i*m + j] = sc.nextChar() == '1';
  rep (i,n) rep (j,m) b[i*m + j] = sc.nextChar() == '1';
} void solve() {
  rep (i,n) {
    Bits x; rep (j,m) x[i*m + j] = 1;
    lb.insert(x); }

  rep (j,m) {
    Bits x; rep (i,n) x[i*m + j] = 1;
    lb.insert(x); }

  for (int sum=0; sum<n+m-1; ++sum) {
    Bits x; 
    rep (i,n) rep (j,m) if (i+j==sum) { x[i*m + j] = 1; }
    lb.insert(x); }

  for (int del=-m+1; del<n; ++del) {
    Bits x; 
    rep (i,n) rep (j,m) if (i-j==del) { x[i*m + j] = 1; }
    lb.insert(x); }

  puts(lb.check(a ^ b) ? "Yes" : "No");
}
