#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

int n; 
std::string s;

std::string solve(std::string_view s)
{
  if (s[0] == 'a')
  {
    std::vector<size_t> pa, pb;
    for (size_t i = 0; i < s.size(); i++)
      (s[i] == 'a' ? pa : pb).push_back(i);
    std::string ans;
    size_t last_pos = 0;
    for (size_t i = 0; i < pa.size(); i++)
      if (pa[i] >= last_pos)
      {
        ans += "ab";
        last_pos = pb[i];
      }
    return ans;
  }
  else
  {
    std::string ans = "";
    size_t b_cnt = 0;
    while (!s.empty())
    {
      (s[0] == 'b') ? b_cnt++ : b_cnt--;
      s = s.substr(1);
      check_max(ans, std::string(b_cnt, 'b') + std::string(s));
    }
    return ans;
  }
}

int main()
{
  std::cin >> n;
  std::cin >> s;
  std::string_view sv(s);

  std::vector<std::string> ans;
  auto last = sv.begin();
  int a_cnt = 0;
  for (auto it = sv.begin(); it != sv.end(); )
  {
    a_cnt += (*it++ == 'a' ? 1 : -1);
    if (a_cnt == 0)
    {
      std::string cur = solve(sv.substr(last - sv.begin(), it - last));
      last = it;
      while (!ans.empty() && cur > ans.back() + cur)
        ans.pop_back();
      ans.push_back(cur);
    }
  }

  for (auto s: ans)
    std::cout << s;
  std::cout << std::endl;
  return 0;
}

