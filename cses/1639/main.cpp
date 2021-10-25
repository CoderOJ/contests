#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

#include <algorithm>

int main()
{
  std::string s, t;  
  std::cin >> s >> t;
  std::vector<std::vector<int>> dp(s.size() + 1, std::vector<int>(t.size() + 1, 0x3f3f3f3f));
  for (size_t i = 0; i <= s.size(); i++) 
    dp[i][0] = static_cast<int>(i);
  for (size_t i = 0; i <= t.size(); i++) 
    dp[0][i] = static_cast<int>(i);
  for (size_t i = 0; i < s.size(); i++)
    for (size_t j = 0; j < t.size(); j++)
      dp[i + 1][j + 1] = std::min({
        dp[i][j + 1] + 1,
        dp[i + 1][j] + 1,
        dp[i][j] + (s[i] != t[j])});
  printf("%d\n", dp[s.size()][t.size()]);
  return 0;
}

