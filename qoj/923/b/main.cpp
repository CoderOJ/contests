#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
// #include "/home/jack/cm/math_util.hpp"
#include "/home/jack/cm/scanner.hpp"
#include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <algorithm>
#include <string>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

bool is_valid(const std::string &s)
{
  int a = 0;
  for (char c: s)
  {
    a += (c == '(') ? 1 : -1;
    if (a < 0)
      return false;
  }
  return a == 0;
}

struct node_t : public cm::segment_tree_node_base<false>
{
  int sum     = -1;
  int max_suf = 0;

  node_t() = default;

  node_t(int v) : sum(v), max_suf(std::max(v, 0)) {}

  node_t(const node_t &lhs, const node_t &rhs) :
      sum(lhs.sum + rhs.sum),
      max_suf(std::max(lhs.max_suf + rhs.sum, rhs.max_suf))
  {
  }

  node_t &operator=(const node_t &) = default;
};

int main()
{
  int n = sc.next_int();

  std::vector<int> col(n + n);
  for (int i = 0; i < n + n; i++)
    col[i] = sc.next_int() - 1;

  std::vector<std::vector<int>> occur(n);
  for (int i = 0; i < n + n; i++)
    occur[col[i]].push_back(i);

  cm::segment_tree<node_t> d(n + n);
  std::string              ans(n + n, ')');

  std::sort(occur.begin(), occur.end());
  for (const auto &iv: occur)
  {
    int ia = iv[0], ib = iv[1];

    d.modify(ia, ia + 1, &node_t::operator=, node_t(1));
    d.modify(ib, ib + 1, &node_t::operator=, node_t(1));
    if (d.query(0, n + n).max_suf <= 0)
    {
      ans[ia] = '(';
      ans[ib] = '(';
    }
    else
    {
      d.modify(ia, ia + 1, &node_t::operator=, node_t(-1));
      d.modify(ib, ib + 1, &node_t::operator=, node_t(-1));
    }
  }
  // see(ans);

  if (!is_valid(ans))
    puts("(");
  else
    std::cout << ans << std::endl;

  return 0;
}
