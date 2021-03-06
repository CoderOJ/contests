#include <bits/stdc++.h>
#include "/home/jack/code/creats/loop.h"
#include "/home/jack/code/creats/log.h"


class HamiltonianConstruction {

public:
  std::vector<std::string> construct (int n) {
    constexpr int N = 20;
    std::vector<std::string> R;
    rep (i,N) { R.push_back(""); 
      rep (j,N) R.back().push_back('N'); }
    rep (i,N-1) { R[i+1][i] = 'Y'; }
    repa (i,N-1) repi (j,i+1,N-1) { R[i][j] = 'Y'; }
    rep (i,17) if (n & (1<<i)) { R[0][17-i] = 'Y'; }
    return R;
  }

};
