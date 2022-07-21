#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
#include "/home/jack/cm/intm.hpp"
#include "/home/jack/cm/math_util.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <type_traits>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  constexpr int MOD = 1'000'000'007;
  using int_t       = cm::intm<MOD>;
  using mu          = cm::math_util<int_t>;

  int n = sc.next_int();
  if (n % 2 == 1)
    n += 1;
  int hn = n / 2;

  int   m = sc.next_int();
  int_t c = sc.next_int();

  auto e = [&] {
    std::vector<std::vector<int>> a(n);

    for (int i = 0; i < m; i++)
    {
      int u = sc.next_int() - 1;
      int v = sc.next_int() - 1;
      a[u].push_back(v);
      a[v].push_back(u);
    }

    return a;
  }();

  auto dp_chain = [&] {
    std::vector<std::vector<int_t>> dp(1 << hn, std::vector<int_t>(n, 0));
    for (int u = 0; u < n; u++)
      dp[1 << (u / 2)][u] = 1;

    for (int i = 0; i < (1 << hn); i++)
      for (int su = 0; su < n; su++)
        if (dp[i][su])
        {
          int u = su ^ 1;
          for (int v: e[u])
          {
            int hv = v / 2;
            if (!(i & (1 << hv)))
              dp[i | (1 << hv)][v] += c * dp[i][su];
          }
        }

    std::vector<int_t> a(1 << hn);
    for (int i = 0; i < (1 << hn); i++)
    {
      for (int u = 0; u < n; u++)
        a[i] += dp[i][u];
      a[i] /= 2;
    }

    return a;
  }();

  auto dp_circle = [&] {
    std::vector<std::vector<int_t>> dp(1 << hn, std::vector<int_t>(n, 0));
    for (int u = 0; u < n; u += 2)
      dp[1 << (u / 2)][u] = c;

    for (int i = 0; i < (1 << hn); i++)
      for (int su = 0; su < n; su++)
        if (dp[i][su])
        {
          int u = su ^ 1;
          for (int v: e[u])
          {
            int hv = v / 2;
            if (!(i & (1 << hv)) && hv > __builtin_ctz(i))
              dp[i | (1 << hv)][v] += c * dp[i][su];
          }
        }

    std::vector<int_t> a(1 << hn);
    for (int i = 1; i < (1 << hn); i++)
      for (int u = 0; u < n; u++)
        if (std::find(e[u ^ 1].begin(), e[u ^ 1].end(), __builtin_ctz(i) * 2)
            != e[u ^ 1].end())
          a[i] += dp[i][u];

    return a;
  }();

  auto fractionalize = [](const auto &v) {
    std::vector<std::vector<int_t>> a(
        __builtin_ctzl(v.size()) + 1, std::vector<int_t>(v.size(), 0));
    for (size_t i = 0; i < v.size(); i++)
      a[__builtin_popcountl(i)][i] = v[i];
    return a;
  };

  auto gather = [](const auto &v) {
    size_t m = v[0].size();

    std::vector<int_t> a(m, 0);
    for (const auto &vv: v)
      for (size_t i = 0; i < m; i++)
        a[i] += vv[i];

    return a;
  };

  auto fwt = [](auto v) {
    for (size_t i = 1; i < v.size(); i <<= 1)
      for (size_t j = 0; j < v.size(); j++)
        if (j & i)
          v[j] += v[j ^ i];
    return v;
  };

  auto ifwt = [](auto v) {
    for (size_t i = 1; i < v.size(); i <<= 1)
      for (size_t j = 0; j < v.size(); j++)
        if (j & i)
          v[j] -= v[j ^ i];
    return v;
  };

  auto exp = [](const auto &f) {
    int m = (int)f.size();
    mu::inv.require(m);

    std::vector<int_t> g{1};
    for (int i = 1; i < m; i++)
    {
      int_t cur = 0;
      for (int j = 0; j < i; j++)
        cur += g[j] * (i - j) * f[i - j];
      g.emplace_back(cur * mu::inv(i));
    }

    return g;
  };

  using cm::pipe::operator|;

  auto ans = cm::vec_map(std::plus<>(), dp_chain, dp_circle) //
           | fractionalize                                   //
           | cm::mapper(fwt)                                 //
           | cm::vec_transpose<int_t>                        //
           | cm::mapper(exp)                                 //
           | cm::vec_transpose<int_t>                        //
           | cm::mapper(ifwt)                                //
           | gather                                          //
           | cm::vec_take((1 << hn) - 1)                     //
      ;

  std::cout << ans << std::endl;

  return 0;
}
