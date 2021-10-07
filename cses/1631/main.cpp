#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
#define int long long
  int n = sc.next_int();
  int sum = 0, max = 0;
  for (int i = 0; i < n; i++)
  {
    int a = sc.next_int();
    sum += a;
    check_max(max, a);
  }

  std::cout << std::max(sum, max * 2) << std::endl;

  return 0;
}

