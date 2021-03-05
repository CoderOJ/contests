#include <bits/stdc++.h>
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"


class TheBrickTowerMediumDivOne {

public:
  std::vector<int> find (std::vector<int> a) {
    int n = a.size(), a_min = *std::min_element(a.begin(), a.end());
    std::vector<bool> vis(a.size());
    std::vector<int> ans;
    int last = std::numeric_limits<int>::max();
    bool reached = false;
    rep (i,n) {
      int pos = -1;
      rep (p,n) if (!vis[p]) {
        bool ok = false;
        if (!reached) { ok = (a[p] <= last); }
        else {
          ok = true;
          rep (k,n) if (!vis[k]) {
            if (a[k] < a[p]) { ok=false; break; } } }
        if (ok) { pos = p; break; } }
      assert(pos != -1);
      if (a[pos] == a_min) { reached = true; }
      ans.push_back(pos); vis[pos] = true;
      last = a[pos]; }
    return ans;
  }

};
