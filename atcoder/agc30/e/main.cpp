#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <cmath>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

int main()
{
  int n;
  std::cin >> n;
  std::string s, t;
  std::cin >> s >> t;

  auto get_break = [](const std::string &s) {
    std::vector<int> ans;
    char last = '0';
    for (int i = 0; i < (int)s.size(); i++)
      if (s[i] != last)
      {
        ans.push_back(i);
        last = s[i];
      }
    return ans;
  };

  auto sb = get_break(s);
  auto tb = get_break(t);
  see(sb);
  see(tb);

  auto vector_ref = [n](const std::vector<int> &a, int index) {
    if (index < 0)
      return 0;
    if (index >= (int)a.size())
      return n;
    return a[index];
  };

  int ans = std::numeric_limits<int>::max();
  int m = static_cast<int>(sb.size() + tb.size());
  m += m % 2;
  for (int offset = -m; offset <= m; offset += 2)
  {
    int cur_ans = 0;
    for (int i = -m * 2; i <= m * 2; i++)
      cur_ans += std::abs(vector_ref(sb, i) - vector_ref(tb, i + offset));
    see(offset, cur_ans);
    check_min(ans, cur_ans);
  }

  std::cout << ans << std::endl;

  return 0;
}
