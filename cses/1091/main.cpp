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
  int m = sc.next_int();
  std::multiset<int> a;
  for (int i = 0; i < n; i++)
    a.insert(sc.next_int());

  for (int i = 0; i < m; i++)
  {
    int b = sc.next_int();
    auto it = a.upper_bound(b);
    if (it == a.begin())
      puts("-1");
    else
    {
      --it;
      std::cout << *it << std::endl;
      a.erase(it);
    }
  }
  return 0;
}

