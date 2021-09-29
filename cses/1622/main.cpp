#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <set>

int cnt[128];
std::set<char> alpha;
std::string s;

std::vector<std::string> ans;
void dfs(std::string cur, size_t n)
{
  if (n == 0)
  {
    ans.push_back(std::move(cur));
    return;
  }
  for (char c: alpha)
    if (cnt[static_cast<int>(c)])
    {
      cnt[static_cast<int>(c)]--;
      dfs(cur + c, n - 1);
      cnt[static_cast<int>(c)]++;
    }
}

int main()
{
  std::cin >> s;
  alpha = std::set<char>(s.begin(), s.end());
  for (char c: s)
    cnt[static_cast<int>(c)]++;
  dfs("", s.size());

  std::cout << ans.size() << std::endl;
  for (auto s : ans)
    std::cout << s << std::endl;
  return 0;
}

