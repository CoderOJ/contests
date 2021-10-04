#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <set>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  int x = sc.next_int();
  std::set<std::pair<int,int>> pre;

  for (int i = 0; i < n; i++)
  {
    int a = sc.next_int();
    if (pre.lower_bound(std::make_pair(x - a, 0)) != pre.end() && 
        pre.lower_bound(std::make_pair(x - a, 0))->first == x - a)
    {
      std::cout << pre.lower_bound(std::make_pair(x - a, 0))->second + 1 << " " << i + 1 << std::endl;
      return 0;
    }
    pre.emplace(a, i);
  }

  puts("IMPOSSIBLE");
  return 0;
}

