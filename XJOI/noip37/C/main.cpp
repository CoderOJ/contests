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
#define int long long

/** My code begins here **/

const int N = 500005;
class Map : private std::map<int, int> {
private:
  int add = 0;
public:
  void pushAdd(int val) { add += val; }
  void set(int id, int val) { 
    std::map<int,int>::operator[](id) = val - add; }
  int operator[] (const int id) {
    return std::map<int,int>::operator[](id) + add; }
  void merge(Map& B) {
    for (auto i: B) {
      std::map<int,int>::operator[](i.first) = i.second + B.add - add; } }
};

struct Dsu {
  Map a[N]; int p[N], sz[N];
  void init(int n) {
    repa (i,n) { a[i].set(i,0); p[i]=i; sz[i]=1; } }
  int get(int u) { return u==p[u] ? u : p[u]=get(p[u]); }
  void merge(int u, int v) {
    int pu = get(u), pv = get(v);
    if (sz[pu] < sz[pv]) { std::swap(pu,pv); }
    p[pv]=pu; sz[pu]+=sz[pv]; a[pu].merge(a[pv]); }
  void add(int u, int v) { u = get(u); a[u].pushAdd(v); }
  void set(int u, int v) { int pu = get(u); a[pu].set(u,v); }
  int at(int u) { return a[get(u)][u]; }
};

int n,m;
Dsu a;
std::set<int> b[N];

void preInit() { } void init() {
  n = sc.n(); m = sc.n();
  a.init(n); repa (i,n) b[i].insert(i);
} void solve() {
  while (m--) {
    int opt = sc.n();
    if (opt == 1) { int x=sc.n(), y=sc.n(); a.merge(x,y); }
    else if (opt == 2) { int x=sc.n(), y=sc.n(); for (int i: b[y]) { b[x].insert(i); } }
    else if (opt == 3) { int x=sc.n(), t=sc.n(); a.add(x,t); }
    else if (opt == 4) { int x=sc.n(), t=sc.n(); for (int i: b[x]) { a.set(i,t); } }
    else { int x=sc.n(); printf("%lld\n", a.at(x)); } }
}
