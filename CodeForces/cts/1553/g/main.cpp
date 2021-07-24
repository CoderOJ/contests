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

constexpr int N = 150005;
constexpr int W = 1000005;
bool is_prime[W];
int min_fac[W];
std::vector<int> primes;
int n, q, a[N];

void preInit() 
{ 
  memset(is_prime, true, sizeof(is_prime));
  for (int i=2; i<W; i++) {
    if (is_prime[i]) { primes.push_back(i); min_fac[i] = i; }
    for (int j: primes) {
      int k =  i * j;
      if (k >= W) break;
      is_prime[k] = false;
      min_fac[k] = j;
      if (i % j == 0) break; } }
} 

struct Dsu {
  int p[W];
  Dsu() { for (int i=0; i<W; i++) p[i] = i; }
  int get(int u) { return u == p[u] ? u : p[u] = get(p[u]); }
  void merge(int u, int v) { p[get(u)] = get(v); }
} st;

std::set<int> e[W];

void init() 
{
  n = sc.n(); q = sc.n();
  for (int i=0; i<n; i++) a[i] = sc.n();
  for (int i=0; i<n; i++) { int p = a[i]; 
    while (p != 1) { st.merge(a[i], min_fac[p]); p /= min_fac[p]; } }
  auto link = [](int u, int v) { e[u].insert(v); e[v].insert(u); };
  for (int i=0; i<n; i++) { int p = a[i] + 1, u = st.get(a[i]);
    std::vector<int> facs;
    while (p != 1) { facs.push_back(min_fac[p]); p /= min_fac[p]; }
    for (int f: facs) link(u, st.get(f));
    for (size_t i=0; i<facs.size(); i++) for (size_t j=i+1; j<facs.size(); j++) 
      link(st.get(facs[i]), st.get(facs[j])); }
} 

void solve() 
{
  for (int i=0; i<q; i++) {
    int s=st.get(a[sc.n() - 1]), t=st.get(a[sc.n() - 1]);
    if (s == t) { puts("0"); }
    else { puts(e[s].count(t) ? "1" : "2"); } }
}
