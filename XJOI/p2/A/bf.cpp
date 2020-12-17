#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"

/** My code begins here **/

const int N = 200005;

struct Tree {
protected:
  typedef std::pair<int, int> Edge;
  std::vector<Edge> e[N];

public:
  void addEdge(int u, int v, int w) {
    e[u].push_back( std::make_pair(v,w) );
    e[v].push_back( std::make_pair(u,w) ); }
  std::vector<long> diss;
  void dfs(int u, int f, long d) {
    diss.push_back(d); 
    for (auto v: e[u]) if (v.first != f) {
      dfs(v.first, u, d + v.second); } }
} T;

int n, k;

void preInit() { } void init() {
  n = sc.n(); k = sc.n();
  rep (i,n-1) { int u=sc.n(), v=sc.n(), w=sc.n(); T.addEdge(u,v,w); }
} void solve() {
  repa (i,n) T.dfs(i,0,0);
  std::sort(T.diss.begin(), T.diss.end(), std::greater<long>());
  rep (i,k) printf("%ld\n", T.diss[i*2]);
}
