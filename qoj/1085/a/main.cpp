#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
#include "/home/jack/cm/math_util.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <cinttypes>
#include <cstdint>
#include <functional>
#include <tuple>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

using matrix_t = cm::matrix_t<int64_t, 2, 2>;
using vector_t = cm::matrix_t<int64_t, 2, 1>;

constexpr std::tuple<matrix_t, matrix_t, matrix_t, int64_t> m_trans(
    uint32_t type)
{
  constexpr matrix_t m_id{{1, 0}, {0, 1}};
  constexpr matrix_t m_t0{{1, 1}, {0, 0}};
  constexpr matrix_t m_all{{1, 1}, {1, 1}};
  constexpr matrix_t m_swap{{0, 1}, {1, 0}};
  constexpr matrix_t m_pre{{1, 0}, {1, 1}};
  constexpr matrix_t m_dpre{{1, 0}, {-1, 1}};
  constexpr matrix_t m_suf{{1, 1}, {0, 1}};
  constexpr matrix_t m_dsuf{{1, -1}, {0, 1}};
  constexpr matrix_t m_xor{{1, 1}, {1, -1}};

  switch (type)
  {
  case 0:
    return {m_t0, m_t0, m_id, 1};

  case 1:
    return {m_suf, m_suf, m_dsuf, 1};

  case 2: {
    const auto [ma, mb, mr, d] = m_trans(1);
    return {ma, mb * m_swap, mr, d};
  }

  case 3:
    return {m_id, m_all, m_id, 1};

  case 4: {
    const auto [ma, mb, mr, d] = m_trans(1);
    return {ma * m_swap, mb, mr, d};
  }

  case 5:
    return {m_all, m_id, m_id, 1};

  case 6:
    return {m_xor, m_xor, m_xor, 2};

  case 7:
    return {m_pre, m_pre, m_dpre, 1};

  default: {
    const auto [ma, mb, mr, d] = m_trans(15 ^ type);
    return {ma, mb, m_swap * mr, d};
  }
  }
}

int main()
{
  int n = sc.next_int();

  std::vector<std::tuple<matrix_t, matrix_t, matrix_t, int>> op;
  for (int i = 0; i < n; i++)
  {
    uint32_t mask = 0;
    for (int i = 3; i >= 0; i--)
      mask |= (sc.next_char() - '0') << i;
    op.emplace_back(m_trans(mask));
  }

  auto read_list = [](int n) {
    std::vector<int64_t> a(n);
    for (int i = 0; i < n; i++)
      a[i] = sc.next_int();
    return a;
  };

  auto as = read_list(1 << n);
  auto bs = read_list(1 << n);

  for (int i = 0; i < n; i++)
  {
    const auto &[ma, mb, mr, d] = op[i];
    for (int j = 0; j < (1 << n); j++)
      if (j & (1 << i))
      {
        int px = j ^ (1 << i), py = j;

        vector_t va{{as[px]}, {as[py]}};
        vector_t vb{{bs[px]}, {bs[py]}};
        vector_t ra = ma * va;
        vector_t rb = mb * vb;

        as[px] = ra[0][0], as[py] = ra[1][0];
        bs[px] = rb[0][0], bs[py] = rb[1][0];
      }
  }

  std::vector<int64_t> rs = cm::vec_map(std::multiplies<>(), as, bs);

  for (int i = 0; i < n; i++)
  {
    const auto &[ma, mb, mr, d] = op[i];
    for (int j = 0; j < (1 << n); j++)
      if (j & (1 << i))
      {
        int px = j ^ (1 << i), py = j;

        vector_t vr{{rs[px]}, {rs[py]}};
        vector_t rr = mr * vr;

        rs[px] = rr[0][0] / d, rs[py] = rr[1][0] / d;
      }
  }

  for (int i = 0; i < (1 << n); i++)
    printf("%" SCNi64 " ", rs[i]);
  puts("");

  return 0;
}
