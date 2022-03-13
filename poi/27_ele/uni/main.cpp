#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

uint64_t find_minxor(uint64_t l, uint64_t r, int k)
{
  if (l <= r)
    return 0;
  else if (((l >> k) & 1) == 0)
    return find_minxor(l, r, k - 1);
  else if (((r >> k) & 1) == 1)
    return find_minxor(l ^ (1ull << k), r ^ (1ull << k), k - 1);
  else
    return (1ull << k) + find_minxor(l ^ (1ull << k), r, k - 1);
}

uint64_t solve(uint64_t l, uint64_t r, int k)
{
  static uint64_t mem[64];

  if (l == 0 && r == (1ull << (k + 1)) - 1 && mem[k] != 0)
    return mem[k];

  if (k == -1)
    return 0;

  if ((l >> k) & 1)
  {
    l ^= (1ull << k);
    r ^= (1ull << k);
  }
  if (((r >> k) & 1) == 0)
  {
    return solve(l, r, k - 1);
  }
  else
  {
    uint64_t res_c = (1ull << k) + find_minxor(l, r ^ (1ull << k), k - 1);
    uint64_t res_l = solve(l, (1ull << k) - 1, k - 1);
    uint64_t res_r = solve(0, r ^ (1ull << k), k - 1);

    uint64_t res = res_c + res_l + res_r;
    if (l == 0 && r == (1ull << (k + 1)) - 1)
      mem[k] = res;

    return res_c + res_l + res_r;
  }
}

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    uint64_t l = sc.next_long();
    uint64_t r = sc.next_long();
    std::cout << solve(l, r, 60) << std::endl;
  }
  return 0;
}
