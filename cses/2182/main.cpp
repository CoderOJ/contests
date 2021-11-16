#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

using int_t = cm::intm<1'000'000'007>;
using int_t_t = cm::intm<1'000'000'006>;

int main()
{
  int n = sc.next_int();
  int_t cnt = 1, sum = 1, mul = 1;
  int_t_t cnt_t = 1;
  for (int i = 0; i < n; i++)
  {
    int_t p = sc.next_int();
    int k = sc.next_int();
    mul = mul.pow(k + 1) * p.pow(1ll * k * (k + 1) / 2).pow(static_cast<int>(cnt_t));
    cnt *= (k + 1);
    cnt_t *= (k + 1);
    sum *= (1 - p.pow(k + 1)) / (1 - p);
  }

  std::cout << cnt << " " << sum << " " << mul << std::endl;

  return 0;
}

