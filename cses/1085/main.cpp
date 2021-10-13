#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>
#include <numeric>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{

#define int long long
  int n = sc.next_int();
  int k = sc.next_int();
  std::vector<int> a(n);
  for (int i = 0; i < n; i++) a[i] = sc.next_int();

  int l = *std::max_element(a.begin(), a.end());
  int r = std::accumulate(a.begin(), a.end(), 0ll);
  while (l < r)
  {
    int m = (l + r) / 2;
    int bk = 1, cur = 0;
    for (int x: a)
    {
      if (cur + x > m) cur = 0, bk++;
      cur += x;
    }
    if (bk > k) l = m + 1;
    else r = m;
  }

  std::cout << l << std::endl;

  return 0;
}

