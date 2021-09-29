#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
#define int long long
  int t = sc.next_int();
  while (t --)
  {
    int x = sc.next_int();
    int y = sc.next_int();
    int id = std::max(x, y);
    int prev = (id - 1) * (id - 1);
    if (id % 2 == 0)
      std::cout << prev + (x == id ? id + id - y : x) << std::endl;
    else
      std::cout << prev + (y == id ? id + id - x : y) << std::endl;
  }
  return 0;
}

