#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
// #include "/home/jack/cm/math_util.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <memory>

cm::scanner<cm::optimal_reader> sc(stdin);

struct node_t
{
  std::unique_ptr<node_t> s[2];
  int                     size = 0;
};

void trie_insert(const std::unique_ptr<node_t> &u, uint32_t v, int d)
{
  u->size += 1;
  if (d > 0)
  {
    auto c = (v >> (d - 1)) & 1;
    if (u->s[c] == nullptr)
      u->s[c] = std::make_unique<node_t>();
    trie_insert(u->s[c], v, d - 1);
  }
}

int solve_isolate(
    const std::unique_ptr<node_t> &u,
    const std::unique_ptr<node_t> &v,
    uint32_t                       k,
    int                            d)
{
  if (u == nullptr && v == nullptr)
    return 0;
  else if (u == nullptr)
    return v->size;
  else if (v == nullptr)
    return u->size;
  else
  {
    if (d == 0)
      return std::max(u->size, v->size);
    else
    {
      auto c = (k >> (d - 1)) & 1;
      if (c == 0)
        return std::max({
            u->size,
            v->size,
            solve_isolate(u->s[0], v->s[0], k, d - 1),
            solve_isolate(u->s[1], v->s[1], k, d - 1),
        });
      else
        return solve_isolate(u->s[0], v->s[1], k, d - 1)
             + solve_isolate(u->s[1], v->s[0], k, d - 1);
    }
  }
}

int solve_common(const std::unique_ptr<node_t> &u, uint32_t k, int d)
{
  if (u == nullptr)
    return 0;
  else
  {
    auto c = (k >> (d - 1)) & 1;
    if (c == 0)
      return std::max(
          solve_common(u->s[0], k, d - 1), solve_common(u->s[1], k, d - 1));
    else
      return solve_isolate(u->s[0], u->s[1], k, d - 1);
  }
}

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    const int B = 20;

    int n   = sc.next_int();
    int thr = sc.next_int() + 1;

    auto tr = std::make_unique<node_t>();
    for (int i = 0; i < n; i++)
    {
      int x = sc.next_int();
      trie_insert(tr, x, B);
    }

    if (thr == (1 << 20))
      printf("%d\n", n);
    else
      printf("%d\n", solve_common(tr, thr, B));
  }
  return 0;
}
