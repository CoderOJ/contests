#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <map>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#ifdef CM_DEBUG
cm::scanner<cm::optimal_reader> sc(stdin);
FILE                           *output = stdout;
#else
cm::scanner<cm::optimal_reader> sc(fopen("borderless.in", "r"));
FILE                           *output = fopen("borderless.out", "w");
#endif

uint64_t last(uint64_t mask, int n)
{
  return mask & ((1ull << n) - 1);
}

uint64_t have_border(uint64_t mask, int n)
{
  for (int i = 1; i * 2 <= n; i++)
    if ((mask >> (n - i)) == last(mask, i))
      return true;
  return false;
}

std::map<std::pair<uint64_t, int>, uint64_t> mem;

uint64_t count(uint64_t mask, int n)
{
  if (mem.find({mask, n}) != mem.end())
    return mem[{mask, n}];
  uint64_t res = mask;
  for (int i = 1; i * 2 <= n; i++)
  {
    res -= count(mask >> (n - i), i) * (1ull << (n - i * 2));
    if (!have_border(mask >> (n - i), i))
    {
      res -= last(mask, n - i) >> i;
      if (last(mask, i) > (mask >> (n - i)))
        res -= 1;
    }
  }
  return mem[{mask, n}] = res;
}

void solve(int n, uint64_t k)
{
  uint64_t l = 0;
  uint64_t r = (2ull << (n - 1)) - 1;
  while (l < r)
  {
    uint64_t mid = l + (r - l) / 2 + 1;
    if (count(mid, n) < k)
      l = mid;
    else
      r = mid - 1;
  }
  for (int i = n - 1; i >= 0; i--)
    fputc(((l >> i) & 1) ? 'b' : 'a', output);
  fputc('\n', output);
}

int main()
{
  while (true)
  {
    int      n;
    uint64_t k;
    n = sc.next_int();
    k = sc.next_long();
    if (n == 0 && k == 0)
      break;
    solve(n, k);
  }
  return 0;
}
