#include "/home/jack/code/creats/gpl.h"

#include "/home/jack/code/creats/Scanner.h"
#include "/home/jack/code/creats/log.h"
#include "/home/jack/code/creats/range.h"
#include "/home/jack/code/creats/util.h"
#include "/home/jack/code/creats/Vector.h"

// #include "/home/jack/code/creats/STree.h"
// #include "/home/jack/code/creats/Tree.h"
// #include "/home/jack/code/creats/Graph.h"
#include "/home/jack/code/creats/Intm.h"
// #include "/home/jack/code/Math/Poly/main.h"

#include <bits/stdc++.h>

// #define MULTIPLE_TEST_CASES_WITH_T
// #define MULTIPLE_TEST_CASES_WITHOUT_T
#include "/home/jack/code/creats/body.h"
// #define int long long

/** My code begins here **/

constexpr int N = 1000005;
constexpr int MOD = 1000000007;
using Int = Temps::Intm<Temps::ConstModuler<MOD>>;
Int b[N], c[N], d[N], x;
Temps::Vector<int> e[N];
int n;

/**
 *  DP States:
 *    - each node have two colors: black / white
 *      - black means this node is ordered to a crircle
 *      - white means not
 *    - each node have four states:
 *      - unvis means there IS NOT a chain in the subtree
 *      - vis   means there IS a chain in the subtree
 *      - up    means this node is going to be the up-going part of the chain (with at least one edge, not single node)
 *      - down  means this node is going to be the down-going part of the chain (alse like above)
 *  Notice that the nodes with state 'up' or 'down' are always considered to have color white
 */

constexpr int COLOR_BITS            = 1;
constexpr int COLOR_OFFSET          = 0;
constexpr int COLOR_WHITE           = 0 << COLOR_OFFSET;
constexpr int COLOR_BLACK           = 1 << COLOR_OFFSET;

constexpr int STATE_BIT             = 2;
constexpr int STATE_OFFSET          = COLOR_OFFSET + COLOR_BITS;
constexpr int STATE_UNVIS           = 0 << STATE_OFFSET;
constexpr int STATE_VIS             = 1 << STATE_OFFSET;
constexpr int STATE_UP              = 2 << STATE_OFFSET;
constexpr int STATE_DOWN            = 3 << STATE_OFFSET;

constexpr int DP_BITS               = STATE_BIT + STATE_OFFSET;

std::array<Int, 1 << DP_BITS> dp[N];

void dfs(int u) {
  auto &g = dp[u]; std::fill(g.begin(), g.end(), 0);

  g[COLOR_WHITE | STATE_UNVIS] = 1;                         // use nothing
  g[COLOR_BLACK | STATE_UNVIS] = Int(0) - d[u];             // use self_loop

  for (const int v: e[u]) { dfs(v);
    const auto vs = dp[v], f = g;
    
    g[COLOR_WHITE | STATE_UNVIS ] = f[COLOR_WHITE | STATE_UNVIS] * vs[COLOR_BLACK | STATE_UNVIS];
    g[COLOR_WHITE | STATE_VIS   ] = f[COLOR_WHITE | STATE_VIS  ] * vs[COLOR_BLACK | STATE_UNVIS]
                                  + f[COLOR_WHITE | STATE_UNVIS] * vs[COLOR_BLACK | STATE_VIS  ];
    g[COLOR_BLACK | STATE_UNVIS ] = f[COLOR_BLACK | STATE_UNVIS] * vs[COLOR_BLACK | STATE_UNVIS]
                                  - f[COLOR_WHITE | STATE_UNVIS] * vs[COLOR_WHITE | STATE_UNVIS] * b[v] * c[v];
    g[COLOR_BLACK | STATE_VIS   ] = f[COLOR_WHITE | STATE_UP   ] * vs[COLOR_WHITE | STATE_DOWN ] * b[v]
                                  + f[COLOR_WHITE | STATE_UP   ] * vs[COLOR_WHITE | STATE_UNVIS] * b[v]
                                  + f[COLOR_WHITE | STATE_DOWN ] * vs[COLOR_WHITE | STATE_UP   ] * c[v]
                                  + f[COLOR_WHITE | STATE_DOWN ] * vs[COLOR_WHITE | STATE_UNVIS] * c[v]
                                  - f[COLOR_WHITE | STATE_VIS  ] * vs[COLOR_WHITE | STATE_UNVIS] * b[v] * c[v]
                                  - f[COLOR_WHITE | STATE_UNVIS] * vs[COLOR_WHITE | STATE_VIS  ] * b[v] * c[v]
                                  + f[COLOR_BLACK | STATE_VIS  ] * vs[COLOR_BLACK | STATE_UNVIS]
                                  + f[COLOR_BLACK | STATE_UNVIS] * vs[COLOR_BLACK | STATE_VIS  ];
    g[COLOR_WHITE | STATE_UP    ] = f[COLOR_WHITE | STATE_UNVIS] * vs[COLOR_WHITE | STATE_UP   ] * c[v]
                                  + f[COLOR_WHITE | STATE_UNVIS] * vs[COLOR_WHITE | STATE_UNVIS] * c[v]
                                  + f[COLOR_WHITE | STATE_UP   ] * vs[COLOR_BLACK | STATE_UNVIS];
    g[COLOR_WHITE | STATE_DOWN  ] = f[COLOR_WHITE | STATE_UNVIS] * vs[COLOR_WHITE | STATE_DOWN ] * b[v]
                                  + f[COLOR_WHITE | STATE_UNVIS] * vs[COLOR_WHITE | STATE_UNVIS] * b[v]
                                  + f[COLOR_WHITE | STATE_DOWN ] * vs[COLOR_BLACK | STATE_UNVIS];
  }
  g[COLOR_BLACK | STATE_VIS] += g[COLOR_WHITE | STATE_UNVIS];
  g[COLOR_BLACK | STATE_VIS] += g[COLOR_WHITE | STATE_UP   ];
  g[COLOR_BLACK | STATE_VIS] += g[COLOR_WHITE | STATE_DOWN ];
}

void preInit() { } void init() {
  n = sc.n(); x = sc.n();
  for (int i=1; i<=n; ++i) { d[i] = Int(sc.n()) - x; }
  for (int i=2; i<=n; ++i) {
    e[sc.n()].push_back(i);
    b[i] = Int(sc.n()) - x;
    c[i] = Int(sc.n()) - x; }
} void solve() {
  dfs(1);
  const auto ans = dp[1][COLOR_BLACK | STATE_UNVIS]
                 - dp[1][COLOR_BLACK | STATE_VIS  ] * x;
  if (n % 2 == 1) { std::cout << Int(0) - ans << std::endl; }
  else { std::cout << ans << std::endl; }
}
