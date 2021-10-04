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
  int k = sc.next_int();
  std::multiset<int> a;
  for (int i = 0; i < n; i++)
    a.insert(sc.next_int());

  int ans = 0;
  while (!a.empty())
  {
    ans++;
    int c = *--a.end();
    a.erase(--a.end());

    if (!a.empty())
    {
      auto it = a.upper_bound(k - c);
      if (it != a.begin())
        a.erase(--it);
    }
  }

  std::cout << ans << std::endl;

  return 0;
}

