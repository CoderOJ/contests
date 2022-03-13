#include "/home/jack/cm/debug"
#include "/home/jack/cm/proof.hpp"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

template <class value_type>
struct lr_vector : std::vector<value_type>
{
  int l, r;

  lr_vector() = default;
  lr_vector(int l, int r) : std::vector<value_type>(r - l + 1), l(l), r(r) {}

  value_type operator[](int id) const
  {
    return std::vector<value_type>::operator[](id - l);
  }
  value_type &operator[](int id)
  {
    return std::vector<value_type>::operator[](id - l);
  }
};

struct dp_t
{
  int64_t val[4];
};

constexpr int N = 200005;

using namespace cm::proof;
using vert   = int_index<0, N>;
using edge_t = std::pair<vert, int64_t>;

index_array<vert, std::vector<edge_t>> e;

int n;

dp_t dfs(vert u, vert f)
{
  std::vector<dp_t> sons;
  for (const auto &[v, w] : e[u])
    if (v != f)
    {
      dp_t dpv = dfs(v, u);
      dp_t vv;
      vv.val[0] = std::max({dpv.val[0], dpv.val[3] + w});
      vv.val[1] = dpv.val[0] + w;
      vv.val[2] = dpv.val[1] + w;
      vv.val[3] = dpv.val[2] + w;
      sons.push_back(vv);
    }
}

int main()
{
  n = sc.next_int();
  for (int i = 1; i < n; i++)
  {
    vert    u(sc.next_int());
    vert    v(sc.next_int());
    int64_t w(sc.next_int());
    e[u].emplace_back(v, w);
    e[v].emplace_back(u, w);
  }
  return 0;
}
