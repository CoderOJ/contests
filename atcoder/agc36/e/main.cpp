#include "/home/jack/cm/debug"
#include "/home/jack/cm/scanner"
#include "/home/jack/cm/util"
#include <algorithm>
#include <cstring>
// #include "/home/jack/cm/intm"
// #include "/home/jack/cm/string"

cm::scanner<cm::optimal_reader> sc(stdin);

constexpr int N = 1000005;
char          s[N];

int  n, m;
int  a[N], b[N], c[N], d[N];
int  cnt[3], p[3], q[3];
bool mark[N];

int main()
{
  m = static_cast<int>(sc.next_token(s + 1) - (s + 1));
  n = 0;

  for (int i = 1; i <= m; ++i)
    if (i == 1 || s[i] != s[i - 1])
    {
      a[++n] = s[i] - 'A';
      cnt[a[n]]++;
    }

  p[1] = 1, p[2] = 2,
  std::sort(p, p + 3, [&](int x, int y) { return cnt[x] < cnt[y]; });
  for (int i = 0; i < 3; ++i)
    q[p[i]] = i;
  for (int i = 1; i <= n; ++i)
    b[i] = q[a[i]];

  int last = 0;
  std::sort(cnt, cnt + 3);
  for (int i = 1; i <= n + 1; ++i)
    if (i > n || b[i] == 0)
    {
      if (i > n || i - last - 1 >= 2 || last == 0)
      {
        if (b[last + 1] == 2 && cnt[2] > cnt[1] && !mark[last + 1])
        {
          mark[last + 1] = 1;
          cnt[2]--;
        }
        if (b[i - 1] == 2 && cnt[2] > cnt[1] && !mark[i - 1])
        {
          mark[i - 1] = 1;
          cnt[2]--;
        }
      }
      last = i;
    }

  if (cnt[1] != cnt[2])
  {
    int pos = 0;
    for (int i = 1; i <= n; ++i)
      if (!mark[i])
      {
        if (pos && cnt[2] > cnt[1] &&
            ((d[pos] == 2 && b[i] == 0) || (d[pos] == 0 && b[i] == 2)))
        {
          cnt[2]--;
          cnt[0]--;
          pos--;
        }
        else
          d[++pos] = b[i];
      }
    n = pos;
    memcpy(b, d, (n + 3) * 4);
    memset(mark, 0, sizeof(mark));
  }

  int pos  = 0;
  int rest = cnt[1] - cnt[0];
  for (int i = 1; i <= n; ++i)
    if (!mark[i])
      c[++pos] = b[i];

  last = 0;
  memset(mark, 0, sizeof(mark));
  for (int i = 1; i <= pos + 1; ++i)
    if (i > pos || c[i] == 0)
    {
      int o = !last || i > pos ? 1 : 2;
      for (int j = last + 1; j + o < i && rest; j += 2)
      {
        mark[j] = mark[j + 1] = 1;
        rest--;
      }
      last = i;
    }

  for (int i = 1; i <= pos; ++i)
    if (!mark[i])
      putchar(p[c[i]] + 'A');
  puts("");

  return 0;
}
