#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int main()
{
  int n = sc.next_int();
  std::vector<std::string> ans{"0", "1"};
  for (int i = 1; i < n; i++)
  {
    std::vector<std::string> cur;
    for (auto it = ans.begin(); it != ans.end(); it++)
      cur.push_back("0" + *it);
    for (auto it = ans.rbegin(); it != ans.rend(); it++)
      cur.push_back("1" + *it);
    ans = std::move(cur);
  }

  for (auto i : ans)
    std::cout << i << std::endl;
  return 0;
}

