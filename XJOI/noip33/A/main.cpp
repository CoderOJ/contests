#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/base.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

#define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

const int N = 1005;
const double eps = 1e-7;

struct Stu
{
  int a, b, c;
  int id;
  double resolv(double pa, double pb, double pc) {
    return a*pa + b*pb + c*pc;
  }
};

Stu a[N];
int n;

void
preInit()
{}

void
init()
{
  n = sc.n();
  rep(i, n)
  {
    a[i].a = sc.n();
    a[i].b = sc.n();
    a[i].c = sc.n();
  }
}

namespace solver0 {
bool
check()
{
  rep(i, n) if (a[i].b != 0) return false;
  return true;
}
void
main()
{
  rep(i, n) if (a[i].a > a[0].a)
  {
    puts("-1");
    return;
  }
  puts("100 100 100");
}
} /* solver0 */

namespace solver1 {
bool
check()
{
  rep(i, n) if (a[i].c != 0) return false;
  return true;
}
typedef std::pair<int, int> Pt;
int
slope(Pt a, Pt b)
{
  return a.first * b.second - a.second * b.first;
}
void
main()
{
  rep(i, n) a[i].id = i;
  std::sort(a, a + n, [](Stu a, Stu b) { return a.a < b.a; });
  std::vector<Stu> st;
  rep(i, n)
  {
    while (st.size() > 1) {
      auto p = st[st.size() - 1];
      auto pp = st[st.size() - 2];
      auto p0 = Pt(a[i].a - p.a, a[i].b - p.b);
      auto p1 = Pt(pp.a - p.a, pp.b - p.b);
      if (slope(p0, p1) > 0) {
        st.pop_back();
      } else {
        break;
      }
    }
    st.push_back(a[i]);
  }
  bool find_zero = false;
  int find_pos = 0;
  for (int i = 0; i < (int)st.size(); ++i) {
    if (st[i].id == 0) {
      find_pos = i;
      find_zero = 1;
      break;
    }
  }
  if (find_zero == false) {
    puts("-1");
    return;
  }
  int pa = 100;
  for (int pb=pa; pb<=(int)(1e6); ++pb) {
    double pre = -1;
    if (find_pos) {
      pre = st[find_pos-1].resolv(pa, pb, 100); }
    double pos = st[find_pos].resolv(pa, pb, 100);
    double suf = 01;
    if (find_pos + 1 < (int)st.size()) {
      suf = st[find_pos+1].resolv(pa, pb, 100); }
    if (pos+eps >= pre && pos+eps >= suf) {
      printf("%d %d %d\n", pa, pb, pa); 
      return;
    }
  }
  pa = 101;
  for (int pb=pa; pb<=(int)(1e6); ++pb) {
    double pre = -1;
    if (find_pos) {
      pre = st[find_pos-1].resolv(pa, pb, 100); }
    double pos = st[find_pos].resolv(pa, pb, 100);
    double suf = 01;
    if (find_pos + 1 < (int)st.size()) {
      suf = st[find_pos+1].resolv(pa, pb, 100); }
    if (pos+eps >= pre && pos+eps >= suf) {
      printf("%d %d %d\n", pa, pb, pa); 
      return;
    }
  }
  pa = 1000;
  for (int pb=pa; pb<=(int)(1e6); ++pb) {
    double pre = -1;
    if (find_pos) {
      pre = st[find_pos-1].resolv(pa, pb, 100); }
    double pos = st[find_pos].resolv(pa, pb, 100);
    double suf = 01;
    if (find_pos + 1 < (int)st.size()) {
      suf = st[find_pos+1].resolv(pa, pb, 100); }
    if (pos+eps >= pre && pos+eps >= suf) {
      printf("%d %d %d\n", pa, pb, pa); 
      return;
    }
  }
  pa = 10000;
  for (int pb=pa; pb<=(int)(1e6); ++pb) {
    double pre = -1;
    if (find_pos) {
      pre = st[find_pos-1].resolv(pa, pb, 100); }
    double pos = st[find_pos].resolv(pa, pb, 100);
    double suf = 01;
    if (find_pos + 1 < (int)st.size()) {
      suf = st[find_pos+1].resolv(pa, pb, 100); }
    if (pos+eps >= pre && pos+eps >= suf) {
      printf("%d %d %d\n", pa, pb, pa); 
      return;
    }
  }
  puts("-1");
}
} /* solver1 */

namespace solver2 {
void
main()
{
  puts("-1");
}
} /* solver2 */

void
solve()
{
  if (solver0::check()) {
    solver0::main();
  } else if (solver1::check()) {
    solver1::main();
  } else {
    solver2::main();
  }
}
