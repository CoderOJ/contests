#include "/home/jack/cm/debug"
#include "/home/jack/cm/intm"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <ostream>
#include <queue>
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int MOD = 1'000'000'007;
constexpr int N = 1005;
constexpr int D = 53;
constexpr int K = 11;
using int_t = cm::intm<MOD>;

int n, d;
char s[N], a[D], b[D];
int_t p[N][2], f[D][N * D][2];

int trie[N * D][K], ed[N * D], fail[N * D], tot = 1;

void build()
{
  int m = d / 2;
  for (int i = 1; i + m - 1 <= n; i++)
  {
    int p = 1;
    for (int j = i, k = 1; k <= m; j++, k++)
    {
      int c = s[j] - '0';
      if (!trie[p][c])
        trie[p][c] = ++tot;
      p = trie[p][c];
    }
    ed[p] = 1;
  }

  std::queue<int> que;
  for (int i = 0; i < 10; i++)
    if (trie[1][i])
      fail[trie[1][i]] = 1, que.push(trie[1][i]);
    else
      trie[1][i] = 1;
  while (que.size())
  {
    int x = que.front();
    que.pop();
    for (int i = 0; i < 10; i++)
      if (trie[x][i])
        fail[trie[x][i]] = trie[fail[x]][i], que.push(trie[x][i]);
      else
        trie[x][i] = trie[fail[x]][i];
  }
}

int_t calc(char *t)
{
  p[d + 1][0] = p[d + 1][1] = 1;
  for (int i = d; i; i--)
    p[i][0] = p[i + 1][0] * 10,
    p[i][1] = (t[i] - '0') * p[i + 1][0] + p[i + 1][1];

  int_t ans = 0;
  for (int i = 1; i <= d; i++)
    for (int j = 1; j <= tot; j++)
      for (int k = 0; k < 2; k++)
        f[i][j][k] = 0;
  f[0][1][1] = 1;

  for (int i = 0; i < d; i++)
    for (int j = 1; j <= tot; j++)
      if (!ed[j])
        for (int k = 0; k < 10; k++)
        {
          int o = trie[j][k];
          f[i + 1][o][0] += f[i][j][0];
          if (k < t[i + 1] - '0')
            f[i + 1][o][0] += f[i][j][1];
          if (k == t[i + 1] - '0')
            f[i + 1][o][1] += f[i][j][1];
        }

  for (int i = 1; i <= d; i++)
    for (int j = 1; j <= tot; j++)
      if (ed[j])
        ans += f[i][j][0] * p[i + 1][0] + f[i][j][1] * p[i + 1][1];
  return ans;
}

int main()
{
  n = static_cast<int>(sc.next_token(s + 1) - s - 1);
  d = static_cast<int>(sc.next_token(a + 1) - a - 1);
  d = static_cast<int>(sc.next_token(b + 1) - b - 1);

  build();

  int k = d;
  while (a[k] == '0')
    a[k--] = '9';
  --a[k];

  std::cout << calc(b) - calc(a) << std::endl;

  return 0;
}
