#include "/home/jack/cm/debug"
#include "/home/jack/cm/intm"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  using int_t = cm::intm<1'000'000'007>;
  using int_t_t = cm::intm<1'000'000'006>;
  int n = sc.next_int();
  for (int i = 0; i < n; i++)
  {
    int a = sc.next_int();
    int b = sc.next_int();
    int c = sc.next_int();
    std::cout << int_t(a).pow(static_cast<int>(int_t_t(b).pow(c))) << std::endl;
  }

  return 0;
}
