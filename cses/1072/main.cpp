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
  for (int n = 1; n <= t; n++)
  {
    const int n2 = n * n;
    int ans = n2 * (n2 - 1) / 2;
    if (n >= 3)
      ans -= 4 * (n - 2) * (n - 1);
    std::cout << ans << std::endl;
  }
  return 0;
}

