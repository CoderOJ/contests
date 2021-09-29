#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  long long n = sc.next_int();
  while (n != 1)
  {
    std::cout << n << " ";
    if (n % 2 == 0) n /= 2;
    else n = n * 3 + 1;
  }
  std::cout << 1 << std::endl;
  return 0;
}

