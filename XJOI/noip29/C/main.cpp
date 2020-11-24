#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/base.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
// #include "/home/jack/code/creats/Intm.h"

#include <bits/stdc++.h>

#include "/home/jack/code/creats/body.h"

/** My code begins here **/

#define int long long

const int N = 100005;
struct Chair
{
  int a, b;
  Chair(int a = 0, int b = 0)
    : a(a)
    , b(b)
  {}
  int resolv(int u) { return u * (a - b * u); }
};

Chair a[N];
int n, k;

void
preInit()
{}

void
init()
{
  n = sc.n();
  k = sc.n();
  rep(i, n)
  {
    a[i].a = sc.n();
    a[i].b = sc.n();
  }
}

struct Rew
{
  int val;
  int id, w;
  Rew(int val, int id, int w)
    : val(val)
    , id(id)
    , w(w)
  {}
  bool operator<(const Rew& B) const { return val < B.val; }
};

void
solve()
{
  std::priority_queue<Rew> rew;
  rep (i,n) rew.push( Rew(a[i].resolv(1) - a[i].resolv(0), i, 0) );
  int ans = 0;
  while (k--) {
    if (rew.top().val <= 0) { break; }
    auto ch = rew.top(); rew.pop();
    ans += ch.val;
    ch.w++;
    ch.val = a[ch.id].resolv( ch.w+1 ) - a[ch.id].resolv( ch.w ); 
    rew.push(ch); }
  printf("%lld\n", ans);
}
