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


// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

using namespace Temps;
constexpr int N = 200005;
using Opt = std::tuple<int, int, int, int>;
std::vector<Opt> opts;
std::vector<int> ys;
long long ans[N];
int cnt[N], width[N], last[N];
int n, k;

void preInit() {  } 
void init() 
{
  n = sc.n(); k = sc.n();
  for (int i=0; i<n; i++) {
    int x=sc.nextInt(), y=sc.nextInt();
    opts.push_back(std::make_tuple(x, y, y+k, 1));
    opts.push_back(std::make_tuple(x+k, y, y+k, -1)); 
    ys.push_back(y); ys.push_back(y+k); }
  std::sort(ys.begin(), ys.end()); ys.erase(std::unique(ys.begin(), ys.end()), ys.end());
  for (auto& [x,y1,y2,d] : opts) {
    y1 = static_cast<int>(std::lower_bound(ys.begin(), ys.end(), y1) - ys.begin());
    y2 = static_cast<int>(std::lower_bound(ys.begin(), ys.end(), y2) - ys.begin()); }
  for (size_t i=0; i+1<ys.size(); i++) { width[i] = ys[i + 1] - ys[i]; }
} 

void solve() 
{
  std::sort(opts.begin(), opts.end());
  memset(last, 0xcf, sizeof(last));
  for (const auto& [x,y1,y2,d] : opts) {
    see(x, y1, y2, d);
    for (int i=y1; i<y2; i++) {
      ans[cnt[i]] += 1ll * width[i] * (x - last[i]);
      cnt[i] += d; last[i] = x; } }
  std::cout << Vector<long long>(ans + 1, ans + n + 1) << std::endl;
}
