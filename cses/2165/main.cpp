#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int find_other(int a, int b)
{
  if (a != 1 && b != 1) return 1;
  if (a != 2 && b != 2) return 2;
  return 3;
}

void move(int f, int t, int n)
{
  if (n == 1)
  {
    std::cout << f << " " << t << std::endl;
    return;
  }
  int o = find_other(f, t);
  move(f, o, n - 1);
  std::cout << f << " " << t << std::endl;
  move(o, t, n - 1);
}

int main()
{
  int n = sc.next_int();
  std::cout << (1 << n) - 1 << std::endl;
  move(1, 3, n);
  return 0;
}

