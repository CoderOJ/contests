#include "/home/jack/code/creats/gpl.h"

// #include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/base.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
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

void
preInit()
{}

void
init()
{}

const double eps = 1e-7;
long long k;
double v1,v2;

using std::abs;

struct State {
  double p1,p2;
  double v1,v2;

  bool isMeet() {
    return abs(p1 - p2) < eps;
  }
  State next() {
    double toEnd1 = std::max(-p1/v1, (100-p1)/v1);
    double toEnd2 = std::max(-p2/v2, (100-p2)/v2);
    double toMeet = (p1-p2) / (v2-v1);
    if (toMeet <= eps) { toMeet = 1000; }
    double end = std::min( std::min(toEnd1,toEnd2), toMeet );
    double vp1 = p1 + end * v1;
    double vp2 = p2 + end * v2;
    double vv1 = v1;
    double vv2 = v2;
    if (abs(toEnd1-toMeet)<eps && abs(toEnd2-toMeet)<eps) {
      vv1 = -vv1;
      vv2 = -vv2;
    } else if (toEnd1 == end) {
      vv1 = -vv1;
    } else if (toEnd2 == end) {
      vv2 = -vv2;
    } else {
      if ((v1>0) ^ (v2>0)) {
        vv1 = -vv1;
        vv2 = -vv2;
      } else {
        double& change = (abs(vv1)>abs(vv2)) ? vv1 : vv2;
        change = -change;
      }
    }
    State nxt = {vp1, vp2, vv1, vv2};
    if (!nxt.isMeet()) {
      return nxt.next();
    } else {
      return nxt;
    }
  }
  void log() {
    slog("pos1: %.6lf speed1: %.6lf \t pos2: %.6lf speed2 %.6lf\n", p1,v1,p2,v2);
  }
};

void
solve()
{
  int T; scanf("%d",&T);
  while (T--) {
    double r;
    scanf("%lld%lf%lf%lf", &k, &v1, &v2, &r);
    State pos = {0,r,v1,-v2};
    if (k <= 200) {
      rep (i,k) { pos = pos.next(); }
      printf("%.9lf\n",pos.p1);
    } else {
      std::vector <State> st;
      rep (i,200) {
        pos = pos.next();
        st.push_back(pos);
      }
      printf("%.9lf\n", st[199 - (k&1)].p1);
    }
  }
}
