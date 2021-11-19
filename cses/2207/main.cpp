#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <set>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{

  std::set<int> lose{
      1,   2,   4,   7,   10,  20,  23,  26,  50,  53,  270, 273, 276,  282,
      285, 288, 316, 334, 337, 340, 346, 359, 362, 365, 386, 389, 392,  566,
      630, 633, 636, 639, 673, 676, 682, 685, 923, 926, 929, 932, 1222,
  };

  int T = sc.next_int();
  for (int i = 0; i < T; i++)
  {
    int n = sc.next_int();
    puts(lose.count(n) ? "second" : "first");
  }

  return 0;
}
