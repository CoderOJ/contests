#include "/home/jack/code/creats/gpl.hpp"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/Scanner.hpp"
#include "/home/jack/code/creats/log.hpp"
#include "/home/jack/code/creats/range.hpp"
#include "/home/jack/code/creats/util.hpp"
#include "/home/jack/code/creats/Vector.hpp"
// #include "/home/jack/code/creats/STree.hpp"
// #include "/home/jack/code/creats/Tree.hpp"
// #include "/home/jack/code/creats/Graph.hpp"
// #include "/home/jack/code/creats/Intm.hpp"
// #include "/home/jack/code/Math/Poly/main.h"


#define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

struct vp_t : public std::pair<int,int>
{
  using std::pair<int,int>::pair; 
  vp_t(std::pair<int,int> x) : std::pair<int,int>(x) {}
  vp_t(vp_t a, vp_t b) : std::pair<int,int>(b - a) {}
  vp_t norm()
  {
    vp_t r = *this;
    if (r.second < 0 || (r.second == 0 && r.first < 0))
      r.first = -r.first, r.second = -r.second;
    if (r.first || r.second)
    {
      auto g = std::abs(Temps::gcd(r.first, r.second));
      r.first /= g, r.second /= g;
    }
    return r;
  }

  vp_t rotater()
  { return vp_t(second, -first); }
};

auto vp_x_cmp = [](vp_t x,vp_t y) { return x.first != y.first ? x.first < y.first : x.second > y.second; };
bool operator< (const vp_t x, const vp_t y)
{ return 1ll * x.second * y.first < 1ll * y.second * x.first; }
bool operator<= (const vp_t x, const vp_t y)
{ return 1ll * x.second * y.first <= 1ll * y.second * x.first; }

constexpr int N = 1005;
vp_t p[N];
int n;

void preInit() {  } 
void init() 
{
  n = sc.n();
  for (int i = 0; i < n; i++)
    p[i].first = sc.nextInt(), p[i].second = sc.nextInt();
  std::sort(p, p + n, vp_x_cmp);
} 

struct vset_t {
  std::map<vp_t, int> cnt;
  void insert(vp_t x) { 
    if (x == vp_t(0,0)) { return; }
    cnt[x]++; }
  void erase(vp_t x) { 
    if (x == vp_t(0,0)) { return; }
    if (--cnt[x] == 0) { cnt.erase(cnt.find(x)); } }
  int query() {
    if (cnt.size() == 0) return -1;
    else if (cnt.size() == 1) return 1;
    return 0; }
  vp_t get_first() { return cnt.begin()->first; }
};

void solve() 
{
  if (n <= 2) { puts("-1"); return; }

  using event_t = std::tuple<vp_t, int, int>;
  std::vector<event_t> events;
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      if (p[i] != p[j])
        events.emplace_back(vp_t(p[i], p[j]).rotater().norm(), i, j);
  if (events.size() == 0) { puts("-1"); return; }
  std::sort(events.begin(), events.end());
  if (std::get<0>(events[0]) != vp_t(1,0)) 
    events.emplace(events.begin(), vp_t(1,0), 0, 0);
  events.emplace_back(vp_t(-1e9,1), 0, 0);

  logArray(p, p + n);
  for (const auto& [_,x,y] : events) see(_,x,y);
    
  std::set<vp_t> ans;
  vset_t vset;
  std::vector<int> ids(n), id2p(n);
  for (int i = 0; i < n; i++) ids[i] = i, id2p[i] = i;
  auto get_min = [&](int x) { return std::min(x, n - 2 - x); };
  auto add_segment = [&](int x) -> void
  {
    const int y = n - 2 - x;
    const vp_t vx(p[ids[x + 1]], p[ids[x]]), vy(p[ids[y]], p[ids[y + 1]]);
    // see(vx, vy, vp_t(vx + vy).rotater().norm());
    vset.insert(vp_t(vx + vy).rotater().norm());
  };
  auto rem_segment = [&](int x) -> void
  {
    const int y = n - 2 - x;
    const vp_t vx(p[ids[x + 1]], p[ids[x]]), vy(p[ids[y]], p[ids[y + 1]]);
    // see(vx, vy, vp_t(vx + vy).rotater().norm());
    vset.erase(vp_t(vx + vy).rotater().norm());
  };

  for (int x = 0; x < n - 2 - x; x++)
    add_segment(x);
  for (size_t i = 0, r; i + 1 < events.size(); i = r)
  {
    r = i + 1;  
    while (r + 1 < events.size() && std::get<0>(events[r]) == std::get<0>(events[i])) r++;
    see(i, r);

    std::vector<int> ban_list;
    std::vector<std::pair<int,int>> inter_list;
    for (size_t j = i; j < r; j++)
    {
      const auto &[_,x,y] = events[j];
      see(_,x,y);
      const int px = id2p[x], py = id2p[y];
      ban_list.push_back(get_min(px)); ban_list.push_back(get_min(px-1));
      ban_list.push_back(get_min(py)); ban_list.push_back(get_min(py-1));
      inter_list.emplace_back(px, py);
    }

    std::sort(ban_list.begin(), ban_list.end());
    ban_list.erase(std::unique(ban_list.begin(), ban_list.end()), ban_list.end());
    for (int i: ban_list) if (i >= 0) rem_segment(i);

    std::sort(inter_list.begin(), inter_list.end(), [](std::pair<int,int> x, std::pair<int,int> y) { return x.first != y.first ? x.first < y.first : x.second > y.second; });
    int max_r = -1;
    for (const auto &[l,r] : inter_list)
    {
      if (r <= max_r) continue;
      max_r = r;
      for (int i = l, j = r; i < j; i++, j--)
      {
        std::swap(ids[i], ids[j]);
        std::swap(id2p[ids[i]], id2p[ids[j]]);
      }
    }

    for (int i: ban_list) if (i >= 0) add_segment(i);

    see(ids);

    {
      const auto ri = vset.query();
      if (ri == -1) { puts("-1"); return; }
      else if (ri == 1)
      {
        const auto v = vset.get_first();
        see(std::get<0>(events[i]) , v , std::get<0>(events[r]));
        if (std::get<0>(events[i]) <= v && v < std::get<0>(events[r]))
          ans.insert(v);
      }
    }
  }

  assert(ans.size() <= n);
  std::cout << ans.size() << std::endl;
}
