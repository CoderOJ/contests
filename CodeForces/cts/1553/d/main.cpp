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

constexpr int N = 100005;
char s[N], t[N];

void preInit() {  } 
void init() 
{ sc.next(s); sc.next(t); } 

bool valid(const char *s, const char *t) {
  while (true) {
    if (*t == '\0') return true;
    if (*s == '\0') return false;
    if (*s == *t) { s++; t++; }
    else { if (s[1] == '\0') return false; s += 2; } } }

void solve() 
{
  int n = static_cast<int>(std::strlen(s));
  int m = static_cast<int>(std::strlen(t));
  if (n < m) { puts("NO"); return; }
  puts(valid(s + (n-m) % 2, t) ? "YES" : "NO");
}
