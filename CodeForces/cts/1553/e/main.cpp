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

constexpr int N = 300005;
int cnt[N], a[N], n, m;

void preInit() {  } 
void init() 
{
  n = sc.n(); m = sc.n();
  for (int i=0; i<n; i++) a[i] = sc.n() - 1;
} 

int b[N], v2pos[N];
bool check(int k) {
  for (int i=0; i<n; i++) b[i] = a[(i + k) % n];
  for (int i=0; i<n; i++) v2pos[b[i]] = i;
  int ans = 0;
  for (int i=0; i<n; i++) if (b[i] != i) {
    v2pos[b[i]] = v2pos[i]; std::swap(b[i], b[v2pos[i]]); v2pos[i] = i; 
    ans++; }
  return ans <= m; }

void solve() 
{
  // std::ios::sync_with_stdio(false); 
  // std::cin.tie(0); std::cout.tie(0);
  for (int i=0; i<n; i++) 
    cnt[(i - a[i] + n) % n]++;
  std::vector<int> ans;
  for (int i=0; i<n; i++) if (cnt[i] >= n - m - m) {
    if (check(i)) ans.push_back(i); }
  std::cout << ans.size() << " " << ans << std::endl;
}
