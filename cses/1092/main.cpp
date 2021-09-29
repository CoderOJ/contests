#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();

  if (n % 4 == 0)
  {
    puts("YES");
    std::cout << n / 2 << std::endl;
    for (int i = 1, j = n; i < j; i += 2, j -= 2)
      std::cout << i << " " << j << " ";
    std::cout << std::endl;
    std::cout << n / 2 << std::endl;
    for (int i = 2, j = n - 1; i < j; i += 2, j -= 2)
      std::cout << i << " " << j << " ";
    std::cout << std::endl;
  }
  else if (n % 4 <= 2)
  {
    puts("NO");
  }
  else
  {
    puts("YES");
    std::cout << n / 2 + 1 << std::endl;
    std::cout << "1 2 ";
    for (int i = 4, j = n; i < j; i += 2, j -= 2)
      std::cout << i << " " << j << " ";
    std::cout << std::endl;
    std::cout << n / 2 << std::endl;
    std::cout << "3 ";
    for (int i = 5, j = n - 1; i < j; i += 2, j -= 2)
      std::cout << i << " " << j << " ";
    std::cout << std::endl;
  }

  return 0;
}

