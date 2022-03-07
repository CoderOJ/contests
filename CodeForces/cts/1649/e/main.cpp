#include "/home/jack/cm/debug"
#include "/home/jack/cm/intm"
#include "/home/jack/cm/math_util"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/segment_tree"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int MOD = 998244353;
using int_t       = cm::intm<MOD>;
using mu          = cm::math_util<int_t>;

CONSTRAINT(N, 200'005, 205)

int cnt[N];

int s[N], t[N], n, m;

struct node_t : public cm::segment_tree_node_base<true>
{
  using cm::segment_tree_node_base<true>::segment_tree_node_base;

  int_t sum = 1;
  int_t mul = 1;

  node_t(node_t lhs, node_t rhs) : sum(lhs.sum + rhs.sum) {}

  void push_mul(int_t mul)
  {
    this->sum *= mul;
    this->mul *= mul;
  }

  void push_down(node_t &lhs, node_t &rhs)
  {
    if (mul != 1)
    {
      lhs.push_mul(mul);
      rhs.push_mul(mul);
      mul = 1;
    }
  }
};

cm::segment_tree<node_t> sgt(N);

int main()
{
  mu::fac.require(N);

  n = sc.next_int();
  m = sc.next_int();
  for (int i = 0; i < n; i++)
    s[i] = sc.next_int();
  for (int i = 0; i < m; i++)
    t[i] = sc.next_int();

  int_t mul_all = 1;
  for (int i = 0; i < n; i++)
  {
    cnt[s[i]] += 1;
    mul_all *= cnt[s[i]];
  }
  int_t mul_all_inv = mul_all.inv();

  for (int i = 0; i < N; i++)
    sgt.modify(i, i + 1, &node_t::push_mul, cnt[i] * mul_all_inv);

  int_t ans = 0;
  for (int i = 0; i < std::min(n, m); i++)
  {
    ans += sgt.query(0, t[i]).sum * mu::fac(n - i - 1);
    // see(i, ans);
    sgt.modify(0, N, &node_t::push_mul, int_t(cnt[t[i]]));
    if (cnt[t[i]] > 0)
    {
      sgt.modify(
          t[i], t[i] + 1, &node_t::push_mul, int_t(cnt[t[i]] - 1) / cnt[t[i]]);
      cnt[t[i]] -= 1;
    }
    else
    {
      break;
    }
  }

  if (std::none_of(cnt, cnt + N, [](int x) { return x != 0; }) && m > n)
    ans += 1;

  std::cout << ans << std::endl;

  return 0;
}
