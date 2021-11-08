#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <functional>
#include <string>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  int a = sc.next_int();
  int b = sc.next_int();
  if (__builtin_popcount(a) % 2 == __builtin_popcount(b) % 2)
  {
    puts("NO");
    return 0;
  }

  std::function<std::basic_string<int>(int, int, int)> construct =
      [&](int n, int a, int b) -> std::basic_string<int> {
    if (n == 1)
      return {a, b};
    const int high_bit = 1 << (n - 1);
    if ((a & high_bit) == (b & high_bit))
    {
      auto part = construct(n - 1, a, b);
      auto bipart = construct(n - 1, part[0] ^ high_bit, part[1] ^ high_bit);
      return part.substr(0, 1) + bipart + part.substr(1);
    }
    else
    {
      int relay = a ^ 1;
      auto part_a = construct(n - 1, a, relay);
      auto part_b = construct(n - 1, relay ^ high_bit, b);
      return part_a + part_b;
    }
  };

  puts("YES");
  auto ans = construct(n, a, b);
  for (int x : ans)
    std::cout << x << " ";

  return 0;
}
