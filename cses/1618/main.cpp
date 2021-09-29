#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  int ans = 0;
  while (n >= 5)
  {
    ans += n / 5;
    n /= 5;
  }
  std::cout << ans << std::endl;
  return 0;
}

