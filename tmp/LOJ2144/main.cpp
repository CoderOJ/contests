#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

struct dp_t
{
  int ans0s   = -0x3f3f3f3f;
  int ans01   = -0x3f3f3f3f;
  int ans10_0 = -0x3f3f3f3f;
  int ans10_1 = -0x3f3f3f3f;
  int ans1s   = -0x3f3f3f3f;
  int ans11   = -0x3f3f3f3f;
  int ans20_0 = -0x3f3f3f3f;
  int ans20_1 = -0x3f3f3f3f;

  dp_t(int w) : ans0s(w), ans01(w), ans10_1(w), ans11(w), ans20_1(w) {}

  int answer() const
  {
    return std::max({ans11, ans20_0, ans20_1});
  }
};

dp_t join(dp_t u, dp_t v)
{
  dp_t r(u.ans0s);

  // clang-format off
  r.ans01 = std::max({
    u.ans01, 
    u.ans0s + v.ans01 - 1
  });
  r.ans10_0 = std::max({
    u.ans10_0, 
    v.ans10_0, 
    v.ans10_1, 
  });
  r.ans10_1 = std::max({
    r.ans01,
    u.ans10_1,
    u.ans01 + v.ans01 - 1,
  });
  r.ans1s = std::max({
    u.ans1s,
    u.ans0s + v.ans10_0,
    u.ans0s + v.ans10_1 - 1,
    r.ans10_1,
  });
  r.ans11 = std::max({
    u.ans11,
    u.ans1s + v.ans01 - 1,
    u.ans01 + v.ans10_0,
    u.ans01 + v.ans10_1 - 1,
    u.ans0s + v.ans11 - 1,
  });
  r.ans20_0 = std::max({
    u.ans20_0, 
    u.ans10_0 + v.ans10_0,
    u.ans10_0 + v.ans10_1,
    v.ans20_0, 
    v.ans20_1, 
  });
  r.ans20_1 = std::max({
    r.ans11,
    u.ans20_1,
    u.ans10_1 + v.ans10_0,
    u.ans10_1 + v.ans10_1 - 1,
    u.ans01 + v.ans11 - 1, 
    u.ans11 + v.ans01 - 1
  });
  // clang-format on

  return r;
}

constexpr int N = 500005;

std::vector<int> e[N];

int n;

dp_t dfs(int u, int f)
{
  dp_t dpu = static_cast<int>(e[u].size()) - 1;
  for (int v : e[u])
    if (v != f)
    {
      dp_t dpv = dfs(v, u);
      dpu      = join(dpu, dpv);
    }
  // see(u);
  // see(dpu.ans0s);
  // see(dpu.ans01);
  // see(dpu.ans10_0);
  // see(dpu.ans10_1);
  // see(dpu.ans1s);
  // see(dpu.ans11);
  // see(dpu.ans20_0);
  // see(dpu.ans20_1);
  return dpu;
}

int main()
{
  int T = sc.next_int();
  int x = sc.next_int();
  for (int i = 0; i < T; i++)
  {
    n = sc.next_int();
    for (int i = 0; i < x * 2; i++)
      sc.next_int();
    for (int i = 1; i <= n; i++)
      e[i].clear();
    for (int i = 1; i < n; i++)
    {
      int u = sc.next_int();
      int v = sc.next_int();
      e[u].push_back(v);
      e[v].push_back(u);
    }

    dp_t ans = dfs(1, 0);
    std::cout << 1 + ans.answer() << std::endl;
  }
  return 0;
}
