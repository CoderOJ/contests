#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  long long ans = 0;
  int last = 0;
  for (int i = 0; i < n; i++)
  {
    int a = sc.next_int();
    if (a < last)
      ans += last - a;
    else
      last = a;
  }
  std::cout << ans << std::endl;
  return 0;
}

