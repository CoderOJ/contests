#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <set>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
#define int long long

  int n = sc.next_int();
  int l = sc.next_int();
  int r = sc.next_int();
  std::vector<int> a(n + 1), p(n + 1);

  int ans = -1e18;
  std::multiset<int> ava;
  for (int i = 1; i <= n; i++)
  {
    a[i] = sc.next_int();
    p[i] = p[i - 1] + a[i];
    if (i >= l) 
    {
      ava.insert(p[i - l]);
      check_max(ans, p[i] - *ava.begin());
    }
    if (i >= r)
    {
      ava.erase(ava.find(p[i - r]));
    }
  }

  std::cout << ans << std::endl;

  return 0;
}

