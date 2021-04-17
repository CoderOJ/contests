#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
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

struct Edge { int u,v,w; };
constexpr int N = 200005;
constexpr int B = 2005;
std::set<int> e[N];
int n, m, tot_w;
Edge es[N];
int id[N];

std::set<int> all;

void dfs(int u) {
  for (std::set<int>::iterator it=all.begin(); it!=all.end();) {
    int v = *it;
    if (e[u].count(v)) { ++it; }
    else {
      id[v] = id[u];
      all.erase(it); 
      dfs(v);
      it = all.upper_bound(v); } }
}

struct Dsu {
  int p[N];
  void init(int n) { for (int i=0; i<=n; ++i) p[i] = i; }
  int get(int u) { return u == p[u] ? u : p[u] = get(p[u]); }
  bool merge(int u, int v) {
    int pu = get(u), pv = get(v);
    if (pu == pv) { return false; }
    return p[pv]=pu, true; }
};

long long mst(std::vector<Edge> e)
{
  for (int i=0; i<(int)e.size()-1; ++i)
    if (e[i].w > e[i+1].w) std::swap(e[i], e[i+1]);
  // assert(std::is_sorted(e.begin(), e.end(), [](const Edge& a, const Edge& b) { return a.w < b.w; }));
  long long ans = 0; Dsu st; st.init(n);
  for (const Edge& i: e)
    ans += i.w * st.merge(i.u, i.v);
  return ans;
}

void preInit() { } void init() {
  n = sc.n(); m = sc.n();
  for (int i=0; i<m; ++i) {
    int u=sc.n(), v=sc.n(), w=sc.n();
    es[i] = Edge{u,v,w};
    e[u].insert(v); e[v].insert(u);
    tot_w ^= w; }
  see(tot_w);
} void solve() {
  for (int i=1; i<=n; ++i) all.insert(i);
  int id_cnt = 0;
  for (int i=1; i<=n; ++i) if (all.count(i)) {
    id[i] = id_cnt++; all.erase(i); dfs(i); }

  see(id_cnt);

  if (1ll * n * (n-1) / 2 - m > n - id_cnt)
  {
    see("huge");
    int min_bl[B][B];
    memset(min_bl, 0x3f, sizeof(min_bl));
    for (int i=0; i<m; ++i) {
      int uid = id[es[i].u], vid = id[es[i].v];
      checkMin(min_bl[uid][vid], es[i].w);
      checkMin(min_bl[vid][uid], es[i].w); }
    std::vector<Edge> emst;
    for (int i=0; i<id_cnt; ++i) 
      for (int j=0; j<i; ++j)
        emst.push_back({i,j, min_bl[i][j]});
    std::sort(emst.begin(), emst.end(), [](const Edge& a, const Edge& b) { return a.w < b.w; });
    printf("%lld\n", mst(emst));
  }
  else
  {
    see("brute");
    std::vector<Edge> emst;
    int free_cnt = 0;
    for (int i=1; i<=n; ++i) for (int j=i+1; j<=n; ++j)
      if (!e[i].count(j)) emst.push_back({i,j,0}), free_cnt++;
    for (int i=0; i<m; ++i) emst.push_back(es[i]);

    long long ans = std::numeric_limits<long long>::max();
    std::sort(emst.begin(), emst.end(), [](const Edge& a, const Edge& b) { return a.w < b.w; });
    if (free_cnt == 0) { ans = mst(emst); }
    for (int i=0; i<free_cnt; ++i) {
      emst[i].w = tot_w;
      checkMin(ans, mst(emst));
      emst[i].w = 0; }

    printf("%lld\n", ans);
  }
}
