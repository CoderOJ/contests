#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
#define int long long
  int n = sc.next_int();
  int sum_d = 0;
  std::vector<int> dur;
  for (int i = 0; i < n; i++)
  {
    dur.push_back(sc.next_int());
    sum_d += sc.next_int();
  }

  std::sort(dur.begin(), dur.end());
  int cur = 0;
  for (int x: dur) sum_d -= (cur += x);
  std::cout << sum_d << std::endl;

  return 0;
}

