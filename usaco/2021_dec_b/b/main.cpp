#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int              n = sc.next_int();
  std::vector<int> a(n);
  for (int i = 0; i < n; i++)
    a[i] += sc.next_int();
  for (int i = 0; i < n; i++)
    a[i] -= sc.next_int();

  int last = 0;
  int inc  = 0;
  int dec  = 0;
  for (int i = 0; i < n; i++)
  {
    if (a[i] > last)
      inc += a[i] - last;
    else
      dec += last - a[i];
    last = a[i];
  }

  std::cout << std::max(inc, dec) << std::endl;

  return 0;
}
