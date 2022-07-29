#include "/home/jack/cm/0pch.hpp"
#include "/home/jack/cm/debug.hpp"
// #include "/home/jack/cm/intm.hpp"
// #include "/home/jack/cm/math_util.hpp"
#include "/home/jack/cm/scanner.hpp"
// #include "/home/jack/cm/segment_tree.hpp"
// #include "/home/jack/cm/string.hpp"
#include "/home/jack/cm/util.hpp"
#include <algorithm>
#include <string>
#include <vector>

cm::scanner<cm::optimal_reader> sc(stdin);

bool is_valid(const std::string &s)
{
  int a = 0;
  for (char c: s)
  {
    a += (c == '(') ? 1 : -1;
    if (a < 0)
      return false;
  }
  return a == 0;
}

int main()
{
  int n = sc.next_int();

  std::vector<int> col(n + n);
  for (int i = 0; i < n + n; i++)
    col[i] = sc.next_int() - 1;

  std::vector<std::vector<int>> occur(n);
  for (int i = 0; i < n + n; i++)
    occur[col[i]].push_back(i);

  std::string ans = ")";
  for (int i = 0; i < (1 << n); i++)
  {
    std::string s(n + n, '(');
    for (int j = 0; j < n; j++)
      if (i & (1 << j))
      {
        s[occur[j][0]] = ')';
        s[occur[j][1]] = ')';
      }
    if (is_valid(s))
      ans = std::min(ans, s);
  }

  std::cout << (ans != ")" ? ans : "(") << std::endl;

  return 0;
}
