#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <set>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int x = sc.next_int();
  int n = sc.next_int();
  std::set<int> pos{0, x};
  std::multiset<int> len{x};

  for (int i = 0; i < n; i++)
  {
    int p = sc.next_int();
    auto itl = pos.lower_bound(p);
    auto itr = itl--;
    int cur_len = *itr - *itl;
    len.erase(len.find(cur_len));
    len.insert(p - *itl);
    len.insert(*itr - p);
    pos.insert(p);
    std::cout << *len.rbegin() << " ";
  }
  return 0;
}

