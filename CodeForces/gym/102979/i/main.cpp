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

  std::vector<int> a(n + 1, -1);
  for (int i = 0; i < n; i++)
    a[i + 1] = sc.next_int();

  a.erase(std::unique(a.begin(), a.end()), a.end());
  n = static_cast<int>(a.size());

  int cnt = 0;
  for (int i = 1; i + 1 < n; i++)
    if ((a[i] > a[i - 1] && a[i] > a[i + 1]) ||
        (a[i] < a[i - 1] && a[i] < a[i + 1]))
      cnt += 1;

  int ans = 0;
  while ((1 << ans) <= cnt)
    ans += 1;

  std::cout << ans << std::endl;

  return 0;
}
