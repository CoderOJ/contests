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

  std::vector<int> a(n);
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();

  std::sort(a.begin(), a.end(), std::greater<int>());
  if (n > 500)
  {
    a.resize(500);
    n = 500;
  }

  int ans = -1;
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      for (int k = j + 1; k + 4 < n; k++)
        if (a[i] < a[j] + a[k] &&
            a[j] + a[k] < a[k + 1] + a[k + 2] + a[k + 3] + a[k + 4])
          check_max(ans,
                    a[i] + a[j] + a[k] + a[k + 1] + a[k + 2] + a[k + 3] +
                        a[k + 4]);

  std::cout << ans << std::endl;

  return 0;
}
