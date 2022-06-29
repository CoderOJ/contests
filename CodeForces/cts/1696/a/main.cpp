#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    int n   = sc.next_int();
    int z   = sc.next_int();
    int ans = 0;
    for (int i = 0; i < n; i++)
      cm::check_max(ans, sc.next_int() | z);
    std::cout << ans << std::endl;
  }
  return 0;
}
