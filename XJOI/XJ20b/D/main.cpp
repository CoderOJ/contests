#pragma GCC optimize(2,3,"Ofast")

#include "/home/jack/code/creats/gpl.h"

// #include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/base.h"
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

void preInit()
{}

std::string _a,_b,_c;
char a[20], b[20], c[20];
int la,lb,lc;
bool deny[128][10];

void init()
{
  std::string in;
  std::cin >> in;
  std::string* to = &_a;
  for (char ch: in) {
    if (ch == '+') {
      to = &_b;
    } else if (ch == '=') {
      to = &_c;
    } else {
      to->push_back(ch);
    }
  }
  strcpy(a,_a.c_str());
  strcpy(b,_b.c_str());
  strcpy(c,_c.c_str());
  int n; 
  std::cin >> n;
  rep (i,n) {
    char cc;
    int aa;
    std::cin >> cc >> aa;
    deny[(int)cc][aa]=1;
  }
}

int ta[20], tb[20];
int repr[128];
int ans = 0;

int ch[20], chcnt;

bool check() {
  int na=0, nb=0;
  int wei = 1;
  repb (i,la-1,0) { na += wei*ta[i]; wei *= 10; }
  wei = 1;
  repb (i,lb-1,0) { nb += wei*tb[i]; wei *= 10; }
  int nc = na + nb;
  chcnt = 0;
  repb (i,lc-1,0) {
    int cur = nc % 10; nc /= 10;
    if (i == 0 && cur == 0) { goto fail; }
    if (deny[(int)c[i]][cur]) { goto fail; }
    if (repr[(int)c[i]] != -1 && repr[(int)c[i]] != cur) { goto fail; }
    if (repr[(int)c[i]] == -1) { repr[(int)c[i]] = cur; ch[chcnt++] = ((int)c[i]); }
  }
  if (nc != 0) { goto fail; }
  rep (i,chcnt) repr[ch[i]] = -1;
  return true;
fail:
  rep (i,chcnt) repr[ch[i]] = -1;
  return false;
}

void dfsb(int id) {
  if (id == lb) { ans += check(); }
  else if (repr[(int)b[id]] != -1) {
    if (id == 0 && repr[(int)b[id]] == 0) { return; }
    tb[id] = repr[(int)b[id]]; 
    dfsb(id+1); }
  else {
    rep (i,10) {
      if (id==0 && i == 0) { continue; }
      if (deny[(int)b[id]][i]) { continue; }
      repr[(int)b[id]] = i;
      tb[id] = i;
      dfsb(id+1);
      repr[(int)b[id]] = -1; } }
}

void dfsa(int id) {
  if (id == la) { dfsb(0); }
  else if (repr[(int)a[id]] != -1) {
    ta[id] = repr[(int)a[id]];
    dfsa(id+1); }
  else {
    rep (i,10) {
      if (id==0 && i == 0) { continue; }
      if (deny[(int)a[id]][i]) { continue; }
      repr[(int)a[id]] = i;
      ta[id] = i;
      dfsa(id+1);
      repr[(int)a[id]] = -1; } }
}

void solve()
{
  la = _a.size();
  lb = _b.size();
  lc = _c.size();
  int max_add = std::max(la,lb);
  if (max_add+1 < lc || max_add > lc) { puts("0"); return; }
  memset(repr, -1, sizeof(repr));
  dfsa(0);
  printf("%d\n", ans);
}
