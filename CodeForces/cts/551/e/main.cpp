#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/base.h"

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

#define in :
/** My code begins here **/

constexpr int N = 502005;
constexpr int L = 1000;
constexpr int THR = 1000000000;
int bel[N], block_pos[N / L];

std::map<int,int> exist[N / L];
int block_add[N / L];
int a[N], n, q, block_cnt;

void inc(int pos, int val) {
  int b = bel[pos];
  if (a[pos] + block_add[b] > THR) { return; }
  int origin_value = a[pos];
  --exist[b][origin_value];
  a[pos] += val; 
  if (a[pos] + block_add[b] > THR) { return; }
  ++exist[b][a[pos]]; }

int search_forward(int b, int val) {
  if (block_add[b] > THR) { return -1; }
  val -= block_add[b];
  if (exist[b].find(val) == exist[b].end() || exist[b][val] == 0) { return -1; }
  for (int i in range(block_pos[b], block_pos[b+1])) {
    if (a[i] == val) { return i; } }
  return -1; }

int search_backward(int b, int val) {
  if (block_add[b] > THR) { return -1; }
  val -= block_add[b];
  if (exist[b].find(val) == exist[b].end() || exist[b][val] == 0) { return -1; }
  for (int i in range(block_pos[b+1]-1, block_pos[b]-1, -1)) {
    if (a[i] == val) { return i; } }
  return -1; }

void preInit() { } void init() {
  for (int i in range(0,N,L)) {
    block_pos[i / L] = i;
    for (int j in range(i,i+L)) { bel[j] = i / L; } }
  n = sc.n(); q = sc.n();
  for (int i in range(n)) { a[i] = sc.n(); }
  for (int i in range(n)) { ++exist[bel[i]][a[i]]; }
  block_cnt = bel[n-1] + 1;
} void solve() {
  while (q--) {
    int opt = sc.n();
    if (opt == 1) {
      int l=sc.n()-1, r=sc.n()-1, k=sc.n();
      int lb = bel[l], rb = bel[r];
      if (lb == rb) {
        for (int i in range(l,r+1)) { inc(i,k); } }
      else {
        for (int i in range(lb+1, rb)) if (block_add[i] <= THR) { block_add[i] += k; }
        for (int i in range(l, block_pos[lb+1])) { inc(i, k); }
        for (int i in range(block_pos[rb], r+1)) { inc(i, k); } } }
    else {
      int val = sc.n();
      int min = -1;
      for (int i in range(block_cnt)) {
        int t = search_forward(i, val); 
        if (t != -1) { min = t; break; } }
      if (min == -1) { puts("-1"); continue; }
      int max = -1;
      for (int i in range(block_cnt-1, -1, -1)) {
        int t = search_backward(i, val);
        if (t != -1) { max = t; break; } }
      printf("%d\n", max - min); }
  }
}
