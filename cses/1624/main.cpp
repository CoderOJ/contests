#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

int cnt[8][8];

int dfs(int n)
{
  if (n == 8) return 1;
  int ans = 0;
  for (int i = 0; i < 8; i++)
    if (cnt[n][i] == 0)
    {
      for (int j = n + 1; j < 8; j++)
      {
        cnt[j][i]++;
        if (i - (j - n) >= 0) cnt[j][i - (j - n)]++;
        if (i + (j - n) <  8) cnt[j][i + (j - n)]++;
      }
      ans += dfs(n + 1);
      for (int j = n + 1; j < 8; j++)
      {
        cnt[j][i]--;
        if (i - (j - n) >= 0) cnt[j][i - (j - n)]--;
        if (i + (j - n) <  8) cnt[j][i + (j - n)]--;
      }
    }
  return ans;
}

int main()
{
  for (int i = 0; i < 8; i++)
    for (int j = 0; j < 8; j++)
      cnt[i][j] = sc.next_char() == '*';
  std::cout << dfs(0) << std::endl;
  return 0;
}

