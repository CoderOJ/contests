#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <list>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 2005;

char e[N][N];
int  n;

int main()
{
  n = sc.next_int();
  for (int i = 0; i < n; i++)
    for (int j = 0; j < i; j++)
      e[i][j] = e[j][i] = sc.next_char();

  for (int s = 0; s < n; s++)
  {
    std::cout << n << std::endl;
    std::list<int> ans;
    ans.insert(ans.begin(), s);
    auto it  = ans.begin();
    char ec0 = '0';
    for (int u = 0; u < n; u++)
      if (u != s)
      {
        if (ec0 == '0')
        {
          ec0 = e[s][u];
          ++it;
          ans.insert(it, u);
          --it;
        }
        else
        {
          if (it == ans.begin())
          {
            ec0 = ec0 == 'R' ? 'B' : 'R';
            it = ans.end();
            it--;
          }
          if (e[*it][u] == ec0)
          {
            ++it;
            ans.insert(it, u);
            if (it == ans.end() || e[u][*it] != ec0)
              --it;
          }
          else
          {
            ans.insert(it, u);
            --it;
            --it;
            if (e[*it][u] == ec0)
              ++it;
          }
        }
      }
    for (const int u : ans)
      printf("%d ", u + 1);
    puts("");
  }

  return 0;
}
