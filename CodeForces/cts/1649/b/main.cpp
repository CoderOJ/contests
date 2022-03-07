#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int t = sc.next_int();
  for (int i = 0; i < t; i++)
  {
    int n = sc.next_int();

    int64_t max = 0, sum = 0;
    for (int i = 0; i < n; i++)
    {
      int64_t x = sc.next_int();
      check_max(max, x);
      sum += x;
    }

    if (sum == 0)
      puts("0");
    else if (max * 2 - 1 <= sum)
      puts("1");
    else
      std::cout << max * 2 - sum << std::endl;
  }
  return 0;
}
