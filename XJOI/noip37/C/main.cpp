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
  int operator[] (const int id) {
    return std::map<int,int>::operator[](id) + add; }
  void merge(Map& B) {
    for (auto i: B) {
      std::map<int,int>::operator[](i.first) = i.second + B.add - add; } }
};

struct Dsu {
  Map a[N]; int p[N], sz[N];
  void init(int n) {
    repa (i,n) { p[i]=i; sz[i]=1; } }
  int get(int u) { return u==p[u] ? u : p[u]=get(p[u]); }
  void merge(int u, int v) {
    int pu = get(u), pv = get(v);
    if (sz[pu] < sz[pv]) { std::swap(pu,pv); }
    p[pv]=pu; sz[pu]+=sz[pv]; a[pu].merge(a[pv]); }
  void add(int u, int v) { u = get(u); a[u].pushAdd(v); }
  int at(int u) { return a[get(u)][u]; }
} dsa;

struct Info { int val, time; Info(int val=0, int time=0) : val(val), time(time) {} };
class Map2 : std::map<int, Info> {
private:
  int val=0, time=0, cnt=1;
public:
  void pushVal(int _val) { time = cnt++; val = _val; }
  void set(int u, int v) { std::map<int,Info>::operator[](u) = (Info){v, cnt++}; }
  int at(int u) { auto v=std::map<int,Info>::operator[](u); return time>v.time ? val : v.val; }
  void merge(Map2& B) { for (auto i: B) { set(i.first, B.at(i.first)); } }
};

struct Dsu2 {
  Map2 a[N], time[N]; int p[N], sz[N];
  void init(int n) { repa (i,n) { p[i]=i; sz[i]=1; time[i].set(i,0); a[i].set(i,0); } }
  int get(int u) { return u==p[u] ? u : p[u]=get(p[u]); }
  void merge(int u, int v) {
    int pu = get(u), pv = get(v);
    if (sz[pu] < sz[pv]) { std::swap(pu,pv); }
    p[pv]=pu; sz[pu]+=sz[pv]; a[pu].merge(a[pv]); time[pu].merge(time[pv]); }
  void upd(int u, int v, int t) { u=get(u); a[u].pushVal(v); time[u].pushVal(t); }
  int atVal(int u) { return a[get(u)].at(u); }
  int atTime(int u) { return time[get(u)].at(u); }
} dsb;

struct Query { int op, x, y; } qs[N];
std::vector<int> queryTrigger[N];
int n,m;

void preInit() { } void init() {
  n = sc.n(); m = sc.n();
  rep (i,m) { 
    qs[i].op = sc.n();
    if (qs[i].op <= 4) { qs[i].x=sc.n(); qs[i].y=sc.n(); }
    else { qs[i].x=sc.n(); } }
} void solve() {
  dsb.init(n);
  rep (i,m) {
    if (qs[i].op == 2) { dsb.merge(qs[i].x, qs[i].y); }
    else if (qs[i].op == 4) { dsb.upd(qs[i].x, qs[i].y, i); }
    else if (qs[i].op == 5) { int u=qs[i].x;
      queryTrigger[dsb.atTime(u)].push_back(i); qs[i].y = dsb.atVal(u); } } 
  dsa.init(n);
  rep (i,m) {
    for (int j: queryTrigger[i]) { qs[j].y -= dsa.at(qs[j].x); }
    if (qs[i].op == 1) { dsa.merge( qs[i].x, qs[i].y ); }
    else if (qs[i].op == 3) { dsa.add(qs[i].x, qs[i].y); }
    else if (qs[i].op == 5) { qs[i].y += dsa.at(qs[i].x); printf("%lld\n", qs[i].y); } 
  }
}
