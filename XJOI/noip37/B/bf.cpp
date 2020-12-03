#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"

#include <bits/stdc++.h>
#include "/home/jack/code/creats/body.h"

/** My code begins here **/

const int N = 100005;
std::vector< std::pair<int,int> > e[N];
std::vector<int> a;
int n, m, k;

int getMin(std::vector<int>& us, std::vector<int>& vs) {
  if (us.size() == 0 || vs.size() == 0) { return 0x3f3f3f3f; }
  static int dis[N]; memset(dis, 0x3f, sizeof(dis));
  std::priority_queue< std::pair<int,int>, std::vector< std::pair<int,int> >, std::greater< std::pair<int,int> > > que;
  for (int u: us) { dis[u] = 0; que.push(std::make_pair(0,u)); }
  while (!que.empty()) {
    int u=que.top().second, w=que.top().first; que.pop(); if (dis[u] != w) { continue; }
    for (auto v: e[u]) { if (checkMin(dis[v.first], v.second+w)) { que.push(std::make_pair(dis[v.first], v.first)); } } }
  int res = 0x3f3f3f3f; for (int u: vs) { checkMin(res, dis[u]); }
  return res; }

int getAns(std::vector<int>& us) {
  if (us.size() < 2) { return 0x3f3f3f3f; }
  int ans = 0x3f3f3f3f;
  int sz = us.size();
  for (int differ=1; differ<sz; differ<<=1) {
    std::vector<int> u1, u2;
    rep (i,sz) { ((i&differ) ? u1 : u2).push_back(us[i]); }
    checkMin(ans, getMin(u1,u2)); }
  return ans; }

namespace solver3 {
bool jury() {
  int num_1 = std::count_if(a.begin(), a.end(), [](int a) { return a==1; });
  int num_2 = std::count_if(a.begin(), a.end(), [](int a) { return a==2; });
  return (num_1==1) && (num_2==1) && (e[1].size()==1) && (e[2].size()==1) && (e[1][0].first==2) && (e[2][0].first==1) && (e[1][0].second==1); }
void solve() {
  std::vector<int> new_a;
  for (int i: a) { if (i>2) { new_a.push_back(i); } }
  printf("%d\n", 1 + getAns(new_a)); }
} /* solver3 */

void preInit() { } void init() {
  n = sc.n(); m = sc.n(); k = sc.n();
  rep (i,m) { int u=sc.n(), v=sc.n(), w=sc.n(); e[u].push_back(std::make_pair(v,w)); e[v].push_back(std::make_pair(u,w)); }
  rep (i,k) a.push_back(sc.n()); 
} void solve() {
  int ans = 0x3f3f3f3f;
  while (static_cast<double>(clock()) / CLOCKS_PER_SEC < 2) {
    std::vector<int> u1, u2;
    rep (i,k) { ((rand()&1) ? u1 : u2).push_back(a[i]); }
    checkMin(ans, getAns(u1) + getAns(u2)); }
  printf("%d\n", ans);
}
