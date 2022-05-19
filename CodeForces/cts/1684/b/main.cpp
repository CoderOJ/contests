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
    int64_t a = sc.next_int();
    int64_t b = sc.next_int();
    int64_t c = sc.next_int();

    int64_t z = c;
    int64_t y = b;
    int64_t x = (int64_t)(1e9) * b + a;

    std::cout << x << " " << y << " " << z << std::endl;
    cm_assert(x % y == a);
    cm_assert(y % z == b);
    cm_assert(z % x == c);
  }
  return 0;
}
