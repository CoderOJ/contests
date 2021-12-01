#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int M = 7;

int  cnt[M][M], num[M], id[M];
bool ava[M];
char s[M];
int  n, m;

bool valid()
{
  for (int s = 1; s < (1 << m) - 1; s++)
  {
    int cnt_l = 0;
    for (int i = 0; i < m; i++)
      if (s & (1 << i))
        cnt_l += num[i + 1];
    int cnt_r = 0;
    for (int i = 0; i < m; i++)
      for (int j = i; j < m; j++)
        if (s & (1 << i) || s & (1 << j))
            cnt_r += cnt[i + 1][j + 1];
    see(s, cnt_l, cnt_r);
    if (cnt_l > cnt_r)
      return false;
  }
  return true;
}

int main()
{
  n = sc.next_int();
  for (int t = n; t > 0; t /= 10)
    m++;

  id[1] = 1;
  for (int i = 2; i <= m; i++)
    id[i] = id[i - 1] * 10;
  id[m + 1] = n + 1;
  for (int i = 1; i <= m; i++)
    num[i] = id[i + 1] - id[i];

  for (int i = 1; i < n; i++)
  {
    int u = static_cast<int>(sc.next_token(s) - s);
    int v = static_cast<int>(sc.next_token(s) - s);
    if (u == v)
      cnt[u][u] += 1;
    else
    {
      cnt[u][v] += 1;
      cnt[v][u] += 1;
    }
  }

  if (!valid())
  {
    puts("-1");
    return 0;
  }

  // make root
  id[1] += 1;
  num[1] -= 1;
  ava[1] = true;

  for (int r = 0; r < n - 1; r++) 
  {
    for (int i = 1; i <= m; i++)
      if (ava[i])
        for (int j = 1; j <= m; j++)
          if (cnt[i][j] > 0 && num[j] > 0)
          {
            // attempt to add this
            {
              cnt[i][j] -= 1; 
              cnt[j][i] -= (i != j);
              num[j] -= 1;
            }
            if (valid())
            {
              printf("%d %d\n", id[i] - 1, id[j]);
              id[j] += 1;
              ava[j] = true;
              goto finish;
            }
            else
            {
              // retrieve
              cnt[i][j] += 1; 
              cnt[j][i] += (i != j);
              num[j] += 1;
            }
          }
finish:;
  }

  return 0;
}
