#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
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

/** My code begins here **/

constexpr int N = 200005;

struct Tree {
  int ef[N], en[N*2], ev[N*2], ew[N*2], ec=0;
  void addEdge(int u, int v, int w) {
    en[ec] = ef[u]; ef[u] = ec; ev[ec] = v; ew[ec] = w; ec++;
    en[ec] = ef[v]; ef[v] = ec; ev[ec] = u; ew[ec] = w; ec++; }
};

struct TreeP : public Tree {
  int sz[N], vis[N];
  void getSize(int u, int f) {
    sz[u] = 1;
    for (int e=ef[u]; e!=-1; e=en[e]) if (ev[e] != -1 && !vis[en[e]]) {

};

struct TreeTD {
  
};

void preInit() { } void init() {

} void solve() {

}
