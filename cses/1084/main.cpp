#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  int m = sc.next_int();
  int k = sc.next_int();
  std::vector<int> a(n), b(m);

  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();
  std::sort(a.begin(), a.end());
  for (int i = 0; i < m; i++)
    b[i] = sc.next_int();
  std::sort(b.begin(), b.end());
  
  int bi = 0; 
  int ans = 0;
  for (int x: a)
  {
    while (bi < m && b[bi] < x - k) bi++;
    if (bi < m && b[bi] <= x + k) { ans++; bi++; }
  }

  std::cout << ans << std::endl;

  return 0;
}

