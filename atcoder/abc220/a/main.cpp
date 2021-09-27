#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int a = sc.next_int();
  int b = sc.next_int();
  int c = sc.next_int();
  int t = a / c * c;
  if (t < a) t += c;
  if (t <= b) { printf("%d\n", t); }
  else { puts("-1"); }
  return 0;
}

