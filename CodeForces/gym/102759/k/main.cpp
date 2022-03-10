#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();

  std::vector<std::tuple<int, int, int>> vs;
  for (int i = 0; i < n; i++)
  {
    int x = sc.next_int();
    int y = sc.next_int();
    vs.emplace_back(x, y, i);
  }

  std::sort(vs.begin(), vs.end());

  std::cout << 2 * n - 1 << std::endl;
  for (int i = 0; i < n; i++)
    std::cout << std::get<2>(vs[i]) + 1 << " ";
  for (int i = n - 2; i >= 0; i--)
    std::cout << std::get<2>(vs[i]) + 1 << " ";

  return 0;
}
