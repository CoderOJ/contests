#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/base.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/loop.h"
// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
#include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"

/** My code begins here **/

const int MOD = 998244353;
typedef Intm::Intm<MOD> Int;
const int N = 200005;
const int B = 31;
int n, m;

struct Arr
{
  int a[N];
  Arr () { 
    memset(a, 0, sizeof(a));
  }
  int* operator[](int id) { return a + id * (n + 1); }
};

Arr a;

void
preInit()
{}

void
init()
{
  n = sc.n();
  m = sc.n();
  rep(i, n) rep(j, n) a[i][j] = sc.n();
}

namespace solve_sum {
int
main()
{
  Int res = 0;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      res += Int(i + 1) * Int(j + 1) * Int(n - i) * Int(n - j) * Int(a[i][j]);
  return res;
}
} /* solve_sum */

namespace solve_or {
Int
main_bit(int b)
{
  Arr right, down;
  repb (i,n-1,0) repb (j,m-1,0) {
    if ((a[i][j]>>b) & 1) {
      right[i][j] = down[i][j] = 0;
    } else {
      right[i][j] = right[i][j+1] + 1;
      down[i][j] = down[i+1][j] + 1;
    }
  }
  repb (i,n-1,0) repb (j,m-1,0) {
    right[i][j] += right[i+1][j];
    down[i][j] += down[i][j+1];
  }
  Arr dp;
  Int ans(0);
  repb (i,n-1,0) repb (j,m-1,0) {
    if ((a[i][j] >> b) & 1) {
      dp[i][j] = 0;
    } else {
      if (dp[i][j+1] == 0) {
        dp[i][j] = down[i][j] - down[i][j+1];
      } else if (dp[i+1][j] == 0) {
        dp[i][j] = right[i][j] - right[i+1][j];
      } else {
        int go_right = right[i][j] - right[i+1][j];
        see(right[i][j], right[i+1][j], go_right);
        dp[i][j] = dp[i+1][j] + go_right;
        int shift_j = j + go_right;
        int shift_i = i + down[i+1][shift_j] - down[i+1][shift_j+1];
        dp[i][j] -= right[i+1][shift_j] - right[shift_i+1][shift_j];
      }
    }
    ans += Int(n-i) * Int(m-j) - Int(dp[i][j]);
  }
  return ans;
}
int
main()
{
  Int res = 0;
  rep(i, B) res += Int(1 << i) * main_bit(i);
  return res;
}
} /* solve_or */

namespace solve_and {
Int
main_bit(int b)
{
  Arr right, down;
  repb (i,n-1,0) repb (j,m-1,0) {
    if ((a[i][j]>>b) & 1) {
      right[i][j] = right[i][j+1] + 1;
      down[i][j] = down[i+1][j] + 1;
    } else {
      right[i][j] = down[i][j] = 0;
    }
  }
  repb (i,n-1,0) repb (j,m-1,0) {
    right[i][j] += right[i+1][j];
    down[i][j] += down[i][j+1];
  }
  Arr dp;
  Int ans(0);
  repb (i,n-1,0) repb (j,m-1,0) {
    if ((a[i][j] >> b) & 1) {
      if (dp[i][j+1] == 0) {
        dp[i][j] = down[i][j] - down[i][j+1];
      } else if (dp[i+1][j] == 0) {
        dp[i][j] = right[i][j] - right[i+1][j];
      } else {
        int go_right = right[i][j] - right[i+1][j];
        dp[i][j] = dp[i+1][j] + go_right;
        int shift_j = j + go_right;
        int shift_i = i + down[i+1][shift_j] - down[i+1][shift_j+1];
        dp[i][j] -= right[i+1][shift_j] - right[shift_i+1][shift_j];
      }
    } else {
      dp[i][j] = 0;
    }
    ans += Int(dp[i][j]);
  }
  return ans;
}
int
main()
{
  Int res = 0;
  rep(i, B) res += Int(1 << i) * main_bit(i);
  return res;
}
} /* solve_and */

namespace solve_xor {
int
main()
{
  return -1;
}
} /* solve_xor */

void
solve()
{
  printf("%d %d %d %d\n",
         (solve_sum::main()),
         (solve_and::main()),
         (solve_or::main()),
         (solve_xor::main()));
}
