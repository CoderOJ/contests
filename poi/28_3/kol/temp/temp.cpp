#include "/home/jack/cm/debug"
#include "/home/jack/cm/math_util"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/segment_tree"
#include "/home/jack/cm/util"
#include <numeric>
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

struct node_t : public cm::segment_tree_node_base<false>
{
  using cm::segment_tree_node_base<false>::segment_tree_node_base;

  uint64_t gcd = 0;

  node_t(uint64_t gcd) : gcd(gcd) {}
  node_t(node_t lhs, node_t rhs) : gcd(std::gcd(lhs.gcd, rhs.gcd)) {}

  void assign(node_t val)
  {
    *this = val;
  }
};

CONSTRAINT(N, 500'005, 5'005)
constexpr int B = 20;

uint64_t g[B][N];

void init_g()
{
  for (int b = 0; b + 1 < B; b++)
    for (int i = 0; i + (1 << b) < N; i++)
      g[b + 1][i] = std::gcd(g[b][i], g[b][i + (1 << b)]);
}

uint64_t query(int l, int r)
{
  int len = r - l;
  int b   = 31 - cm::clz(len);
  return std::gcd(g[b][l], g[b][r - (1 << b)]);
}

int main()
{
  int n = sc.next_int();
  for (int i = 0; i < n; i++)
  {
    int      a = sc.next_int();
    uint64_t b = sc.next_long();
    g[0][a]    = std::gcd(g[0][a], b);
  }

  init_g();

  uint64_t ans = query(0, N);

  for (int i = 2; i < N; i++)
  {
    uint64_t cur_gcd = i;
    for (int j = 0; j + 1 < N; j += i)
      cur_gcd = std::gcd(cur_gcd, query(j + 1, std::min(j + i, N)));
    check_max(ans, cur_gcd);
  }

  std::cout << ans << std::endl;

  return 0;
}
