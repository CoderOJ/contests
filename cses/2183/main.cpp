#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{

#define int long long
  int n = sc.next_int();
  std::vector<int> a(n);
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();
  std::sort(a.begin(), a.end());
  a.push_back(1e18);

  int cur = 0;
  for (int x: a)
  {
    if (x > cur + 1)
    {
      std::cout << cur + 1 << std::endl;
      return 0;
    }
    cur += x;
  }
  return 0;
}

