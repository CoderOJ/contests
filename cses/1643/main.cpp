#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  std::vector<int> a(n);
  for (int i = 0; i < n; i++)
    a[i] = sc.next_int();

  long long cur = 0, ans = -1e10;
  for (int i = 0; i < n; i++)
    check_max(ans, cur = std::max(cur, 0ll) + a[i]);
  std::cout << ans << std::endl;

  return 0;
}

